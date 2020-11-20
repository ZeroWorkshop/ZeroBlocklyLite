
#include "NextionSimple.h"
#include "HUSKYLENS.h"

#include "beatleESP32_general.h"

#define nextion Serial2
NextionSimple myNextion(nextion, 115200);
String message;
char* cmd;
char str1[50]
;char str2[50];

HUSKYLENS huskylens;

void setup(){
  Serial.begin(115200);

  myNextion.init(); ;

  Wire.begin();
  while (!huskylens.begin(Wire))
  {
    delay(100);
  }

  cmd = "cls WHITE";
  myNextion.sendCommand(cmd);
  huskylens.writeAlgorithm(ALGORITHM_TAG_RECOGNITION);
  Serial.begin(115200);
  ioexpander.begin();
  ioexpander.servoWrite(90);

}

void loop(){
  if (!huskylens.request()) {
    ServoScan();
    Serial.println("searching......1");

  } else if (!huskylens.isLearned()) {
    ServoScan();
    Serial.println("searching......2");
  } else if (!huskylens.available()) {
    ServoScan();
    Serial.println("searching......3");
  } else {
    HUSKYLENSResult result = huskylens.read();
    Serial.println("tracking");
    trackTarget(result);
    if (huskylens.countBlocks(1)) {
      cmd = "cls RED";
      myNextion.sendCommand(cmd);

    } else if (huskylens.countBlocks(2)) {
      cmd = "cls GREEN";
      myNextion.sendCommand(cmd);
    } else if (huskylens.countBlocks(3)) {
      cmd = "cls BLUE";
      myNextion.sendCommand(cmd);
    }

  }

}