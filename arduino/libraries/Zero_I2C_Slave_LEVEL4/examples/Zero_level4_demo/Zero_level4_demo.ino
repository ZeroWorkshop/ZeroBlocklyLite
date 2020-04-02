#include "Zero_I2C_Slave_LEVEL4.h"
#include <Wire.h>

int PS2_Button_Read[6];
int ProgramSelected;

void setup()
{
    Serial.begin(115200);        //start serial for output
    LEVEL4.init();
    LEVEL4.StartProgram(&ProgramSelected);
    LEVEL4.setMotor("M2","M4","M1","M3"); //comment this line, with set default connection as:  M1 -- LeftFront  M2 -- LeftRear   M3-- RightFront  M4 -- RightRear 
}

void loop()
{  

 LEVEL4.PS2_RF_ReadButton(PS2_Button_Read);
  if (ButtonUp) {
    LEVEL4.goForward(100); //set the speed to 100, the range is from 0 to 255
    //LEVEL4.goForward();  //without parameter, it will run with full speed
  }
  else if (ButtonDown) {
    LEVEL4.goReverse(100);
  }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
  else if (ButtonLeft) {
    LEVEL4.goLeftTurn(100);
  }
   else if (ButtonRight) {
    LEVEL4.goRightTurn(100);
  }
  else {
    LEVEL4.goBrake();
  }

  delay(10);
}
/*********************************************************************************************************
 * END FILE
 *********************************************************************************************************/
