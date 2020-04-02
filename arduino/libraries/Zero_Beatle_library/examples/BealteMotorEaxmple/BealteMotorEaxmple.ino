#include <Beatle.h>

Beatle beatle;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  beatle.motors.flipLeftMotor(true);
  beatle.led.colorAll(beatle.led.Color(255,0,0));
  delay(1000);
  
  beatle.StartProgram();
  beatle.led.colorAll(beatle.led.Color(0,0,0));
  delay(100);
}

void loop() {
  // put your main code here, to run repeatedly:
  beatle.led.OneLED_RGB(0,beatle.led.Color(255,0,0));
  for (int speed = 0; speed <= 255; speed++)
  {
    beatle.motors.setLeftSpeed(speed);
    delay(2);
  }

  for (int speed = 255; speed >= 0; speed--)
  {
    beatle.motors.setLeftSpeed(speed);
    delay(2);
  }

  // run left motor backward

 beatle.led.OneLED_RGB(0,beatle.led.Color(0,0,0));
 beatle.led.OneLED_RGB(11,beatle.led.Color(255,0,0));
 

  for (int speed = 0; speed >= -255; speed--)
  {
    beatle.motors.setLeftSpeed(speed);
    delay(2);
  }

  for (int speed = -255; speed <= 0; speed++)
  {
    beatle.motors.setLeftSpeed(speed);
    delay(2);
  }

  // run right motor forward

  beatle.led.OneLED_RGB(11,beatle.led.Color(0,0,0));
  beatle.led.OneLED_RGB(5,beatle.led.Color(255,0,0));
  for (int speed = 0; speed <= 255; speed++)
  {
    beatle.motors.setRightSpeed(speed);
    delay(2);
  }

  for (int speed = 255; speed >= 0; speed--)
  {
    beatle.motors.setRightSpeed(speed);
    delay(2);
  }

  // run right motor backward

  
  beatle.led.OneLED_RGB(5,beatle.led.Color(0,0,0));
  beatle.led.OneLED_RGB(6,beatle.led.Color(255,0,0));
  for (int speed = 0; speed >= -255; speed--)
  {
    beatle.motors.setRightSpeed(speed);
    delay(2);
  }

  for (int speed = -255; speed <= 0; speed++)
  {
    beatle.motors.setRightSpeed(speed);
    delay(2);
  }
  beatle.led.OneLED_RGB(6,beatle.led.Color(0,0,0));
  delay(500);
}
