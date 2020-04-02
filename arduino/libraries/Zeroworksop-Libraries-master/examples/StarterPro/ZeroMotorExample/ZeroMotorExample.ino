#include <Wire.h>
#include <ZeroMotors.h>
#include <Pushbutton.h>
#include "Buzzer.h"

ZeroMotors motors;
Pushbutton button(ZERO_BUTTON);

void setup()
{                       
  playStart();       
  button.waitForButton();
}

void loop()
{
  // run left motor forward

  
  for (int speed = 0; speed <= 255; speed++)
  {
    motors.setLeftSpeed(speed);
    delay(2);
  }

  for (int speed = 255; speed >= 0; speed--)
  {
    motors.setLeftSpeed(speed);
    delay(2);
  }

  // run left motor backward  

  for (int speed = 0; speed >= -255; speed--)
  {
    motors.setLeftSpeed(speed);
    delay(2);
  }

  for (int speed = -255; speed <= 0; speed++)
  {
    motors.setLeftSpeed(speed);
    delay(2);
  }

  // run right motor forward

  for (int speed = 0; speed <= 255; speed++)
  {
    motors.setRightSpeed(speed);
    delay(2);
  }

  for (int speed = 255; speed >= 0; speed--)
  {
    motors.setRightSpeed(speed);
    delay(2);
  }

  // run right motor backward

  for (int speed = 0; speed >= -255; speed--)
  {
    motors.setRightSpeed(speed);
    delay(2);
  }

  for (int speed = -255; speed <= 0; speed++)
  {
    motors.setRightSpeed(speed);
    delay(2);
  }

  delay(500);
}
