#include <Beatle.h>

Beatle beatle;

int speed = 128;

void setup() {
  // put your setup code here, to run once:
	Serial.begin(115200);
  beatle.StartProgram();
  
  pinMode(DSL,INPUT);
  pinMode(DSR,INPUT);
    
 
}

void loop() {
  // put your main code here, to run repeatedly:
	int LeftValue,RightValue;
  LeftValue = digitalRead(DSL);
  RightValue = digitalRead(DSR);

  //beatle.theaterChaseRainbow(5);
  beatle.led.rainbow_stream(2);
  if((LeftValue == 0) && (RightValue == 0))
  {  
     beatle.motors.setSpeeds(-speed, -speed);
     delay(300);
     beatle.motors.setSpeeds(speed, -speed);
     delay(200);
  }
  else if(LeftValue == 0)
  {    
    beatle.motors.setSpeeds(speed, -speed);
    delay(200);
  }
  else if(RightValue == 0)
  {
    beatle.motors.setSpeeds(-speed, speed);
    delay(200);
  }
  else
  {
    beatle.motors.setSpeeds(speed, speed);
  }
  
}

