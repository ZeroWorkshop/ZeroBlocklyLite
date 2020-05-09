#include <Beatle.h>


Beatle beatle; 

//Set the maxvalue and minvalue of the LineSensors.
unsigned int max_value[] = {2000,2000,2000,1000,2000,2000,2000};
unsigned int min_value[] = {800, 450, 500, 400, 450, 450, 800};

void setup()
{
   Serial.begin(115200);
  //beatle.motors.flipLeftMotor(true);
  beatle.StartProgram();
  beatle.led.colorAll(beatle.led.strip.Color(255,255,0));
  delay(500);  
  beatle.LineSensorCalibration(true,128, 20);
  beatle.button.waitForButton(); 
   // Play music and wait for it to finish before we start driving.
  beatle.buzzer.play("L16 cdegreg4");
  while(beatle.buzzer.isPlaying());  
 
}

void loop()
{
   beatle.solveMaze();
   delay(200);

  // Sound off buzzer to denote Zumo has solved the maze
  beatle.buzzer.play(">>a32");
  

  // The maze has been solved. When the user
  // places the Zumo at the starting line
  // and pushes the Zumo button, the Zumo
  // knows where the finish line is and
  // will automatically navigate.
  while(1)
  {
    beatle.button.waitForButton();

    beatle.goToFinishLine();
    // Sound off buzzer to denote Zumo is at the finish line.
    beatle.buzzer.play(">>a32");
  }
  
   
}
