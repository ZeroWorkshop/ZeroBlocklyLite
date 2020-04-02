
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
  long val;
   
  val = StarterPro_S1.analogRead(ZW_A1);
  Serial.print("val =  ");
  Serial.println(val);
  delay(100);
 
}