
#include "StarterProI2C.h"
#include <Wire.h>
#include <SoftwareSerial.h>

StarterProI2C  StarterPro_S1(0x09);

void setup() {
  // put your setup code here, to run once:
  StarterPro_S1.begin();
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:

 
  StarterPro_S1.stepperControl(M1M2,300,3000);
  StarterPro_S1.stepperControl(M1M2,300,-3000);
  
 
}