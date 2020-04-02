
#include "StarterProI2C.h"
#include <Wire.h>
#include <SoftwareSerial.h>

StarterProI2C  StarterPro_S1(0x09);

void setup() {
  // put your setup code here, to run once:
  StarterPro_S1.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  StarterPro_S1.digitalWrite(ZW_B1,HIGH);
  delay(100);
  StarterPro_S1.digitalWrite(ZW_B1,LOW);
  delay(100);
}
