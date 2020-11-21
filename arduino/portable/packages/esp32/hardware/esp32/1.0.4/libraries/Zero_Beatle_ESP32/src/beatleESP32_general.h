#include "PIDLoop.h"
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
  uint8_t cmdBuffer[beatleCMD::STACK_SIZE];
  uint8_t tmp[beatleCMD::STACK_SIZE];
  uint8_t index = 0;
  uint8_t offset;
	int timer = millis();
	while (1) 
	{
		if (millis() - timer > timeout) return false;
	  while (Serial.available() < beatleCMD::STACK_SIZE);



  while (Serial.available()) {
    tempBuffer = Serial.read();
    cmdBuffer[index++] = tempBuffer;
  }

  for (uint8_t i = 0; i < beatleCMD::STACK_SIZE; i++) {
    if (cmdBuffer[i] == beatleCMD::SB &&
        cmdBuffer[(i + 1) > 9 ? (i - 9) : (i + 1)] == beatleCMD::VER &&
        cmdBuffer[(i + 2) > 9 ? (i - 8) : (i + 2)] == beatleCMD::LEN) {
      offset = i;
    }
  }

  for (uint8_t j = 0; j < beatleCMD::STACK_SIZE; j++) {
    tmp[j] = cmdBuffer[offset + j > 9 ? (offset + j - 10) : (offset + j)];
  }
  
  if (tmp[5] == 0xCC && tmp[6] == 0xDD) return true;
/*
  //while (!Serial.available()) {
  //  if (millis() - timer > timeout) return false;
  //}
  while (1) {
  	if (millis() - timer > timeout) return false;
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
  //return false;
}
*/
}
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