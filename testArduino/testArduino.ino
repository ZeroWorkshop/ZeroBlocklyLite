#include <Beatle.h>

Beatle beatle;

void setup(){
  Serial.begin(115200);

  beatle.StartProgram();

  beatle.SetupAll(0);

}

void loop(){
  beatle.LoopAll(0);

}