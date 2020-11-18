
#include <PS4Controller.h>

#include "ZWHuskyLens.h"

#include <BeatleSerial.h>
#include "beatleESP32_general.h"

#include "NextionSimple.h"

volatile int state;

ZWHuskyLens huskylens;

BeatleSerial bSerial;

const char* cmd2TargetStr = "SBLR";

#define nextion Serial2
NextionSimple myNextion(nextion, 115200);
String message;
char* cmd;
char str1[50]
;char str2[50];

void setup(){
  state = 0;
  Serial.begin(115200);
  PS4.begin("00:01:02:03:04:05");

  Wire.begin();
  while (!huskylens.begin(Wire))
  {
    delay(100);
  }

  huskylens.writeAlgorithm(ALGORITHM_COLOR_RECOGNITION);
  Serial.begin(115200);
  bSerial.begin(Serial);

  Serial.begin(115200);

  myNextion.init(); ;

}

void loop(){
  switch (state) {
   case 0:
    if (PS4.data.button.ps) {
      bSerial.sendMazeGotoTargetCMD(cmd2TargetStr);
      state = 1;

    }
    break;
   case 1:
    if (targetReached(10000)) {
      cmd = "cls 63624";
      myNextion.sendCommand(cmd);

    }
    break;
   case 2:
    break;
   default:
    break;
  }

}