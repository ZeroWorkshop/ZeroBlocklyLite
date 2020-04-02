
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
  /*
    *  M1   --  0b1000
    *  M2   --  0b0100    
    *  M3   --  0b0010    
    *  M4   --  0b0001   *
    *
     */
  // StarterPro_S1.motorControl(0b1000,FORWARD,200);
  StarterPro_S1.motorControl(M1,200);
  delay(1000);
  StarterPro_S1.motorControl(M1,-200);
  delay(1000);

 
}
