#include <Wire.h>
#include "StarterPro.h"
#include <ZeroMotors.h>
#include <Pushbutton.h>

ZeroMotors motors;
Pushbutton START(ZERO_BUTTON);

#define        time_interval   200

void setup()
{                       
  //playStart();       
  pinMode(ZW_A1,INPUT);
  pinMode(ZW_A2,INPUT);
  pinMode(ZW_A3,INPUT);
  pinMode(ZW_A4,INPUT);
  pinMode(ZW_B1,OUTPUT);
  pinMode(ZW_B2,OUTPUT);
  pinMode(ZW_B3,OUTPUT);
  pinMode(ZW_B4,OUTPUT);
  digitalWrite(ZW_B1,LOW);
  digitalWrite(ZW_B2,LOW);
  digitalWrite(ZW_B3,LOW);
  digitalWrite(ZW_B4,LOW);
  motors.motorControl(M3,0);
  motors.motorControl(M4,0);
  motors.motorControl(M3,0);
  motors.motorControl(M4,0);
  Serial.begin(115200);
  START.waitForButton();
}

void loop()
{
  // run left motor forward 
     digitalWrite(ZW_B1,HIGH);
     digitalWrite(ZW_B2,HIGH);
     digitalWrite(ZW_B3,HIGH);
     digitalWrite(ZW_B4,HIGH);
     delay(time_interval);
     digitalWrite(ZW_B1,LOW);
     digitalWrite(ZW_B2,LOW);
     digitalWrite(ZW_B3,LOW);
     digitalWrite(ZW_B4,LOW);
     delay(time_interval); 
}