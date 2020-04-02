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
    Serial.println(F("2.Please insert the SD card or USB drive!"));
    while(true){
      delay(0); // Code to compatible with ESP8266 watch dog.
    }
  }
  Serial.println(F("Player Mini online."));
}

void loop()
{
  static unsigned long timer = millis();

  if (millis() - timer > 3000) {
    timer = millis();
    
    int value;

//    value = myPlayer.readState(); //read mp3 state
//    value = myPlayer.readVolume(); //read current volume
//    value = myPlayer.readEQ(); //read EQ setting
//    value = myPlayer.readFileCounts(); //read all file counts in SD card
//    value = myPlayer.readCurrentFileNumber(); //read current play file number
    value = myPlayer.readFileCountsInFolder(3); //read file counts in folder SD:/03
    
    if (value == -1) {  //Error while Reading.
      printDetail(myPlayer.readType(), myPlayer.read());
    }
    else{ //Successfully get the result.
      Serial.println(value);
    }
  }
  
  if (myPlayer.available()) {
    printDetail(myPlayer.readType(), myPlayer.read()); //Print the detail message from Player to handle different errors and states.
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
