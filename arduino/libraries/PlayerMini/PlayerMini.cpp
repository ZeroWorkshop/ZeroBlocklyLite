/*!
 * @file DFRobotDFPlayerMini.cpp
 * @brief DFPlayer - An Arduino Mini MP3 Player From DFRobot
 * @n Header file for DFRobot's DFPlayer
 *
 * @copyright	[DFRobot]( http://www.dfrobot.com ), 2016
 * @copyright	GNU Lesser General Public License
 *
 * @author [Angelo](Angelo.qiao@dfrobot.com)
 * @version  V1.0.3
 * @date  2016-12-07
 */

#include "PlayerMini.h"

void PlayerMini::setTimeOut(unsigned long timeOutDuration){
  _timeOutDuration = timeOutDuration;
}

void PlayerMini::uint16ToArray(uint16_t value, uint8_t *array){
  *array = (uint8_t)(value>>8);
  *(array+1) = (uint8_t)(value);
}

uint16_t PlayerMini::calculateCheckSum(uint8_t *buffer){
  uint16_t sum = 0;
  for (int i=Stack_Version; i<Stack_CheckSum; i++) {
    sum += buffer[i];
  }
  return -sum;
}

void PlayerMini::sendStack(){
  if (_sending[Stack_ACK]) {  //if the ack mode is on wait until the last transmition
    while (_isSending) {
      delay(0);
      available();
    }
  }

#ifdef _DEBUG
  Serial.println();
  Serial.print(F("sending:"));
  for (int i=0; i<PLAYER_SEND_LENGTH; i++) {
    Serial.print(_sending[i],HEX);
    Serial.print(F(" "));
  }
  Serial.println();
#endif
  _serial->write(_sending, PLAYER_SEND_LENGTH);
  _timeOutTimer = millis();
  _isSending = _sending[Stack_ACK];

  if (!_sending[Stack_ACK]) { //if the ack mode is off wait 10 ms after one transmition.
    delay(10);
  }
}

void PlayerMini::sendStack(uint8_t command){
  sendStack(command, 0);
}

void PlayerMini::sendStack(uint8_t command, uint16_t argument){
  _sending[Stack_Command] = command;
  uint16ToArray(argument, _sending+Stack_Parameter);
  uint16ToArray(calculateCheckSum(_sending), _sending+Stack_CheckSum);
  sendStack();
}

void PlayerMini::sendStack(uint8_t command, uint8_t argumentHigh, uint8_t argumentLow){
  uint16_t buffer = argumentHigh;
  buffer <<= 8;
  sendStack(command, buffer | argumentLow);
}

void PlayerMini::enableACK(){
  _sending[Stack_ACK] = 0x01;
}

void PlayerMini::disableACK(){
  _sending[Stack_ACK] = 0x00;
}

bool PlayerMini::waitAvailable(unsigned long duration){
  unsigned long timer = millis();
  if (!duration) {
    duration = _timeOutDuration;
  }
  while (!available()){
    if (millis() - timer > duration) {
      return false;
    }
    delay(0);
  }
  return true;
}

bool PlayerMini::begin(Stream &stream, bool isACK, bool doReset){
  _serial = &stream;

  if (isACK) {
    enableACK();
  }
  else{
    disableACK();
  }

  if (doReset) {
    reset();
    waitAvailable(2000);
    delay(200);
  }
  else {
    // assume same state as with reset(): online
    _handleType = PlayerCardOnline;
  }

  return (readType() == PlayerCardOnline) || (readType() == PlayerUSBOnline) || !isACK;
}

uint8_t PlayerMini::readType(){
  _isAvailable = false;
  return _handleType;
}

uint16_t PlayerMini::read(){
  _isAvailable = false;
  return _handleParameter;
}

bool PlayerMini::handleMessage(uint8_t type, uint16_t parameter){
  _receivedIndex = 0;
  _handleType = type;
  _handleParameter = parameter;
  _isAvailable = true;
  return _isAvailable;
}

bool PlayerMini::handleError(uint8_t type, uint16_t parameter){
  handleMessage(type, parameter);
  _isSending = false;
  return false;
}

uint8_t PlayerMini::readCommand(){
  _isAvailable = false;
  return _handleCommand;
}

