
#include <Wire.h>
#include <SoftwareSerial.h>
#include  "StarterPro.h"
#include <ZeroMotors.h>
#include <Pushbutton.h>

ZeroMotors motors;
Pushbutton button(ZERO_BUTTON);

void setup() {
  // put your setup code here, to run once:
   Serial.begin(115200);
   button.waitForButton();  // need to press start button   
}
void loop() {


if ( _ButtonUp)
  {
    motors.forward(255);
  }
  else if( _ButtonDown)
  {
   motors.backward(255);
  }
  else if(_ButtonLeft)
  {
    motors.turnLeft();
  }
  else if(_ButtonRight)
  {
     motors.turnRight();
  }
  else
 {
    motors.stop();
 }
  
}