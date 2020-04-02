#include "LineFollowerArray.h"
#include <Wire.h>
#include <SoftwareSerial.h>

LineFollowerArray  LineFollower(0x09);

void setup() {
  // put your setup code here, to run once:
  LineFollower.begin();
  //LineFollower.setMaxVal(2000);
  Serial.begin(115200);
}

void loop() {
  long sensor_raw_data[8];  
  LineFollower.read(sensor_raw_data);
  for(int i = 0; i<8; i++)
  {  
        Serial.print(sensor_raw_data[i]);
        Serial.print("\t");
  }  
    Serial.println(); 
    delay(250);
}