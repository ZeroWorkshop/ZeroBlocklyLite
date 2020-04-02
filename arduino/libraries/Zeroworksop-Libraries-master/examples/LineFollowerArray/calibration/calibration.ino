#include  "StarterPro.h"
//#include "LineFollowerArray.h"
//#include  "ZeroWorkshop_Macro_Definitions.h"
#include <Wire.h>
#include <SoftwareSerial.h>
#include <ZeroMotors.h>
#include <Pushbutton.h>

//LineFollowerArray  LineFollower(0x09);


int PS2_Button_Read[6];

extern int Rx_Buffer[6];

ZeroMotors motors;
Pushbutton button(ZERO_BUTTON);

void setup() {
  // put your setup code here, to run once:
  //LineFollower.begin();
  //LineFollower.setMaxVal(2000);
  Serial.begin(115200);
   button.waitForButton();
  
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