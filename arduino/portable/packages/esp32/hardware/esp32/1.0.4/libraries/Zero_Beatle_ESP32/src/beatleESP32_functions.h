/**
 * \par Copyright (C), 206, Zeroworkshop
 * \class   StarterProI2C
 * \brief   Driver for Starter Pro module.
 * @file    StarterProI2C.h
 * @author  Zeroworkshop
 * @version V1.0.0
 * @date    2019/05/8
 * @brief   Header for StarterProI2C.cpp module
 *
 * \par Copyright
 * This software is Copyright (C), 2016-2019, Zeroworkshop. Use is subject to license \n
 * conditions. The main licensing options available are GPL V2 or Commercial: \n
 *
 * \par Open Source Licensing GPL V2
 * This is the appropriate option if you want to share the source code of your \n
 * application with everyone you distribute it to, and you also want to give them \n
 * the right to share who uses it. If you wish to use this software under Open \n
 * Source Licensing, you must contribute all your source code to the open source \n
 * community in accordance with the GPL Version 2 when your application is \n
 * distributed. See http://www.gnu.org/copyleft/gpl.html
 *
*/
#ifndef _BEATLEESP32_FUNCTIONS_H_
#define _BEATLEESP32_FUNCTIONS_H_

#include "HUSKYLENS.h"
#include "chinese.c"

#include "PIDLoop.h"
#include "io_expander.h"
#include <BeatleSerial.h>
#include "NextionSimple.h"

#define ZUMO_FAST        255
#define mappingSCALE     255 / 400

#define CAM_PAN_MIDDLE 500
#define PAN_RANGE 300
#define PAN_SEARCH_RANGE 1000

HUSKYLENS huskylens;
IOExpander  ioexpander(0x18);
BeatleSerial bSerial;

extern int32_t speedP, speedI, speedD;
extern int32_t servoP, servoI, servoD;

#define nextion Serial2
NextionSimple myNextion(nextion, 9600); 
String message;
char* cmd;
char str1[50];
char str2[50];

//PIDLoop headingLoop(1500, 0, 0, false);
//PIDLoop linetrackingLoop(2500, 0, 0, false);
//PIDLoop panLoop(100, 0, 0, true);
PIDLoop headingLoop(speedP, speedI, speedD, false);
PIDLoop linetrackingLoop(speedP, speedI, speedD, false);
PIDLoop panLoop(servoP, servoI, servoD, true);

double angle;
int left = 0, right = 0;
int left_temp, right_temp;
uint32_t lastMove = 0;
int scanIncrement = (PAN_SEARCH_RANGE) / 50;

extern int32_t size;
extern HUSKYLENS huskylens;
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

void ScanForTarget()
{

  char buf[32];


  if (millis() - lastMove > 100)
  {


    lastMove = millis();
    panLoop.m_command += scanIncrement;

    if ((panLoop.m_command >= CAM_PAN_MIDDLE + PAN_SEARCH_RANGE / 2) || (panLoop.m_command <= CAM_PAN_MIDDLE - PAN_SEARCH_RANGE / 2))
    {

       scanIncrement   = -scanIncrement;

      if (scanIncrement < 0)
      {
       bSerial.setSpeeds(-200 * mappingSCALE, 200 * mappingSCALE);

      }
      else
      {
        bSerial.setSpeeds(150 * mappingSCALE, -150 * mappingSCALE);
      }
      delay(random(100, 200));
    }

    angle = map(panLoop.m_command, 0, 1000, 0, 180);
    ioexpander.servoWrite(angle);
  }
}

