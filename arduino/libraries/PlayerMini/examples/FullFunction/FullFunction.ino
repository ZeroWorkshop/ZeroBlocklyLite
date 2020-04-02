/***************************************************
 DFPlayer - A Mini MP3 Player For Arduino
 <https://www.dfrobot.com/product-1121.html>
 
 ***************************************************
 This example shows the all the function of library for DFPlayer.
 
 Created 2016-12-07
 By [Angelo qiao](Angelo.qiao@dfrobot.com)
 
 GNU Lesser General Public License.
 See <http://www.gnu.org/licenses/> for details.
 All above must be included in any redistribution
 ****************************************************/

/***********Notice and Trouble shooting***************
 1.Connection and Diagram can be found here
<https://www.dfrobot.com/wiki/index.php/DFPlayer_Mini_SKU:DFR0299#Connection_Diagram>
 2.This code is tested on Arduino Uno, Leonardo, Mega boards.
 ****************************************************/

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "PlayerMini.h"

SoftwareSerial mySoftwareSerial(A1, A0); // RX, TX
PlayerMini myPlayer;
void printDetail(uint8_t type, int value);

void setup()
{
  mySoftwareSerial.begin(9600);
  Serial.begin(115200);
  
  Serial.println();
  Serial.println(F("Player Mini Demo"));
  Serial.println(F("Initializing Player Mini ... (May take 3~5 seconds)"));
  
  if (!myPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("Player Mini online."));
  
  myPlayer.setTimeOut(500); //Set serial communictaion time out 500ms
  
  //----Set volume----
  myPlayer.volume(10);  //Set volume value (0~30).
  myPlayer.volumeUp(); //Volume Up
  myPlayer.volumeDown(); //Volume Down
  
  //----Set different EQ----
  myPlayer.EQ(PLAYER_EQ_NORMAL);
//  myPlayer.EQ(PLAYER_EQ_POP);
//  myPlayer.EQ(PLAYER_EQ_ROCK);
//  myPlayer.EQ(PLAYER_EQ_JAZZ);
//  myPlayer.EQ(PLAYER_EQ_CLASSIC);
//  myPlayer.EQ(PLAYER_EQ_BASS);
  
  //----Set device we use SD as default----
//  myPlayer.outputDevice(PLAYER_DEVICE_U_DISK);
  myPlayer.outputDevice(PLAYER_DEVICE_SD);
//  myPlayer.outputDevice(PLAYER_DEVICE_AUX);
//  myPlayer.outputDevice(PLAYER_DEVICE_SLEEP);
//  myPlayer.outputDevice(PLAYER_DEVICE_FLASH);
  
  //----Mp3 control----
//  myPlayer.sleep();     //sleep
//  myPlayer.reset();     //Reset the module
//  myPlayer.enableDAC();  //Enable On-chip DAC
//  myPlayer.disableDAC();  //Disable On-chip DAC
//  myPlayer.outputSetting(true, 15); //output setting, enable the output and set the gain to 15
  
  //----Mp3 play----
  myPlayer.next();  //Play next mp3
  delay(1000);
  myPlayer.previous();  //Play previous mp3
  delay(1000);
  myPlayer.play(1);  //Play the first mp3
  delay(1000);
  myPlayer.loop(1);  //Loop the first mp3
  delay(1000);
  myPlayer.pause();  //pause the mp3
  delay(1000);
  myPlayer.start();  //start the mp3 from the pause
  delay(1000);
  myPlayer.playFolder(15, 4);  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)
  delay(1000);
  myPlayer.enableLoopAll(); //loop all mp3 files.
  delay(1000);
  myPlayer.disableLoopAll(); //stop loop all mp3 files.
  delay(1000);
  myPlayer.playMp3Folder(4); //play specific mp3 in SD:/MP3/0004.mp3; File Name(0~65535)
  delay(1000);
  myPlayer.advertise(3); //advertise specific mp3 in SD:/ADVERT/0003.mp3; File Name(0~65535)
  delay(1000);
  myPlayer.stopAdvertise(); //stop advertise
  delay(1000);
  myPlayer.playLargeFolder(2, 999); //play specific mp3 in SD:/02/004.mp3; Folder Name(1~10); File Name(1~1000)
  delay(1000);
  myPlayer.loopFolder(5); //loop all mp3 files in folder SD:/05.
  delay(1000);
  myPlayer.randomAll(); //Random play all the mp3.
  delay(1000);
  myPlayer.enableLoop(); //enable loop.
  delay(1000);
  myPlayer.disableLoop(); //disable loop.
  delay(1000);

  //----Read imformation----
  Serial.println(myPlayer.readState()); //read mp3 state
  Serial.println(myPlayer.readVolume()); //read current volume
  Serial.println(myPlayer.readEQ()); //read EQ setting
  Serial.println(myPlayer.readFileCounts()); //read all file counts in SD card
  Serial.println(myPlayer.readCurrentFileNumber()); //read current play file number
  Serial.println(myPlayer.readFileCountsInFolder(3)); //read file counts in folder SD:/03
}

void loop()
{
  static unsigned long timer = millis();
  
  if (millis() - timer > 3000) {
    timer = millis();
    myPlayer.next();  //Play next mp3 every 3 second.
  }
  
  if (myPlayer.available()) {
    printDetail(myPlayer.readType(), myPlayer.read()); //Print the detail message from DFPlayer to handle different errors and states.
  }
}

void printDetail(uint8_t type, int value){
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case PlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case PlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case PlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case PlayerUSBInserted:
      Serial.println("USB Inserted!");
      break;
    case PlayerUSBRemoved:
      Serial.println("USB Removed!");
      break;
    case PlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case PlayerError:
      Serial.print(F("PlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
  
}

