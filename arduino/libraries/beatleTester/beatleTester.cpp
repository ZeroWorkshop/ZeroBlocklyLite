#include "beatleTester.h"

bool beatleTester::begin(Stream &stream)
{
  _serial = &stream;

  sendStack.start_byte = beatleCMD::SB;
  sendStack.version    = beatleCMD::VER;
  sendStack.length     = beatleCMD::LEN;
  sendStack.end_byte   = beatleCMD::EB;

  recStack.start_byte  = beatleCMD::SB;
  recStack.version     = beatleCMD::VER;
  recStack.length      = beatleCMD::LEN;
  recStack.end_byte    = beatleCMD::EB;

  return true;
}

void beatleTester::progEEPROM(uint8_t prodY, uint8_t prodM, uint8_t prodD, uint8_t delY, uint8_t delM, uint8_t delD) {
	sendStack.commandValue  = beatleCMD::SET_PRODDATE;
	sendStack.feedbackValue = beatleCMD::NO_FEEDBACK;
		
	uint8_t tempMSB = ((prodY & 0x1F) << 3) | ((prodM >> 1) & 0x7);
	uint8_t tempLSB = ((prodM & 0x1)  << 7) | (((prodD >> 2) & 0x1F) << 2);
	 
  sendStack.paramMSB = tempMSB;
  sendStack.paramLSB = tempLSB;

  findChecksum(&sendStack);
  sendData();
  
  delay(10);
  
  sendStack.commandValue  = beatleCMD::WRITE_EEPROM;
	sendStack.feedbackValue = beatleCMD::NO_FEEDBACK;
		
	tempMSB = ((delY & 0x1F) << 3) | ((delM >> 1) & 0x7);
	tempLSB = ((delM & 0x1)  << 7) | (((delD >> 2) & 0x1F) << 2);
	 
  sendStack.paramMSB = tempMSB;
  sendStack.paramLSB = tempLSB;

  findChecksum(&sendStack);
  sendData();
}


void beatleTester::resetBeatle() {
  sendStack.commandValue  = beatleCMD::RESET_BEATLE;

  sendStack.feedbackValue = beatleCMD::NO_FEEDBACK;
  sendStack.paramMSB = 0;
  sendStack.paramLSB = 0;

  findChecksum(&sendStack);
  sendData();
}


void beatleTester::runWheel(uint8_t direct, uint8_t speed) {
  sendStack.commandValue  = beatleCMD::RUNWHEELS;

  sendStack.feedbackValue = beatleCMD::NO_FEEDBACK;
  sendStack.paramMSB = direct;
  sendStack.paramLSB = speed;

  findChecksum(&sendStack);
  sendData();
}





void beatleTester::playBuzzer() {
  sendStack.commandValue  = beatleCMD::PLAYBUZZER;
  sendStack.feedbackValue = beatleCMD::NO_FEEDBACK;
  sendStack.paramMSB = 0;
  sendStack.paramLSB = 1;

  findChecksum(&sendStack);
  sendData();
}




void beatleTester::setLED(uint8_t on_off, uint8_t color) {
  sendStack.commandValue  = beatleCMD::SETLED;
  sendStack.feedbackValue = beatleCMD::NO_FEEDBACK;


  sendStack.paramMSB = on_off;
  sendStack.paramLSB = color;


  findChecksum(&sendStack);
  sendData();
}



bool beatleTester::isDocked()
{
  int16_t result = query(beatleCMD::GET_STATUS_);

  if (result != -1) {    //only when there is a feedback from the serial and the paraMSB == 0xCC and paraLSB == 0xDD, means the board is docked
    if (recStack.paramMSB == 0xCC && recStack.paramLSB == 0xDD)  
      return true;
    else
      return false;
  }
  else
    return false;
}



int16_t beatleTester::buttonState(uint8_t button) {
  return query(beatleCMD::GET_BUTTON_STATE, 0, button);
}




int16_t beatleTester::frontIRSensors() {
  return query(beatleCMD::GET_IRSENSORS);
}




int16_t beatleTester::lineSensors() {
  return query(beatleCMD::GET_LINESENSORS);
}


/////////////////////////////////////////////////////////
void beatleTester::findChecksum(stack *_stack)
{
  uint16_t checksum = (~(_stack->version + _stack->length + _stack->commandValue + _stack->feedbackValue + _stack->paramMSB + _stack->paramLSB)) + 1;

  _stack->checksumMSB = checksum >> 8;
  _stack->checksumLSB = checksum & 0xFF;
}




void beatleTester::sendData()
{
  _serial->write(sendStack.start_byte);
  _serial->write(sendStack.version);
  _serial->write(sendStack.length);
  _serial->write(sendStack.commandValue);
  _serial->write(sendStack.feedbackValue);
  _serial->write(sendStack.paramMSB);
  _serial->write(sendStack.paramLSB);
  _serial->write(sendStack.checksumMSB);
  _serial->write(sendStack.checksumLSB);
  _serial->write(sendStack.end_byte);
}




void beatleTester::flush()
{
  while (_serial->available())
    _serial->read();
}




