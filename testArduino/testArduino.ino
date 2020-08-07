
#include <ESP32_Servo.h>

Servo servo_0;

void setup(){
  pinMode(0, OUTPUT);
  servo_0.attach(0,500,2500);
}

void loop(){
  digitalWrite(0,HIGH);

  do{
    servo_0.write(0);
    delay(0);
  }while(true);

}