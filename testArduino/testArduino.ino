
#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;
unsigned long timer = 0;
float timeStep = 0.01;
float pitch = 0;
float roll = 0;
float yaw = 0;

void setup(){
  Serial.begin(115200);
  Serial.begin(115200);
  Serial.println("Initialize MPU6050");
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
      Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
      delay(500);
  }

  mpu.calibrateGyro();
  mpu.setThreshold(3);

}

void loop(){
  timer = millis();
  Vector normAccel = mpu.readNormalizeAccel();
  Vector norm = mpu.readNormalizeGyro();

  pitch = pitch + norm.YAxis * timeStep;
  roll = roll + norm.XAxis * timeStep;
  yaw = yaw + norm.ZAxis * timeStep;
  Serial.print("pitch = ");
  Serial.print(pitch);
  Serial.print("roll = ");
  Serial.print(roll);
  Serial.print("yaw = ");
  Serial.println(yaw);
  delay((timeStep*1000) - (millis() - timer));

}