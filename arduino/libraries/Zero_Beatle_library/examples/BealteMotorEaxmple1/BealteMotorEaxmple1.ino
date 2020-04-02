#include <Beatle.h>

Beatle beatle;

int speed = 200;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  beatle.motors.flipLeftMotor(true);
  beatle.StartProgram();
}

void loop() {
  // put your main code here, to run repeatedly:
  //Forward and set the background color to red
  beatle.led.colorAll(beatle.led.Color(255,0,0));
  
  beatle.motors.setSpeeds(speed,speed);
  delay(1000);
  
  //Turn Left and set the background color to gree
  beatle.led.colorAll(beatle.led.Color(0,255,0));
  beatle.motors.setSpeeds(-speed,speed);
  delay(1000);

  //Turn Right and set the background color to blue
  beatle.led.colorAll(beatle.led.Color(0,0,255));
  beatle.motors.setSpeeds(speed,-speed);
  delay(1000);

  //Backward  and set the background color to yellow
  beatle.led.colorAll(beatle.led.Color(255,255,0));
  beatle.motors.setSpeeds(-speed,-speed);
  delay(1000);
  
  
}
