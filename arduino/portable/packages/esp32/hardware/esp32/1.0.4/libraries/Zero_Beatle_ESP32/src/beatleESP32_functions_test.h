//#include "ZWHuskyLens.h"
#include "HUSKYLENS.h"

#include "PIDLoop.h"
#include "io_expander.h"
#include <ESP32_Servo.h>

Servo myservo;  // create servo object to control a servo
                // 16 servo objects can be created on the ESP32

int pos = 0;    // variable to store the servo position
// Recommended PWM GPIO pins on the ESP32 include 2,4,12-19,21-23,25-27,32-33 
extern int servoPin = 2;




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
HUSKYLENS huskylens;
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
    myservo.write(angle);

  }
}

void servoTrackingOnly(int ID1, bool facerecog=true) {
  int32_t error;
  int32_t panOffset;
  if (!huskylens.request()) {
    Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection!"));
    //    ScanForTargetServoOnly();
  }
  else if (!huskylens.isLearned()) {
    Serial.println(F("Nothing learned, press learn button on HUSKYLENS to learn one!"));
    ScanForTargetServoOnly();
  }
  else if (!huskylens.available()) {
    Serial.println(F("No block or arrow appears on the screen!"));
    ScanForTargetServoOnly();
  }
  else
  {
    Serial.println(F("###########"));
    //    while (huskylens.available())
    {
      HUSKYLENSResult result = huskylens.read();
      printResult(result);
      panOffset = (int32_t)160 - (int32_t)result.xCenter;


      // update loops
      panLoop.update(panOffset);
      angle = map(panLoop.m_command, 0, 1000, 0, 180);
      ioexpander.servoWrite(angle);
      myservo.write(angle);
    }
  }
}