void PlayerMini::parseStack(){
  uint8_t handleCommand = *(_received + Stack_Command);
  if (handleCommand == 0x41) { //handle the 0x41 ack feedback as a spcecial case, in case the pollusion of _handleCommand, _handleParameter, and _handleType.
    _isSending = false;
    return;
  }

  _handleCommand = handleCommand;
  _handleParameter =  arrayToUint16(_received + Stack_Parameter);

  switch (_handleCommand) {
    case 0x3D:
      handleMessage(PlayerPlayFinished, _handleParameter);
      break;
    case 0x3F:
      if (_handleParameter & 0x01) {
        handleMessage(PlayerUSBOnline, _handleParameter);
      }
      else if (_handleParameter & 0x02) {
        handleMessage(PlayerCardOnline, _handleParameter);
      }
      else if (_handleParameter & 0x03) {
        handleMessage(PlayerCardUSBOnline, _handleParameter);
      }
      break;
    case 0x3A:
      if (_handleParameter & 0x01) {
        handleMessage(PlayerUSBInserted, _handleParameter);
      }
      else if (_handleParameter & 0x02) {
        handleMessage(PlayerCardInserted, _handleParameter);
      }
      break;
    case 0x3B:
      if (_handleParameter & 0x01) {
        handleMessage(PlayerUSBRemoved, _handleParameter);
      }
      else if (_handleParameter & 0x02) {
        handleMessage(PlayerCardRemoved, _handleParameter);
      }
      break;
    case 0x40:
      handleMessage(PlayerError, _handleParameter);
      break;
    case 0x3C:
    case 0x3E:
    case 0x42:
    case 0x43:
    case 0x44:
    case 0x45:
    case 0x46:
    case 0x47:
    case 0x48:
    case 0x49:
    case 0x4B:
    case 0x4C:
    case 0x4D:
    case 0x4E:
    case 0x4F:
      handleMessage(PlayerFeedBack, _handleParameter);
      break;
    default:
      handleError(WrongStack);
      break;
  }
}

uint16_t PlayerMini::arrayToUint16(uint8_t *array){
  uint16_t value = *array;
  value <<=8;
  value += *(array+1);
  return value;
}

bool PlayerMini::validateStack(){
  return calculateCheckSum(_received) == arrayToUint16(_received+Stack_CheckSum);
}

bool PlayerMini::available(){
  while (_serial->available()) {
    delay(0);
    if (_receivedIndex == 0) {
      _received[Stack_Header] = _serial->read();
#ifdef _DEBUG
      Serial.print(F("received:"));
      Serial.print(_received[_receivedIndex],HEX);
      Serial.print(F(" "));
#endif
      if (_received[Stack_Header] == 0x7E) {
        _receivedIndex ++;
      }
    }
    else{
      _received[_receivedIndex] = _serial->read();
#ifdef _DEBUG
      Serial.print(_received[_receivedIndex],HEX);
      Serial.print(F(" "));
#endif
      switch (_receivedIndex) {
        case Stack_Version:
          if (_received[_receivedIndex] != 0xFF) {
            return handleError(WrongStack);
          }
          break;
        case Stack_Length:
          if (_received[_receivedIndex] != 0x06) {
            return handleError(WrongStack);
          }
          break;
        case Stack_End:
#ifdef _DEBUG
          Serial.println();
#endif
          if (_received[_receivedIndex] != 0xEF) {
            return handleError(WrongStack);
          }
          else{
            if (validateStack()) {
              _receivedIndex = 0;
              parseStack();
              return _isAvailable;
            }
            else{
              return handleError(WrongStack);
            }
          }
          break;
        default:
          break;
      }
      _receivedIndex++;
    }
  }

  if (_isSending && (millis()-_timeOutTimer>=_timeOutDuration)) {
    return handleError(TimeOut);
  }

  return _isAvailable;
}

void PlayerMini::next(){
  sendStack(0x01);
}

void PlayerMini::previous(){
  sendStack(0x02);
}

void PlayerMini::play(int fileNumber){
  sendStack(0x03, fileNumber);
}

void PlayerMini::volumeUp(){
  sendStack(0x04);
}

void PlayerMini::volumeDown(){
  sendStack(0x05);
}

void PlayerMini::volume(uint8_t volume){
  sendStack(0x06, volume);
}

void PlayerMini::EQ(uint8_t eq) {
  sendStack(0x07, eq);
}

void PlayerMini::loop(int fileNumber) {
  sendStack(0x08, fileNumber);
}

void PlayerMini::outputDevice(uint8_t device) {
  sendStack(0x09, device);
  delay(200);
}

void PlayerMini::sleep(){
  sendStack(0x0A);
}

void PlayerMini::reset(){
  sendStack(0x0C);
}

void PlayerMini::start(){
  sendStack(0x0D);
}

void PlayerMini::pause(){
  sendStack(0x0E);
}

void PlayerMini::playFolder(uint8_t folderNumber, uint8_t fileNumber){
  sendStack(0x0F, folderNumber, fileNumber);
}

void PlayerMini::outputSetting(bool enable, uint8_t gain){
  sendStack(0x10, enable, gain);
}

void PlayerMini::enableLoopAll(){
  sendStack(0x11, 0x01);
}

void PlayerMini::disableLoopAll(){
  sendStack(0x11, 0x00);
}

void PlayerMini::playMp3Folder(int fileNumber){
  sendStack(0x12, fileNumber);
}

void PlayerMini::advertise(int fileNumber){
  sendStack(0x13, fileNumber);
}

void PlayerMini::playLargeFolder(uint8_t folderNumber, uint16_t fileNumber){
  sendStack(0x14, (((uint16_t)folderNumber) << 12) | fileNumber);
}

void PlayerMini::stopAdvertise(){
  sendStack(0x15);
}

void PlayerMini::stop(){
  sendStack(0x16);
}

void PlayerMini::loopFolder(int folderNumber){
  sendStack(0x17, folderNumber);
}