void ScanForTargetServoOnly()
{

  char buf[32];


  if (millis() - lastMove > 100)
  {


    lastMove = millis();
    panLoop.m_command += scanIncrement;

    if ((panLoop.m_command >= CAM_PAN_MIDDLE + PAN_SEARCH_RANGE / 2) || (panLoop.m_command <= CAM_PAN_MIDDLE - PAN_SEARCH_RANGE / 2))
    {

       scanIncrement   = -scanIncrement;


      //delay(random(100, 200));
    }

    angle = map(panLoop.m_command, 0, 1000, 0, 180);
    ioexpander.servoWrite(angle);
  }
}
void FollowLargeTarget(HUSKYLENSResult result)
{
  int32_t followError = PIXY_RCS_CENTER_POS - panLoop.m_command;  // How far off-center are we looking now?

  // Size is the area of the object.
  // We keep a running average of the last 8.
  size += result.width * result.height;
  size -= size >> 3;



  // Forward speed decreases as we approach the object (size is larger)
  int forwardSpeed = constrain(51200 - (size / 128), -100, 400);


  // Steering differential is proportional to the error times the forward speed
  int32_t differential = (followError + (followError * forwardSpeed)) >> 8;

  // Adjust the left and right speeds by the steering differential.
  left = constrain(forwardSpeed + 1.2 * differential, -400, 400);
  right = constrain(forwardSpeed - 1.2 * differential, -400, 400);

  // And set the motor speeds
  //  setLeftSpeed(leftSpeed);
  //  setRightSpeed(rightSpeed);
  bSerial.setSpeeds(left, right);
}

void FollowTarget(HUSKYLENSResult result)
{
  int32_t followError = PIXY_RCS_CENTER_POS - panLoop.m_command;  // How far off-center are we looking now?

  // Size is the area of the object.
  // We keep a running average of the last 8.
  size += result.width * result.height;
  size -= size >> 3;



  // Forward speed decreases as we approach the object (size is larger)
  int forwardSpeed = constrain(400 - (size / 128), -100, 400);


  // Steering differential is proportional to the error times the forward speed
  int32_t differential = (followError + (followError * forwardSpeed)) >> 8;

  // Adjust the left and right speeds by the steering differential.
  left = constrain(forwardSpeed + 1.2 * differential, -400, 400);
  right = constrain(forwardSpeed - 1.2 * differential, -400, 400);

  // And set the motor speeds
  //  setLeftSpeed(leftSpeed);
  //  setRightSpeed(rightSpeed);
  bSerial.setSpeeds(left, right);
}

