
#include "io_expander.h"

IOExpander  ioexpander(0x18);
int pos = 90;

void setup(){
  Serial.begin(115200);

  ioexpander.begin();
  ioexpander.servoWrite(pos);

}

void loop(){
  for (int i = 0; i <= 180; i = i + (1)) {
    ioexpander.servoWrite(i);
    delay(0.1);
  }
  for (int j = 180; j >= 0; j = j + (-1)) {
    ioexpander.servoWrite(j);
    delay(0.1);
  }

}