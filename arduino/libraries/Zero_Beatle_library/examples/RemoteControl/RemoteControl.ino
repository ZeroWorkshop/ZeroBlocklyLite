#include <Beatle.h>

Beatle beatle;


#define SPEED  255


void setup() {
  // put your setup code here, to run once:  
  Serial.begin(115200);
  beatle.motors.flipLeftMotor(true);
  beatle.StartProgram();
  

}

void loop() {
  // put your main code here, to run repeatedly:
    
	beatle.led.theaterChaseRainbow(5);
	if ( _ButtonUp)
  {
   	beatle.motors.setSpeeds(SPEED, SPEED);
  }
  else if( _ButtonDown)
  {
   	beatle.motors.setSpeeds(-SPEED, -SPEED);
  }
  else if(_ButtonLeft)
  {
    beatle.motors.setSpeeds(-SPEED, SPEED);    
  }
  else if(_ButtonRight)
  {
    beatle.motors.setSpeeds(SPEED, -SPEED);
  }
  else
 	{
    beatle.motors.setSpeeds(0, 0);
 	}
}


