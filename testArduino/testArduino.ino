
#include <BeatleSerial.h>

BeatleSerial bSerial;
const char* cmdStr = "SBLR";

void setup(){
  Serial.begin(115200);
  bSerial.begin(Serial);
  bSerial.sendMaseCMDString(cmdStr);

}

void loop(){

}