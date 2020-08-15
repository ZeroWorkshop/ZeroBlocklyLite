#include <BeatleSerial.h>


BeatleSerial bSerial;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  bSerial.begin(Serial);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  bSerial.setSpeeds(255,255);
  delay(2000);
  bSerial.setSpeeds(255,-255);
  delay(2000);
  bSerial.setSpeeds(-255,-255);
  delay(2000);
  bSerial.setSpeeds(-255,255);
  delay(2000);
  
  /*
   tester.runWheel(beatleCMD::LEFTFORWARD, 200);
   tester.runWheel(beatleCMD::RIGHTFORWARD, 200);
   delay(2000);
   tester.runWheel(beatleCMD::LEFTBACKWARD, 200);
   tester.runWheel(beatleCMD::RIGHTFORWARD, 200);
   delay(2000);
    tester.runWheel(beatleCMD::LEFTBACKWARD, 200);
   tester.runWheel(beatleCMD::RIGHTBACKWARD, 200);
   delay(2000);
    tester.runWheel(beatleCMD::LEFTFORWARD, 200);
   tester.runWheel(beatleCMD::RIGHTBACKWARD, 200);
   delay(2000);*/
}
