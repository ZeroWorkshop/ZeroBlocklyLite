#include <Beatle.h>

volatile int position;
volatile int error;
volatile int lastError;
volatile int speedDifference;
volatile double kp;
volatile double kd;
volatile int MaxSpeed;
volatile int LeftSpeed;
volatile int RightSpeed;

Beatle beatle;

unsigned int max_value[] = {2000,2000,2000,1000,2000,2000,2000};
unsigned int min_value[] = {450,450,450,300,450,450,450};

unsigned int sensor_values[7];

void setup(){
  position = 0;
  error = 0;
  lastError = 0;
  speedDifference = 0;
  kp = 1/12.0;
  kd = 6.0;
  MaxSpeed = 128;
  LeftSpeed = 0;
  RightSpeed = 0;
  Serial.begin(115200);

  beatle.StartProgram();

  beatle.writeCalibrationData(max_value,min_value);

  //beatle.LineSensors.init();

}

void loop(){
  position = beatle.LineSensors.readLine(sensor_values);
  ;
  error = position - 3000;
  speedDifference = kp * error + kd * (error - lastError);
  lastError = error;
  LeftSpeed = MaxSpeed + speedDifference;
  RightSpeed = MaxSpeed - speedDifference;
  if (LeftSpeed < 0) {
    LeftSpeed = 0;

  }
  else if (LeftSpeed > MaxSpeed) {
    LeftSpeed = MaxSpeed;
  }
  if (RightSpeed < 0) {
    RightSpeed = 0;

  }
  else if (RightSpeed > MaxSpeed) {
    RightSpeed = MaxSpeed;
  }
  beatle.motors.setSpeeds(LeftSpeed, RightSpeed);

}