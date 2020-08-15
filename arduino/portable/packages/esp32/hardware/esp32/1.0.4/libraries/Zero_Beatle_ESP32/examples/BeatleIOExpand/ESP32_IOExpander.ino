#include "io_expander.h"
IOExpander  ioexpander(0x09);
void setup() {
  // put your setup code here, to run once:
    ioexpander.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
   ioexpander.digitalWrite(3,HIGH);
   delay(500);
   ioexpander.digitalWrite(3,LOW);
   delay(500);

   ioexpander.servoWrite(0);
   delay(1000);
   ioexpander.servoWrite(90);
   delay(1000);
   ioexpander.servoWrite(180);
   delay(1000);
}