void PlayerMini::randomAll(){
  sendStack(0x18);
}

void PlayerMini::enableLoop(){
  sendStack(0x19, 0x00);
}

void PlayerMini::disableLoop(){
  sendStack(0x19, 0x01);
}

void PlayerMini::enableDAC(){
  sendStack(0x1A, 0x00);
}

void PlayerMini::disableDAC(){
  sendStack(0x1A, 0x01);
}

int PlayerMini::readState(){
  sendStack(0x42);
  if (waitAvailable()) {
    if (readType() == PlayerFeedBack) {
      return read();
    }
    else{
      return -1;
    }
  }
  else{
    return -1;
  }
}

int PlayerMini::readVolume(){
  sendStack(0x43);
  if (waitAvailable()) {
    return read();
  }
  else{
    return -1;
  }
}

int PlayerMini::readEQ(){
  sendStack(0x44);
  if (waitAvailable()) {
    if (readType() == PlayerFeedBack) {
      return read();
    }
    else{
      return -1;
    }
  }
  else{
    return -1;
  }
}

int PlayerMini::readFileCounts(uint8_t device){
  switch (device) {
    case PLAYER_DEVICE_U_DISK:
      sendStack(0x47);
      break;
    case PLAYER_DEVICE_SD:
      sendStack(0x48);
      break;
    case PLAYER_DEVICE_FLASH:
      sendStack(0x49);
      break;
    default:
      break;
  }

  if (waitAvailable()) {
    if (readType() == PlayerFeedBack) {
      return read();
    }
    else{
      return -1;
    }
  }
  else{
    return -1;
  }
}

int PlayerMini::readCurrentFileNumber(uint8_t device){
  switch (device) {
    case PLAYER_DEVICE_U_DISK:
      sendStack(0x4B);
      break;
    case PLAYER_DEVICE_SD:
      sendStack(0x4C);
      break;
    case PLAYER_DEVICE_FLASH:
      sendStack(0x4D);
      break;
    default:
      break;
  }
  if (waitAvailable()) {
    if (readType() == PlayerFeedBack) {
      return read();
    }
    else{
      return -1;
    }
  }
  else{
    return -1;
  }
}

int PlayerMini::readFileCountsInFolder(int folderNumber){
  sendStack(0x4E, folderNumber);
  if (waitAvailable()) {
    if (readType() == PlayerFeedBack) {
      return read();
    }
    else{
      return -1;
    }
  }
  else{
    return -1;
  }
}

int PlayerMini::readFolderCounts(){
  sendStack(0x4F);
  if (waitAvailable()) {
    if (readType() == PlayerFeedBack) {
      return read();
    }
    else{
      return -1;
    }
  }
  else{
    return -1;
  }
}

int PlayerMini::readFileCounts(){
  return readFileCounts(PLAYER_DEVICE_SD);
}

int PlayerMini::readCurrentFileNumber(){
  return readCurrentFileNumber(PLAYER_DEVICE_SD);
}


void PlayerMini::VoiceWord(int num)
{
  //Serial.println(num);
  if(num <20)
  {
  playFolder(1, num);
  if(num ==  17 || num == 18)
  delay(600);
  else 
  delay(400);
  }
}

void PlayerMini::VoiceWeight(int value)
{
  int tmp_value;
  int arr[5]={0,0,0,0,0};
  int thousand_status = 0;
  int hundred_status = 0;
  int ten_status = 0;
  tmp_value = value;
  int i,m,bit_num;
  i =1;
  bit_num = 1;
  m = tmp_value;
  while(tmp_value>=10)
  {
    tmp_value/=10;
    i*=10;
    bit_num++;
  }
  int idx = bit_num;
  while(m>0)
  {
     tmp_value = m/i;
     arr[idx-1] = tmp_value;
     m = m - tmp_value * i;
     i /= 10;    
     idx --;
    
  }

  VoiceWord(17);
  VoiceWord(18);
  for(int idx = bit_num-1; idx >=0; idx--)
  {  
   // Serial.print("idx = ");Serial.print(idx); Serial.print("value = ");Serial.println(arr[idx]);
    if(arr[idx] >0)
    { 
        VoiceWord(arr[idx]+1);  
     //Serial.println(tmp_value);
    //if(idx ==4)VoiceWord(14); //
    if(idx ==3 )VoiceWord(14);
    else if(idx ==2 )VoiceWord(13);
    else if(idx ==1 )VoiceWord(12);
    }
    else
    {
      if(bit_num == 4){
        if(idx == 2)
        {
          if((arr[2] == 0) && (arr[1] > 0))VoiceWord(1);      
        }
        else if(idx == 1)
        {
           if(arr[1] == 0 && (arr[0] > 0) )VoiceWord(1); 
         }             
       }
       else if(bit_num == 3)
       {
         if(idx == 1)
         {
           if(arr[1] == 0 && (arr[0] > 0) )VoiceWord(1); 
          }   
        }
       else
       {
          if(arr[idx] == 0 && idx != 0)VoiceWord(1);
       }
    }
   }
  VoiceWord(16);
}