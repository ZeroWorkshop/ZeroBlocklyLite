
#include <PS4Controller.h>

#include "HUSKYLENS.h"

#include "NextionSimple.h"
#include <BeatleSerial.h>

#include "beatleESP32_general.h"

volatile int state;

HUSKYLENS huskylens;

#define nextion Serial2
NextionSimple myNextion(nextion, 115200);
String message;
char* cmd;
char str1[50];
char str2[50];

BeatleSerial bSerial;

const char* cmd2TargetStr1 = "SSRSL";

const char* cmd2TargetStr2 = "SBLR";

void setup(){
  state = 0;
  Serial.begin(115200);
  PS4.begin("0c:fc:83:fe:38:de");

  Wire.begin();
  while (!huskylens.begin(Wire))
  {
    delay(100);
  }

  myNextion.init();

  huskylens.writeAlgorithm(ALGORITHM_TAG_RECOGNITION);cmd = "page 0";
  myNextion.sendCommand(cmd);
  while (message != "65 0 1 0 ff ff ff") {
    message = myNextion.listen();
    if (message != "") { // if a message is received...
    }
  }
  cmd = "page 1";
  myNextion.sendCommand(cmd);
  Serial.begin(115200);

  bSerial.begin(Serial);

  ioexpander.begin();
  ioexpander.servoWrite(90);

}

void loop(){
  switch (state) {
   case 0:
    cmd = "cls WHITE";
    myNextion.sendCommand(cmd);
    bSerial.sendMazeGotoTargetCMD(cmd2TargetStr1);
    state = 1;
    break;
   case 1:
    if (targetReached(50000)) {
      state = 2;

    } else {
      state = 10;

    }
    break;
   case 2:
    if (!huskylens.request()) {
      ServoScan();

    } else if (!huskylens.isLearned()) {
      ServoScan();
    } else if (!huskylens.available()) {
      ServoScan();
    } else {
      ioexpander.servoWrite(90);

    }
    break;
   case 3:
    bSerial.sendMazeGotoTargetCMD(cmd2TargetStr2);
    state = 4;
    break;
   case 4:
    break;
   default:
    break;
  }

}