void FollowTarget_TargetInCenter()
{
  uint16_t block_seen;
  uint32_t lastBlockTime1 = 0;
  int32_t panOffset;


  lastBlockTime1 = millis();
  while (panLoop.m_command < CAM_PAN_MIDDLE - PAN_RANGE / 2 || panLoop.m_command > CAM_PAN_MIDDLE + PAN_RANGE / 2) {

    if (millis() - lastBlockTime1 > 100)
      break;


    if (huskylens.request(ID1)) {
      HUSKYLENSResult result = huskylens.read();
      printResult(result);

      // calculate pan "errors" with respect to ID1,
      panOffset = (int32_t)160 - (int32_t)result.xCenter;


      // update loops
      panLoop.update(panOffset);
      angle = map(panLoop.m_command, 0, 1000, 0, 180);
      ioexpander.servoWrite(angle);

      if (panLoop.m_command > CAM_PAN_MIDDLE + PAN_RANGE / 2 ) { //used to be 650
        //beatle.motors.setSpeeds(0, 200 * mappingSCALE);
        bSerial.setSpeeds(0, 200 * mappingSCALE);
        delay(1);
      }
      else if (panLoop.m_command < CAM_PAN_MIDDLE - PAN_RANGE / 2) {  //used to be 500
        //beatle.motors.setSpeeds(200 * mappingSCALE, 0);
        bSerial.setSpeeds(200 * mappingSCALE, 0);
        delay(1);
      }

    }
  }

  if (panLoop.m_command > CAM_PAN_MIDDLE - PAN_RANGE / 2 && panLoop.m_command < CAM_PAN_MIDDLE + PAN_RANGE / 2) { //used to be 500~650
    //beatle.motors.setSpeeds(250 * mappingSCALE, 250 * mappingSCALE);
    bSerial.setSpeeds(250 * mappingSCALE, 250 * mappingSCALE);
    delay(0.5);
  }

}
void follower_setup(protocolAlgorithm algorithmType) {
  ioexpander.begin();
  ioexpander.servoWrite(90);
  Serial.begin(115200);
  bSerial.begin(Serial);

  Wire.begin();
  while (!huskylens.begin(Wire))
  {
    delay(100);
  }
  huskylens.writeAlgorithm(algorithmType); //Switch the algorithm to line tracking.
  
  myNextion.init(); // send the initialization commands for Page 0
  
  while (message != "65 0 2 0 ff ff ff") {
    message = myNextion.listen();
    if (message != "") { // if a message is received...
      ;
      //      Serial.println(message); //...print it out
    }
  }
  sprintf(str1, "%s", str_2);
  myNextion.setComponentText("t0", str1);
  
}
void follower(HUSKYLENS huskylens, int ID1, bool followLargTarget=false) {
  int32_t error;
  int32_t panOffset;


  if (!huskylens.request(ID1)) {
  	sprintf(str1, "%s", str_0);
    myNextion.setComponentText("t0", str1);
    left = 0;
    right = 0;
    //ScanForTarget();

  }
  else if (!huskylens.isLearned()) {
  	sprintf(str1, "%s", str_3);
    myNextion.setComponentText("t0", str1);
    left = 0;
    right = 0;
    //ScanForTarget();

  }
  else if (!huskylens.available()) {
  	sprintf(str1, "%s", str_4);
    myNextion.setComponentText("t0", str1);
    left = 0;
    right = 0;
    ScanForTarget();

  }
  else
  {
  	sprintf(str1, "%s", str_1);
    myNextion.setComponentText("t0", str1);
    HUSKYLENSResult result = huskylens.read();
    printResult(result);


    // calculate pan "errors" with respect to ID1,
    panOffset = (int32_t)160 - (int32_t)result.xCenter;


    // update loops
    panLoop.update(panOffset);
    angle = map(panLoop.m_command, 0, 1000, 0, 180);
    ioexpander.servoWrite(angle);
    
    if (followLargTarget)
    	FollowLargeTarget(result);
    else
    	FollowTarget(result);
    	
    FollowTarget_TargetInCenter();
  }

  /*if (sel == 0) {  //color follower
  	if (bSerial.lineSensors() == (beatleCMD::ALLBLACK)) {  //find a horizontal black line
  		sprintf(str1, "%s", str_9);
      myNextion.setComponentText("t0", str1);
  		left = 0;
      right = 0;
  	}
  }*/
  	

  bSerial.setSpeeds(left, right);
}

void lineTracking(HUSKYLENS huskylens, int ID1) {
  int32_t error;
  if (!huskylens.request(ID1)) {
    left = 0;
    right = 0;
  }
  else if (!huskylens.isLearned()) {
    left = 0;
    right = 0;
  }
  else if (!huskylens.available()) {
    left = right_temp;
    right = left_temp;
  }
  else
  {
    HUSKYLENSResult result = huskylens.read();
    printResult(result);
    lastXOrigin = (int32_t)result.xOrigin;
    lastXTarget = (int32_t)result.xTarget;
    // Calculate the error:
    error = (int32_t)result.xTarget - (int32_t)160;

    // Perform PID algorithm.
    linetrackingLoop.update(error);

    // separate heading into left and right wheel velocities.
    left = linetrackingLoop.m_command;
    right = -linetrackingLoop.m_command;

    left += ZUMO_FAST;
    right += ZUMO_FAST;
    left_temp = left;
    right_temp = right;
  }

  bSerial.setSpeeds(left, right);
}


