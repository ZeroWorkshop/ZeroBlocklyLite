#include <Beatle.h>

Beatle beatle;

int speed = 128;

unsigned int sensor_values[7];

void setup()
{
  // uncomment if necessary to correct motor directions
  Serial.begin(115200);
  //beatle.motors.flipLeftMotor(true); 
  
  beatle.StartProgram();
  pinMode(DSL,INPUT);
  pinMode(DSR,INPUT);
  beatle .led.colorAll(beatle.led.strip.Color(0,255,0));
  delay(100);
  beatle.LineSensors.init();
 
}

void loop()
{
  if (beatle.button.isPressed())
  {
    // if button is pressed, stop and wait for another press to go again
    beatle.motors.setSpeeds(0, 0);
    beatle.button.waitForRelease();
    beatle.waitForButtonAndCountDown();
  }
	 
	 beatle.LineSensors.read(sensor_values);
	 
  
   for(int i = 0; i<7; i++)
   {
    Serial.print(sensor_values[i]);Serial.print("\t");
   }
   Serial.println();
        

  if (sensor_values[0]>1500 )
  {
    // if leftmost sensor detects line, reverse and turn to the right
    beatle.motors.setSpeeds(-speed, -speed);
    delay(200);
    beatle.motors.setSpeeds(speed, -speed);
    delay(300);
    beatle.motors.setSpeeds(speed, speed);
  }
  else if (sensor_values[6]>1500)
  {
    // if rightmost sensor detects line, reverse and turn to the left
    beatle.motors.setSpeeds(-speed, -speed);
    delay(200);
    beatle.motors.setSpeeds(-speed, speed);
    delay(300);
    beatle.motors.setSpeeds(speed, speed);
  }
  else
  {
    // otherwise, go straight
    beatle.motors.setSpeeds(speed, speed);
  }
}
