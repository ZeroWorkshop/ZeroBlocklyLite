#include "ZWHuskyLens.h"


#include "PIDLoop.h"
#include "io_expander.h"




#define CAM_PAN_MIDDLE 500
#define PAN_RANGE 300
#define PAN_SEARCH_RANGE 1000


IOExpander  ioexpander(0x18);


extern int32_t speedP, speedI, speedD;
extern int32_t servoP, servoI, servoD;


PIDLoop panLoop(servoP, servoI, servoD, true);

double angle;
int left = 0, right = 0;
int left_temp, right_temp;
uint32_t lastMove = 0;
int scanIncrement = (PAN_SEARCH_RANGE) / 50;

extern int32_t size;
extern ZWHuskyLens huskylens;
extern int ID1;
int32_t lastXOrigin = 0;
int32_t lastXTarget = 0;

int sel;
void printResult(HUSKYLENSResult result) {
  if (result.command == COMMAND_RETURN_BLOCK) {
    Serial.println(String() + F("Block:xCenter=") + result.xCenter + F(",yCenter=") + result.yCenter + F(",width=") + result.width + F(",height=") + result.height + F(",ID=") + result.ID);
  }
  else if (result.command == COMMAND_RETURN_ARROW) {
    Serial.println(String() + F("Arrow:xOrigin=") + result.xOrigin + F(",yOrigin=") + result.yOrigin + F(",xTarget=") + result.xTarget + F(",yTarget=") + result.yTarget + F(",ID=") + result.ID);
  }
  else {
    Serial.println("Object unknown!");
  }
}



void ScanForTargetServoOnly()
{

  


  if (millis() - lastMove > 100)
  {


    lastMove = millis();
    panLoop.m_command += scanIncrement;

    if ((panLoop.m_command >= CAM_PAN_MIDDLE + PAN_SEARCH_RANGE / 2) || (panLoop.m_command <= CAM_PAN_MIDDLE - PAN_SEARCH_RANGE / 2))
    {

       scanIncrement   = -scanIncrement;


      delay(random(100, 200));
    }

    angle = map(panLoop.m_command, 0, 1000, 5, 175);
    Serial.print("Servo angle = ");Serial.println(angle);
    ioexpander.servoWrite(angle);
    
  }
}



void servoTrackingOnly(HUSKYLENS huskylens, int ID1, bool facerecog=true) {
  int32_t error;
  int32_t panOffset;


  
  if (!huskylens.request(ID1)) {
  	Serial.println("111111");
    ScanForTargetServoOnly();

  }
  else if (!huskylens.isLearned()) {
  	Serial.println("222222");
    ScanForTargetServoOnly();

  }
  else if (!huskylens.available()) {
  
  //if (!huskylens.request(ID1)) {
  	Serial.println("333333");
    ScanForTargetServoOnly();

  }
  else
  {
  	Serial.println("444444");
    HUSKYLENSResult result = huskylens.read();
    printResult(result);


    // calculate pan "errors" with respect to ID1,
    panOffset = (int32_t)160 - (int32_t)result.xCenter;


    // update loops
    panLoop.update(panOffset);
    angle = map(panLoop.m_command, 0, 1000, 0, 180);
    ioexpander.servoWrite(angle);
    
    left = 0;
    right = 0;
  }

}