void servoTrackingOnly(HUSKYLENS huskylens, int ID1, bool facerecog=true) {
  int32_t error;
  int32_t panOffset;


  if (!huskylens.request(ID1)) {
  	if (facerecog) {
  		sprintf(str1, "%s", str_5);
      myNextion.setComponentText("t0", str1);
  	}
  	else {
  	  sprintf(str1, "%s", str_0);
      myNextion.setComponentText("t0", str1);
    }
    left = 0;
    right = 0;
    //ScanForTarget();

  }
  else if (!huskylens.isLearned()) {
  	if (facerecog) {
  		sprintf(str1, "%s", str_6);
      myNextion.setComponentText("t0", str1);
  	}
  	else {
  	  sprintf(str1, "%s", str_3);
      myNextion.setComponentText("t0", str1);
    } 
    left = 0;
    right = 0;
    //ScanForTarget();

  }
  else if (!huskylens.available()) {
  	if (facerecog) {
  		sprintf(str1, "%s", str_7);
      myNextion.setComponentText("t0", str1);
  	}
  	else {
  	  sprintf(str1, "%s", str_4);
      myNextion.setComponentText("t0", str1);
    }
    left = 0;
    right = 0;
    ScanForTargetServoOnly();

  }
  else
  {
  	if (facerecog) {
  		sprintf(str1, "%s", str_8);
      myNextion.setComponentText("t0", str1);
  	}
  	else {
  	  sprintf(str1, "%s", str_1);
      myNextion.setComponentText("t0", str1);
    }
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



  bSerial.setSpeeds(left, right);
}

void combo_setup() {
  //ioexpander.begin();
  //ioexpander.servoWrite(90);
  //Serial.begin(115200);
  //bSerial.begin(Serial);
  //bSerial.setSpeeds(0, 0);
  
  ioexpander.begin();
  ioexpander.servoWrite(90);
  Serial.begin(115200);
  bSerial.begin(Serial);
  bSerial.setSpeeds(0, 0);
  /*
  Wire.begin();
  while (!huskylens.begin(Wire))
  {
    delay(100);
  }
  huskylens.writeAlgorithm(algorithmType); //Switch the algorithm to line tracking.
  */
  myNextion.init(); // send the initialization commands for Page 0
  
  cmd = "page 2";
  myNextion.sendCommand(cmd);
  char *cmp_str = "65 2";
  while (strstr(message.c_str(), cmp_str) == NULL) {
    message = myNextion.listen();
  }

  if (message == "65 2 2 0 ff ff ff") {
    sel = 0;
  }
  else if (message == "65 2 3 0 ff ff ff") {
    sel = 1;
  }
  else if (message == "65 2 4 0 ff ff ff") {
    sel = 2;
  }
  else if (message == "65 2 5 0 ff ff ff") {
    sel = 3;
  }
  else if (message == "65 2 6 0 ff ff ff") {
    sel = 4;
  }
  else if (message == "65 2 7 0 ff ff ff") {
    sel = 5;
  }

  cmd = "page 0";
  myNextion.sendCommand(cmd);
  switch (sel) {
    case 0:
      servoP = 100, servoI = 0, servoD = 0;
      follower_setup(ALGORITHM_COLOR_RECOGNITION);
      break;

    case 1:
      servoP = 50, servoI = 0, servoD = 50;
      follower_setup(ALGORITHM_OBJECT_TRACKING);
      break;

    case 2:
      servoP = 50, servoI = 0, servoD = 50;
      follower_setup(ALGORITHM_OBJECT_RECOGNITION);
      break;

    case 3:
      follower_setup(ALGORITHM_LINE_TRACKING);
      break;

    case 4:
      servoP = 200, servoI = 0, servoD = 0;
      follower_setup(ALGORITHM_FACE_RECOGNITION);
      break;

    case 6:
      servoP = 150, servoI = 0, servoD = 50;
      follower_setup(ALGORITHM_TAG_RECOGNITION);
      break;
  }
}

void combo() {
	if (sel == 2)
    follower(huskylens, ID1, true);
  else if (sel == 3)
    lineTracking(huskylens, ID1);
  else if (sel == 4)
    servoTrackingOnly(huskylens, ID1);
  else if (sel == 5)
    servoTrackingOnly(huskylens, ID1, false);
  else
    follower(huskylens, ID1);
}
#endif