int16_t beatleTester::query(uint8_t cmd, uint8_t msb, uint8_t lsb)
{
  flush();

  sendStack.commandValue  = cmd;
  sendStack.feedbackValue = beatleCMD::FEEDBACK;
  sendStack.paramMSB = msb;
  sendStack.paramLSB = lsb;

  findChecksum(&sendStack);
  sendData();

  if (getStatus(cmd))
    return (recStack.paramMSB << 8) | recStack.paramLSB;

  return -1;
}




bool beatleTester::getStatus(uint8_t cmd)
{
  timer = millis();
  bool result = parseFeedback();

  if (!result)
    return false;

  while (recStack.commandValue != cmd)
  {
    if (timeout())
      return false;

    result = parseFeedback();

    if (!result)
      return false;
  }

  return true;
}




bool beatleTester::parseFeedback()
{                  
	
  while (_serial->available() < beatleCMD::STACK_SIZE)
    if (timeout())  {    
    	//Serial.println("TIMEOUT!!!!!!");
      return false;
    }

  recStack.start_byte    = _serial->read();
  recStack.version       = _serial->read();
  recStack.length        = _serial->read();
  recStack.commandValue  = _serial->read();
  recStack.feedbackValue = _serial->read();
  recStack.paramMSB      = _serial->read();
  recStack.paramLSB      = _serial->read();
  recStack.checksumMSB   = _serial->read();
  recStack.checksumLSB   = _serial->read();
  recStack.end_byte      = _serial->read();

  //Serial.println(recStack.start_byte);
  //Serial.println(recStack.version);
  //Serial.println(recStack.length);
  //Serial.println(recStack.commandValue);
  //Serial.println(recStack.feedbackValue);
  //Serial.println(recStack.paramMSB);
  //Serial.println(recStack.paramLSB);
  //Serial.println(recStack.checksumMSB);
  //Serial.println(recStack.checksumLSB);
  //Serial.println(recStack.end_byte);

  
  return true;
}
/*
bool beatleTester::parseFeedback()
{
	uint8_t tempBuffer;
  uint8_t cmdBuffer[beatleCMD::STACK_SIZE];
  uint8_t tmp[beatleCMD::STACK_SIZE];
  uint8_t index = 0;
  uint8_t offset;
  
  while (_serial->available() < beatleCMD::STACK_SIZE)
    if (timeout())
      return false;
      
  while (_serial->available()) {
    tempBuffer = _serial->read();
    cmdBuffer[index++] = tempBuffer;
  }

  for (uint8_t i = 0; i < beatleCMD::STACK_SIZE; i++) {
    if (cmdBuffer[i] == beatleCMD::SB &&
        cmdBuffer[(i + 1) > 9 ? (i - 9) : (i + 1)] == beatleCMD::VER &&
        cmdBuffer[(i + 2) > 9 ? (i - 8) : (i + 2)] == beatleCMD::LEN) {
      offset = i;
    }
  }

  for (uint8_t j = 0; j < beatleCMD::STACK_SIZE; j++) {
    tmp[j] = cmdBuffer[offset + j > 9 ? (offset + j - 10) : (offset + j)];
  }



  recStack.start_byte    = tmp[0];
  recStack.version       = tmp[1];
  recStack.length        = tmp[2];
  recStack.commandValue  = tmp[3];
  recStack.feedbackValue = tmp[4];
  recStack.paramMSB      = tmp[5];
  recStack.paramLSB      = tmp[6];
  recStack.checksumMSB   = tmp[7];
  recStack.checksumLSB   = tmp[8];
  recStack.end_byte      = tmp[9];
  
  Serial.write(recStack.start_byte);
  Serial.write(recStack.version);
  Serial.write(recStack.length);
  Serial.write(recStack.commandValue);
  Serial.write(recStack.feedbackValue);
  Serial.write(recStack.paramMSB);
  Serial.write(recStack.paramLSB);
  Serial.write(recStack.checksumMSB);
  Serial.write(recStack.checksumLSB);
  Serial.write(recStack.end_byte);
  return true;
}
*/



bool beatleTester::timeout()
{
  if ((millis() - timer) >= threshold)
    return true;
  return false;
}




void beatleTester::printStack(stack _stack)
{
  Serial.println("Stack:");
  Serial.print(_stack.start_byte, HEX);    Serial.print(' ');
  Serial.print(_stack.version, HEX);       Serial.print(' ');
  Serial.print(_stack.length, HEX);        Serial.print(' ');
  Serial.print(_stack.commandValue, HEX);  Serial.print(' ');
  Serial.print(_stack.feedbackValue, HEX); Serial.print(' ');
  Serial.print(_stack.paramMSB, HEX);      Serial.print(' ');
  Serial.print(_stack.paramLSB, HEX);      Serial.print(' ');
  Serial.print(_stack.checksumMSB, HEX);   Serial.print(' ');
  Serial.print(_stack.checksumLSB, HEX);   Serial.print(' ');
  Serial.println(_stack.end_byte, HEX);
}
