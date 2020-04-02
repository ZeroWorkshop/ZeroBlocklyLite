
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
  
double power_voltage;
power_voltage = StarterPro_S1.getPower();

  Serial.print("val =  ");
  Serial.println(power_voltage);
  delay(100);
 
}
