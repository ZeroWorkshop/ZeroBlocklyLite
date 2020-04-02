                                                                              /*
 * This example uses the ZumoMotors library to drive each motor on the Zumo
 * forward, then backward. The yellow user LED is on when a motor should be
 * running forward and off when a motor should be running backward. If a
 * motor on your Zumo has been flipped, you can correct its direction by
 * uncommenting the call to flipLeftMotor() or flipRightMotor() in the setup()
 * function.
 */

#include <Wire.h>
#include <ZeroMotors.h>
#include <Pushbutton.h>
#include "Buzzer.h"

ZeroMotors motors;
Pushbutton button(ZERO_BUTTON);
const int speed = 200;

void setup()
{    
    Serial.begin(115200);
    playStart();                            
    button.waitForButton();
}

void loop()
{
  motors.forward(200);
  delay(1000);
  motors.backward(200);
  delay(1000);
  motors.turnRight(200);
  delay(1000);
  motors.turnLeft(200);
  delay(1000);
}