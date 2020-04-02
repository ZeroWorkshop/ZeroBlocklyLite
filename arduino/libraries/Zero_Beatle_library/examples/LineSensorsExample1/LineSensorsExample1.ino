#include <Beatle.h>
Beatle beatle;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  beatle.StartProgram();
  beatle.LineSensors.init();
  
}

void loop() {
  // put your main code here, to run repeatedly:
 unsigned int sensors[7];
 //unsigned int *sensors;
 //sensors = beatle.LineSensors.read(); 
 //Serial.println("********");
 beatle.LineSensors.read(sensors);
 for(int i = 0; i<7;i++)
 {
  //Serial.print(*(sensors+i));
  Serial.print(sensors[i]);
  Serial.print("\t");
  }
  Serial.println();
}