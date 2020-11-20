﻿#include "PIDLoop.h"
#include "io_expander.h"

#define CAM_PAN_MIDDLE 500
#define PAN_RANGE 300
#define PAN_SEARCH_RANGE 1000


IOExpander  ioexpander(0x18);



PIDLoop panLoop(100, 0, 0, true);

double angle;
uint32_t lastMove = 0;
int scanIncrement = (PAN_SEARCH_RANGE) / 50;

extern int ID1;
int32_t lastXOrigin = 0;
int32_t lastXTarget = 0;

int sel;
bool targetReached(int timeout) {
  uint8_t tempBuffer;
  
	int timer = millis();
	
  while (!Serial.available()) {
    if (millis() - timer > timeout) return false;
  }
  while (Serial.available()) {
    tempBuffer = Serial.read();
    Serial.println(tempBuffer, HEX);
    if (tempBuffer == 0xCC) {
      tempBuffer = Serial.read();
      if (tempBuffer == 0xDD) {
        return true;
      }
    }
  }
  return false;
}

void ServoScan()
{

  if (millis() - lastMove > 50)
  {


    lastMove = millis();
    panLoop.m_command += scanIncrement;

    if ((panLoop.m_command >= CAM_PAN_MIDDLE + PAN_SEARCH_RANGE / 2) || (panLoop.m_command <= CAM_PAN_MIDDLE - PAN_SEARCH_RANGE / 2))
    {

       scanIncrement   = -scanIncrement;


      delay(random(100, 200));
    }

    angle = map(panLoop.m_command, 0, 1000, 5, 175);
    //Serial.print("Servo angle = ");Serial.println(angle);
    ioexpander.servoWrite(angle);
    
  }
}

void trackTarget(HUSKYLENSResult result) {
   int32_t panOffset;
   panOffset = (int32_t)160 - (int32_t)result.xCenter;


   // update loops
   panLoop.update(panOffset);
   angle = map(panLoop.m_command, 0, 1000, 0, 180);
   ioexpander.servoWrite(angle);
}