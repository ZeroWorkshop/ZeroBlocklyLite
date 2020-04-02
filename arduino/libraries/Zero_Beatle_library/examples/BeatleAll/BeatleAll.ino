#include <Beatle.h>

/**********************************************************
*   program_idx = 0   load all program and select the program with START Button
*   program_idx = 1   only load the first program  -- AovidObstacle
*   program_idx = 2   only load the first program  -- BorderDetect
*   program_idx = 3   only load the first program  -- FollowLine
*   program_idx = 4   only load the first program  -- MazeSolver
*   program_idx = 5   only load the first program  -- Sumo
*   program_idx = 6   only load the first program  -- RemoteControlCar  (need to add rf contorl broad or Bluetooth broad)
*   program_idx = 7   only load the first program  -- Wandering
*   program_idx = ...   coming soon
*
*******************************************************************/
#define program_idx  0

//Define the class 
Beatle beatle;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
   //beatle.motors.flipLeftMotor(true);
  beatle.StartProgram(); 
  beatle.SetupAll(program_idx);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  beatle.LoopAll(program_idx);
}  
