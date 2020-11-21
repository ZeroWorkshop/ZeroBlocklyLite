
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

const char* cmd2TargetStr = "SBLR";

void setup(){
  state = 0;
  Serial.begin(115200);
  PS4.begin("f0:d5:bf:c6:d6:25");

  Wire.begin();
  while (!huskylens.begin(Wire))
  {
    delay(100);
  }

  Serial.begin(115200);

  myNextion.init(); ;

  huskylens.writeAlgorithm(ALGORITHM_COLOR_RECOGNITION);cmd = "cls YELLOW";
  myNextion.sendCommand(cmd);
  Serial.begin(115200);
  bSerial.begin(Serial);

  ioexpander.begin();
  ioexpander.servoWrite(90);

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
    if (targetReached(50000)) {
      cmd = "cls WHITE";
      myNextion.sendCommand(cmd);
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
      HUSKYLENSResult result = huskylens.read();
      trackTarget(result);
      if (huskylens.request(1)) {
        cmd = "cls RED";
        myNextion.sendCommand(cmd);

      } else if (huskylens.request(2)) {
        cmd = "cls GREEN";
        myNextion.sendCommand(cmd);
      } else if (huskylens.request(3)) {
        cmd = "cls BLUE";
        myNextion.sendCommand(cmd);
      }

    }
    break;
   default:
    break;
  }

}