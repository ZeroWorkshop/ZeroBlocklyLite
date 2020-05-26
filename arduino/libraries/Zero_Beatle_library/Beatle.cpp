#include "Beatle.h"

// constructor (doesn't do anything)
Beatle::Beatle()
{	
	//path[100] = "";	 
	DEBUG           =  0;
	REVERSE_SPEED   =  128;// 0 is stopped, 255 is full speed
	TURN_SPEED      =  100;
 	FORWARD_SPEED   =  128;
 	SPEED           =  128;
	MAX_SPEED       =  170;
	REVERSE_DURATION=  200; // ms  //for border detect
	TURN_DURATION   =  300; // ms  /for border detect
	
	// SENSOR_THRESHOLD is a value to compare reflectance sensor
	// readings to to decide if the sensor is over a black line
	SENSOR_THRESHOLD =   500;
	
	AT_END_POINT - 0;
	
	_Kp = 1.0/8.0;
	_Kd = 6.0;
	_Ki = 0;
	
}


void Beatle::StartProgram()
{
	
	ProgramSelector= -1;
  buzzer.play(">g32>>c32");
  button.waitForButton(); 
  ProgramSelector= 0;
  buzzer.play("! V15 c");
  unsigned long time_start;
  time_start = millis();

  int idx = 1;
  while(millis() - time_start < 2000)
  {   
      if (button.getSingleDebouncedRelease())
      {
          ProgramSelector++;
          //Serial.print("count = "); Serial.println(count);
          switch( ProgramSelector%7)
          {
           case 0: buzzer.play("c");break;
           case 1: buzzer.play("d");break;
           case 2: buzzer.play("e");break;
           case 3: buzzer.play("f");break;
           case 4: buzzer.play("g");break;
           case 5: buzzer.play("a");break;
           case 6: buzzer.play("b");break;         
          }
           
          time_start = millis();
      }
      
    }   
   if(ProgramSelector== 0)
   {
    ProgramSelector= EEPROM.read(EEPROM_PROG_IDX_ADDRESS);
   }
   else
   {
    EEPROM.write(EEPROM_PROG_IDX_ADDRESS, ProgramSelector);
   
   }
    
   buzzer.play("L16 cdegreg4");
   while(buzzer.isPlaying());  
}

void Beatle::SetupAll(int idx)
{
	//ProgramSelector = idx;
	int select;

	if(idx == 0)
	{
		select = ProgramSelector;
	}
	else
	{
		select = idx;
	}
	switch(select)
   {
    case 1:
    	led.colorAll(led.Color(0xFF,0,0)); //red
  		delay(1000);
  		//led.rainbow_stream(20,&led.firstPixelHue);
      Setup_AvoidObstacle();
     break;
    case 2:
    	led.colorAll(led.Color(0xFF,0xA5,0)); //Orange
  		delay(1000);
  		//led.rainbow_stream(20,&led.firstPixelHue);
    	Setup_BorderDetect();
     break;
     case 3:
     	led.colorAll(led.Color(0xFF,0xFF,0)); //yellow
  		delay(1000);
  		//led.rainbow_stream(20,&led.firstPixelHue);
    Setup_FollowLine();
     break;
     case 4:
     	led.colorAll(led.Color(0x00,0xFF,0x00));  //green
  		delay(1000);
  		//led.colorAll(led.Color(0x00,0x0,0));  //green
  		//delay(1000);
  		//led.rainbow_stream(20,&led.firstPixelHue);
      Setup_MazeSolver();
     break;
     case 5:
     	led.colorAll(led.Color(0x00,0xFF,0xFF));  //cyan
  		delay(1000);
  		//led.rainbow_stream(20,&led.firstPixelHue);
      Setup_Sumo();
     break;
     case 6:
     	led.colorAll(led.Color(0,0,0xFF)); //Blue
  		delay(1000);
  		//led.rainbow_stream(20,&led.firstPixelHue);
      Setup_RemoteControl();
     break;
     case 7:
     	led.colorAll(led.Color(0x80,0x00,0x80));  //purple
  		delay(1000);
  		//led.rainbow_stream(20,&led.firstPixelHue);
      Setup_Wandering();
     	
   }
 	
}


void Beatle::Setup_Wandering()
{
	pinMode(DSL,INPUT);
	pinMode(DSR,INPUT);
	
	LineSensors.init();

}
void Beatle::Loop_Wandering()
{
		int idx;
		int move_time;
		int speed;
		int left_value,right_value;
		int border_detect = 0;
		int obstacle_detect = 0;
		
	  randomSeed(millis());

		idx = random(1,9);
		move_time = random(400,2000);
		speed = random(80,255);
		Serial.print("idx = ");Serial.println(idx);
		Serial.print("speed = ");Serial.println(speed);
		Serial.print("move_time = ");Serial.println(move_time);
	
		unsigned long time_startA;
		time_startA = millis();
		while(millis() - time_startA < move_time)
		{	
			left_value = digitalRead(DSL);
			right_value = digitalRead(DSR);
			
			LineSensors.read(sensor_values);
			//Serial.print(left_value); Serial.print("\t");Serial.print(right_value);Serial.print("\t");
			//for(int i = 0; i<7; i++)
		//	{
			//	Serial.print(sensor_values[i]); Serial.print("\t");
				
			//}
			
			//Serial.print("idx = "); Serial.println(idx);
			move_state = idx;
			if(left_value ==0 && right_value == 0)
			{
					move_state = BACKWARD;
			}
			else if(left_value == 0)
			{
					move_state = LEFT_BACK;
			}		
			else if (right_value == 0 )
			{
					move_state = RIGHT_BACK;
			}
			
			if(sensor_values[0]>1500 && sensor_values[6]>1500)
			{
					move_state = BACKWARD;
			}
			else if(sensor_values[0]>1500)
			{
					move_state = LEFT_BACK;
			}		
			else if (sensor_values[6]>1500 )
			{
					move_state = RIGHT_BACK;
			}
				
			//	Serial.print("move_state = "); Serial.println(move_state);
			
			switch(move_state)
			{	
				case FORWARD:
					motors.setSpeeds(speed,speed);
					break;		
				case FORWARD_LEFT:
					motors.setSpeeds(0,speed);
					break;
				case LEFT:
					motors.setSpeeds(-speed,speed);
					break;
				case FORWARD_RIGHT:
					motors.setSpeeds(speed,0);
					break;
				case RIGHT:
					motors.setSpeeds(speed,-speed);
					break;
				case LEFT_BACK:
					motors.setSpeeds(-speed,0);
					break;
				case BACKWARD:
					motors.setSpeeds(-speed,-speed);
					break;
				case RIGHT_BACK:
					motors.setSpeeds(0,-speed);
					break;
				case STOP:
					motors.setSpeeds(0,0);
					break;				
			}	
		
		}
		
}

void Beatle::LoopAll(int idx)
{
  int select;

	if(idx == 0)
	{
		select = ProgramSelector;
	}
	else
	{
		select = idx;
	}
	
	switch(select)
   {
    case 1:
     Loop_AvoidObstacle();
     break;
     case 2:
     Loop_BorderDetect();
     break;
     case 3:
     Loop_FollowLine();
     break;
     case 4:
     Loop_MazeSolver();
     break;
     case 5:
     Loop_Sumo();
     break;
     case 6:
     Loop_RemoteControl();
     break;
     case 7:
     Loop_Wandering();
     break;
   }
}

void Beatle::Setup_BorderDetect()
{
	//led.colorAll(led.Color(0,255,0));
	//delay(500);
	//led.colorAll(led.Color(0,255,0));
	SetForwardSpeed(128);
	SetTurnSpeed(128);
	SetReverseSpeed(128);
	SetReverseDuration(200); //200ms
	SetTurnDuration(300);    //300ms	
  pinMode(DSL,INPUT);
  pinMode(DSR,INPUT);
 
  delay(100);
  LineSensors.init();
  
}





void Beatle::waitForButtonAndCountDown()
{
  //digitalWrite(LED, HIGH);
  button.waitForButton();
 // digitalWrite(LED, LOW);

  // play audible countdown
  for (int i = 0; i < 3; i++)
  {
    delay(1000);
    buzzer.playNote(NOTE_G(3), 200, 15);
  }
  delay(1000);
  buzzer.playNote(NOTE_G(4), 500, 15);
  delay(1000);
}


void Beatle::Loop_BorderDetect()
{
	if (button.isPressed())
  {
    // if button is pressed, stop and wait for another press to go again
    motors.setSpeeds(0, 0);
    button.waitForRelease();
    waitForButtonAndCountDown();
  }
 
   //int position;
   unsigned int sensors[7];
   //position =  LineSensors.readLine(sensors);
	 LineSensors.read(sensors);


  if (sensors[0]>1500  )
  {
    // if leftmost sensor detects line, reverse and turn to the right
    motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
    delay(REVERSE_DURATION);
    motors.setSpeeds(TURN_SPEED, -TURN_SPEED);
    delay(TURN_DURATION);
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
  }
  else if (sensors[6]>1500 )
  {
    // if rightmost sensor detects line, reverse and turn to the left
    motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
    delay(REVERSE_DURATION);  
    motors.setSpeeds(-TURN_SPEED, TURN_SPEED);
    delay(TURN_DURATION);
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
  }
  else
  {
    // otherwise, go straight
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
  }
	
}


void Beatle::QTRC_ReadRawValue()
{
	unsigned int sensors[7];
	LineSensors.init();
	
	 LineSensors.read(sensors);
	 for(int i = 0; i<7; i++)
	 {
	 	Serial.print(sensors[i]);
	 	Serial.print("\t");	
	 }
	 Serial.println();

}

void Beatle::Setup_FollowLine()
{
	pinMode(DSL,INPUT);
	pinMode(DSR,INPUT);	
	LineSensorCalibration(true,128, 20); 
	SetPID(1.0/6.0,0,6.0);
  button.waitForButton(); 
  // Play music and wait for it to finish before we start driving.
  buzzer.play("L16 cdegreg4");
  while(buzzer.isPlaying());  
}

int Beatle::ABOVE_LINE(int value)
{	
	if(value > SENSOR_THRESHOLD)
		return 1;
	else
		return 0;
}


void Beatle::Setup_Sumo()
{
  
	pinMode(DSL,INPUT);
	pinMode(DSR,INPUT);	
	LineSensors.init();
	
	SetForwardSpeed(128);
	SetTurnSpeed(128);
	SetReverseSpeed(128);
	SetAttackSpeed(255);
	SetReverseDuration(200); //200ms
	SetTurnDuration(300);    //300ms	
	SetHuntDuration(1000);
	
	//LineSensorCalibration(true,128, 20); 
  //button.waitForButton(); 
  // Play music and wait for it to finish before we start driving.
  //buzzer.play("L16 cdegreg4");
  //while(buzzer.isPlaying()); 	
}

void Beatle::Loop_Sumo()
{
	if (button.isPressed())
  {
    motors.setSpeeds(0, 0);
    button.waitForRelease();
    waitForButtonAndCountDown();
  }  
  
  // Go!
  updateFromSensors();
  checkStateTransition();
  executeCommands();
      
}


// This function reads the sensors and updates the events and parameters that determine behaviour
void Beatle::updateFromSensors()
{
	

  // set if either line sensor detects an edge
  
  //int position;
  
  //position =  LineSensors.readLine(sensor_values);
  LineSensors.read(sensor_values);

  edgeDetected = ((sensor_values[0])>1500  || (sensor_values[6] >1500) );
  
  // set if the ir sensor sees something
  opponentDetected = (!(digitalRead(DSL) && digitalRead(DSR)));

  // accelerometer
  // TODO

  // compass
  // TODO
  //  rotationComplete = false;
}



// This is a (very) simple implementation of a Finite State Machine to represent behaviour.
//
// The code checks the events and guards with context of the current state and determines whether to transition to another behavioural state.
void Beatle::checkStateTransition()
{
  // check for transition from or execute the current state
  switch (state)
  {
  case SURVIVE:
    if (!executingCommands) hunt();
    break;
  //case EVADE:
  //  if (edgeDetected) survive();
  //  else if (!executingCommands) hunt();
  //  break;
  case ATTACK:
    if (edgeDetected) survive();
    else if (!opponentDetected) hunt();
    // Oponent still Detected - check guard
    else if (opponentDetected) target();
    break;
  case TARGET:
    if (edgeDetected) survive();
    //else if (inContact) evade();
    // Lost oponent
    else if (!opponentDetected) hunt();
    // Oponent still Detected - check guard
    // Attack if close
    else if (opponentDetected) attack();
    // Continue to target
    break;
  default:  // HUNT
    if (edgeDetected) survive();
    //else if (inContact) evade();
    else if (opponentDetected)
    {
      // Oponent Detected - check guard
      //if (distance >= CLOSE_RANGE) attack();
      //else target();
      attack();
    }
    else if (!executingCommands) hunt();
    break;
  }
}



// Survival Mode - rotate away from the border
void Beatle::survive()
{

  state = SURVIVE;

  buzzer.playFromProgramSpace(edge_sound_effect);


  if (ABOVE_LINE(sensor_values[0]) ) turnDirection = 1;
  else turnDirection = -1;

  clearCommands();

  addCommand(-REVERSE_SPEED, -REVERSE_SPEED, REVERSE_DURATION);

  if ((ABOVE_LINE(sensor_values[0]))&& (ABOVE_LINE(sensor_values[6])))
  {
    addCommand(turnDirection * TURN_SPEED, -turnDirection * TURN_SPEED, TURN_DURATION);
  }

  addCommand(turnDirection * TURN_SPEED, -turnDirection * TURN_SPEED, TURN_DURATION);
  addCommand(FORWARD_SPEED, FORWARD_SPEED, REVERSE_DURATION);
  startExecutingCommands();
}

// Hunt - search for the oponent
void Beatle::hunt()
{

  state = HUNT;

  buzzer.playFromProgramSpace(hunt_sound_effect);


  clearCommands();
  addCommand(FORWARD_SPEED, FORWARD_SPEED, HUNT_DURATION);
  addCommand(turnDirection * TURN_SPEED, -turnDirection * TURN_SPEED, TURN_DURATION/3);
  startExecutingCommands();
}

// Target - once the opponent is detected, position for an attack
void Beatle::target()
{
  state = TARGET;
  buzzer.playFromProgramSpace(target_sound_effect);
  clearCommands();
  
  addCommand(FORWARD_SPEED, FORWARD_SPEED, 0);
  startExecutingCommands();
}

// Got them where you want them? Attack!
void Beatle::attack()
{
  state = ATTACK;
  buzzer.playFromProgramSpace(attack_sound_effect);
  clearCommands();
  addCommand(ATTACK_SPEED, ATTACK_SPEED, 0);
  startExecutingCommands();
}

// *** Command Queue ***
// stop executing commands and reset the queue
void Beatle::clearCommands()
{
  executingCommands = false;
  numberOfCommands = 0;
  nextCommand = millis();
}

// start executing commands from the start of the queue
void Beatle::startExecutingCommands()
{
  executingCommands = true;
  commandIndex = 0;
  startTime = millis();
  nextCommand = startTime;  // execute the first command immediately
}

// add a command to the queue
void Beatle::addCommand(int left, int right, int duration)
{
  if (numberOfCommands < MAX_COMMANDS)
  {
    // set the command parameters
    leftSpeed[numberOfCommands] = left;
    rightSpeed[numberOfCommands] = right;
    commandDuration[numberOfCommands] = duration;

    // increment the number of commands
    numberOfCommands++;
  }
}

void Beatle::executeCommands()
{
// check if the current command is completed
  if (millis() >= nextCommand)
  {
    // execute the next command
    if (commandIndex < numberOfCommands)
    {
      motors.setSpeeds(leftSpeed[commandIndex], rightSpeed[commandIndex]);
      nextCommand = nextCommand + commandDuration[commandIndex];
      commandIndex++;
    }
    // commands completed
    else executingCommands = false;
  }
}
void Beatle::Loop_FollowLine()
{
	
	//led.colorAll(led.Color(0, 0, 0)); //Set all RGB to red  
  //led.show();
	followSegment();	
	
}

void Beatle::Setup_RemoteControl()
{
	pinMode(DSL,INPUT);
	pinMode(DSR,INPUT);
}
void Beatle::Loop_RemoteControl()
{
	
	//led.theaterChaseRainbow(3);
	if ( _ButtonUp)
  {
   motors.setSpeeds(SPEED, SPEED);
  }
  else if( _ButtonDown)
  {
   motors.setSpeeds(-SPEED, -SPEED);
  }
  else if(_ButtonLeft)
  {
     motors.setSpeeds(-SPEED, SPEED);    
  }
  else if(_ButtonRight)
  {
      motors.setSpeeds(SPEED, -SPEED);
  }
  else
 {
     motors.setSpeeds(0, 0);
 }  
 
 if(_ButtonTriangle)
 	{
 		led.colorAll(led.Color(255,0,0));
 	}
 	else if(_ButtonCircle)
 		{
 			led.colorAll(led.Color(0,255,0));
 		}
 		else if(_ButtonCross)
 		{
 			led.colorAll(led.Color(0,0,255));
 		}
 		else if(_ButtonSquare)
 		{
 			led.colorAll(led.Color(255,255,0));
 		}
 		else if(_ButtonL1)
 		{
 			led.theaterChase(led.Color(127, 0, 0), 50); // Blue
 		}
 		else if(_ButtonL2)
 		{
 			led.theaterChase(led.Color(0, 0, 127), 50); // Blue
 		}
 		else if(_ButtonR1)
 		{
 			  led.rainbowCycle(20);
 		}
 		else if(_ButtonR2)
 		{
 			led.theaterChaseRainbow(50);
 		}
}

void Beatle::Setup_AvoidObstacle()
{
	 pinMode(DSL,INPUT);
   pinMode(DSR,INPUT);
   SetSpeed(128);  //set the running speed = 128;
   
}

void Beatle::Loop_AvoidObstacle()
{
	
	int LeftValue;
  int RightValue;
  LeftValue = digitalRead(DSL);
  RightValue = digitalRead(DSR);

  //led.theaterChaseRainbow(3);
  
  if((LeftValue == 0) && (RightValue == 0))
  {
     motors.setSpeeds(-SPEED, -SPEED);
     delay(300);
     motors.setSpeeds(SPEED, -SPEED);
     delay(200);
  }
   if(LeftValue == 0)
  {
    motors.setSpeeds(SPEED, -SPEED);
    delay(200);
  }
  else if(RightValue == 0)
  {    
    motors.setSpeeds(-SPEED, SPEED);
    delay(200);
  }
  else
  {
    motors.setSpeeds(SPEED, SPEED);
  }
  
	
}

void Beatle::Setup_MazeSolver()
{
	 pinMode(DSL,OUTPUT);
	 pinMode(DSR,OUTPUT);
	 digitalWrite(DSL,LOW);
	 digitalWrite(DSR,LOW);
	 delay(500);
	 digitalWrite(DSL,HIGH);
	 digitalWrite(DSR,HIGH);
   LineSensorCalibration(true,128, 22);
   SetPID(1.0/6.0,0,6.0);
   button.waitForButton(); 
   // Play music and wait for it to finish before we start driving.
   buzzer.play("L16 cdegreg4");
   while(buzzer.isPlaying());  
  
}

// Main function for maze solver
void Beatle::Loop_MazeSolver()
{
  // solveMaze() explores every segment
  // of the maze until it finds the finish
  // line.
  solveMaze();
  delay(200);

  // Sound off buzzer to denote Zumo has solved the maze
  buzzer.play(">>a32");
  

  // The maze has been solved. When the user
  // places the Zumo at the starting line
  // and pushes the Zumo button, the Zumo
  // knows where the finish line is and
  // will automatically navigate.
  while(1)
  {
    button.waitForButton();

    goToFinishLine();
    // Sound off buzzer to denote Zumo is at the finish line.
    buzzer.play(">>a32");
  }
}


// Turns according to the parameter dir, which should be
// 'L' (left), 'R' (right), 'S' (straight), or 'B' (back).
void Beatle::turn(char dir)
{

  // count and last_status help
  // keep track of how much further
  // the Zumo needs to turn.
  unsigned short count;
  unsigned short last_status = 0;
  unsigned int sensors[7];
  //delay(5);  //10

  count = 0;
  // dir tests for which direction to turn
  switch(dir)
  {

  // Since we're using the sensors to coordinate turns instead of timing them,
  // we can treat a left turn the same as a direction reversal: they differ only
  // in whether the zumo will turn 90 degrees or 180 degrees before seeing the
  // line under the sensor. If 'B' is passed to the turn function when there is a
  // left turn available, then the Zumo will turn onto the left segment.
    case 'L':
       //digitalWrite(DSL,LOW);
       motors.setSpeeds(-100, 100);
     
      // This while loop monitors line position
      // until the turn is complete.
      while(count < 2)
      {
        LineSensors.readLine(sensors);
        count += ABOVE_LINE(sensors[1]) ^ last_status;
        last_status = ABOVE_LINE(sensors[1]);
      }

    break;
  case 'B':
      // Turn left.
      //motors.setSpeeds(-TURN_SPEED, TURN_SPEED);
      //digitalWrite(DSL,LOW);
      //digitalWrite(DSR,LOW);
      motors.setSpeeds(-100, 100);
     
      // This while loop monitors line position
      // until the turn is complete.
      while(count < 2)
      {
        LineSensors.readLine(sensors);
        

        // Increment count whenever the state of the sensor changes
    // (white->black and black->white) since the sensor should
    // pass over 1 line while the robot is turning, the final
    // count should be 2
        count += ABOVE_LINE(sensors[1]) ^ last_status;
        last_status = ABOVE_LINE(sensors[1]);
      }

    break;

    case 'R':
      // Turn right.
      //motors.setSpeeds(TURN_SPEED, -TURN_SPEED);
      //digitalWrite(DSR,LOW);
      motors.setSpeeds(100, -100);

      // This while loop monitors line position
      // until the turn is complete.
      while(count < 2)
      {
        LineSensors.readLine(sensors);
        count += ABOVE_LINE(sensors[5]) ^ last_status;
        last_status = ABOVE_LINE(sensors[5]);
      }

    break;

    case 'S':
    // Don't do anything!
    break;
  }
}

// This function decides which way to turn during the learning phase of
// maze solving.  It uses the variables found_left, found_straight, and
// found_right, which indicate whether there is an exit in each of the
// three directions, applying the "left hand on the wall" strategy.
char Beatle::selectTurn(unsigned char found_left, unsigned char found_straight,
  unsigned char found_right)
{
  // Make a decision about how to turn.  The following code
  // implements a left-hand-on-the-wall strategy, where we always
  // turn as far to the left as possible.
  if(found_left)
  {
  		digitalWrite(DSL,LOW);
      return 'L';
  }
  	
  else if(found_straight)
  {
  		//digitalWrite(DSL,LOW);
  		//digitalWrite(DSR,LOW);
  		 return 'S';
  }
   
  else if(found_right)
  {
  		digitalWrite(DSR,LOW);
  		return 'R';
  }
    
  else
  {
  		digitalWrite(DSL,LOW);
  		digitalWrite(DSR,LOW);
  		return 'B';		
  }
    
}

// The maze is broken down into segments. Once the Zumo decides
// which segment to turn on, it will navigate until it finds another
// intersection. followSegment() will then return after the
// intersection is found.
void Beatle::followSegment()
{
  unsigned int position;
  unsigned int sensors[7];
  int error;
  int speedDifference;
  unsigned long timeA;
  
  while(1)
  {
  	
  	//  led.rainbow_stream(2, &led.firstPixelHue);
  	  
  	  //led.theaterChaseRainbow(20, &led.firstPixelHue, &led.firstloop, &led.secondloop);
      // unsigned int sensors[6];

      // Get the position of the line.  Note that we *must* provide the "sensors"
      // argument to readLine() here, even though we are not interested in the
      // individual sensor readings
      position = LineSensors.readLine(sensors);
  
      // Our "error" is how far we are away from the center of the line, which
      // corresponds to position 2500.
      error = position - 3000;

      // Get motor speed difference using proportional and derivative PID terms
      // (the integral term is generally not very useful for line following).
      // Here we are using a proportional constant of 1/4 and a derivative
      // constant of 6, which should work decently for many Zumo motor choices.
      // You probably want to use trial and error to tune these constants for
      // your particular Zumo and line course.
      //int speedDifference = _Kp *error  + _Kd * (error - lastError);  //Kp = 1/12 Kd = 6
      int speedDifference = error * _Kp + _Kd * (error - lastError);

      lastError = error;

      // Get individual motor speeds.  The sign of speedDifference
      // determines if the robot turns left or right.
      int m1Speed = MAX_SPEED + speedDifference;
      int m2Speed = MAX_SPEED - speedDifference;

      // Here we constrain our motor speeds to be between 0 and MAX_SPEED.
      // Generally speaking, one motor will always be turning at MAX_SPEED
      // and the other will be at MAX_SPEED-|speedDifference| if that is positive,
      // else it will be stationary.  For some applications, you might want to
      // allow the motor speed to go negative so that it can spin in reverse.
      if (m1Speed < 0)
        m1Speed = 0;
      if (m2Speed < 0)
        m2Speed = 0;
      if (m1Speed > MAX_SPEED)
        m1Speed = MAX_SPEED;
      if (m2Speed > MAX_SPEED)
        m2Speed = MAX_SPEED;

      motors.setSpeeds(m1Speed, m2Speed);
      if(!ABOVE_LINE(sensors[0]) && !ABOVE_LINE(sensors[1]) && !ABOVE_LINE(sensors[2]) && !ABOVE_LINE(sensors[3]) && !ABOVE_LINE(sensors[4]) && !ABOVE_LINE(sensors[5])&& !ABOVE_LINE(sensors[6]))
      {
         return;
      }
      else if(ABOVE_LINE(sensors[0])  || ABOVE_LINE(sensors[6]) )
      {
        return;
      }
    }//end while
}

// The solveMaze() function works by applying a "left hand on the wall" strategy:
// the robot follows a segment until it reaches an intersection, where it takes the
// leftmost fork available to it. It records each turn it makes, and as long as the
// maze has no loops, this strategy will eventually lead it to the finish. Afterwards,
// the recorded path is simplified by removing dead ends. More information can be
// found in the 3pi maze solving example.

void Beatle::solveMaze()
{
    while(AT_END_POINT == 0)
    {
        // Navigate current line segment
        followSegment();

        // These variables record whether the robot has seen a line to the
        // left, straight ahead, and right, while examining the current
        // intersection.
        unsigned char found_left = 0;
        unsigned char found_straight = 0;
        unsigned char found_right = 0;
        

        // Now read the sensors and check the intersection type.
        unsigned int sensors[7]; 
        int position;
        position =  LineSensors.readLine(sensors);

        // Check for left and right exits.
        if(ABOVE_LINE(sensors[0]) ) 
        {
          found_left = 1;
        }
        if(ABOVE_LINE(sensors[6]) )
        {
            found_right = 1;
        }
        // Drive straight a bit more, until we are
        // approximately in the middle of intersection.
        // This should help us better detect if we
        // have left or right segments.
        motors.setSpeeds(SPEED, SPEED);
        delay(100);//75

        position = LineSensors.readLine(sensors);

        // Check for left and right exits.
         if(ABOVE_LINE(sensors[0])) 
            found_left = 1;
          if(ABOVE_LINE(sensors[6]))
            found_right = 1;

        // After driving a little further, we
        // should have passed the intersection
        // and can check to see if we've hit the
        // finish line or if there is a straight segment
        // ahead.
        delay(100);//75

        // Check for a straight exit.
        position = LineSensors.readLine(sensors);

        // Check again to see if left or right segment has been found
         if(ABOVE_LINE(sensors[0]) ) 
            found_left = 1;
         if(ABOVE_LINE(sensors[6]) )
            found_right = 1;

        if(ABOVE_LINE(sensors[1]) || ABOVE_LINE(sensors[2]) ||  ABOVE_LINE(sensors[3])||  ABOVE_LINE(sensors[4]) ||  ABOVE_LINE(sensors[5]))
            found_straight = 1;

        // Check for the ending spot.
        // If all four middle sensors are on dark black, we have
        // solved the maze.
        if(ABOVE_LINE(sensors[1]) && ABOVE_LINE(sensors[2]) && ABOVE_LINE(sensors[3]) && ABOVE_LINE(sensors[4]) && ABOVE_LINE(sensors[5]))
        {
           delay(100);

        // Check for a straight exit.
           position = LineSensors.readLine(sensors);
           if(ABOVE_LINE(sensors[1]) && ABOVE_LINE(sensors[2]) && ABOVE_LINE(sensors[3]) && ABOVE_LINE(sensors[4]) && ABOVE_LINE(sensors[5]))
            {
               motors.setSpeeds(0,0);
               AT_END_POINT = 1;
               break;
            }
         
        }

     

        // Intersection identification is complete.
        unsigned char dir = selectTurn(found_left, found_straight, found_right);

        // Make the turn indicated by the maze_path.

        time_start = millis();
        
    		turn(dir);
  
        // Store the intersection in the maze_path variable.
       // 
       if(dir == 'S')
       {
         maze_path[maze_path_length] = dir;
         maze_path_length++;
        // Serial.print( millis() - time_start);Serial.print("\t");
        // Serial.println(dir);
       }
       else if( millis() - time_start >250)
       {
        maze_path[maze_path_length] = dir;
        maze_path_length++;
         //Serial.print( millis() - time_start);Serial.print("\t");
         //Serial.println(dir);
           
       }
       digitalWrite(DSL,HIGH);
       digitalWrite(DSR,HIGH);

        // You should check to make sure that the maze_path_length does not
        // exceed the bounds of the array.  We'll ignore that in this
        // example.

        // Simplify the learned maze_path.
        simplifymaze_path(); 

       

    }
    
    //eeprom_write_string(900,maze_path);
    //Serial.println(maze_path);
    eeprom_write_string(900,maze_path);
    delay(200);
    buzzer.play(">>a32");  
    
}



// Now enter an infinite loop - we can re-run the maze as many
// times as we want to.
void Beatle::goToFinishLine()
{
  unsigned int sensors[7];
  int i = 0;
 
  int position;
      

  // Turn around if the Zumo is facing the wrong direction.
  if(maze_path[0] == 'B')
  {
    turn('B');
    i++;
  }

  for(;i<maze_path_length;i++)
  {

    followSegment();

    // Drive through the intersection.
    motors.setSpeeds(SPEED, SPEED);
    delay(200);

    // Make a turn according to the instruction stored in
    // maze_path[i].
    turn(maze_path[i]);
   // Serial.println(maze_path[i]);
   
  }

  // Follow the last segment up to the finish.
  followSegment();

  // The finish line has been reached.
  // Return and wait for another button push to
  // restart the maze.
  position = LineSensors.readLine(sensors);
  motors.setSpeeds(0,0);

  return;
}


// simplifymaze_path analyzes the maze_path[] array and reduces all the
// turns. For example: Right turn + Right turn = (1) Back turn.
void Beatle::simplifymaze_path()
{

  // only simplify the maze_path if the second-to-last turn was a 'B'
  if(maze_path_length < 3 || maze_path[maze_path_length - 2] != 'B')
  return;

  int total_angle = 0;
  int i;

  for(i = 1; i <= 3; i++)
  {
    switch(maze_path[maze_path_length - i])
    {
      case 'R':
        total_angle += 90;
        break;
      case 'L':
        total_angle += 270;
        break;
      case 'B':
        total_angle += 180;
        break;
    }
  }

  // Get the angle as a number between 0 and 360 degrees.
  total_angle = total_angle % 360;

  // Replace all of those turns with a single one.
  switch(total_angle)
  {
    case 0:
      maze_path[maze_path_length - 3] = 'S';
      break;
    case 90:
      maze_path[maze_path_length - 3] = 'R';
      break;
    case 180:
      maze_path[maze_path_length - 3] = 'B';
      break;
    case 270:
      maze_path[maze_path_length - 3] = 'L';
      break;
  }

  // The maze_path is now two steps shorter.
  maze_path_length -= 2;
}



void Beatle::SetMaxSpeed(int speed)
{
	  MAX_SPEED = speed;
}
void Beatle::SetTurnSpeed(int speed)
{
		TURN_SPEED = speed;
}
void Beatle::SetSpeed(int speed)
{
		SPEED = speed;
}
void Beatle::SetForwardSpeed(int speed)
{
		FORWARD_SPEED = speed;
}
void Beatle::SetReverseSpeed(int speed)
{
		REVERSE_SPEED = speed;
}

void Beatle::SetAttackSpeed(int speed)
{
		ATTACK_SPEED = speed;
}


void Beatle::SetReverseDuration(int duration)
{
		REVERSE_DURATION = duration;
}
	
void Beatle::SetTurnDuration(int duration)
{
		TURN_DURATION = duration;
}
		
void Beatle::SetHuntDuration(int duration)
{
		HUNT_DURATION = duration;
}

void Beatle::SetSensorThreshold(int threshold)
{
		SENSOR_THRESHOLD = threshold;
}

void Beatle::SetPID(double kp,double ki,double kd)
{
	_Kp = kp;
	_Ki = ki;
	_Kd = kd;
	
}


/****************************************************************************************************
 * Parameters configuration
****************************************************************************************************/
void Beatle::setDefaultvalue(void)
{
  encoder_eeprom.start_data = EEPROM_CAL_START;
  encoder_eeprom.rev = 1;
  
  encoder_eeprom.RGB_pin = 2;
  
  encoder_eeprom.DSL_pin  = 11;
  encoder_eeprom.DSR_pin  = 13;
  
  encoder_eeprom.DIR_LP_pin  = 9;
  encoder_eeprom.DIR_LN_pin  = 5;
  encoder_eeprom.DIR_RP_pin  = 6;
  encoder_eeprom.DIR_RN_pin  =10;
  
 

  encoder_eeprom.S0_pin = A3;
  encoder_eeprom.S0_maxval = 2500;
  encoder_eeprom.S0_minval = 0;
  
  encoder_eeprom.S1_pin = 4;
  encoder_eeprom.S1_maxval = 2500;
  encoder_eeprom.S1_minval = 0;
  
  encoder_eeprom.S2_pin = A2;
  encoder_eeprom.S2_maxval = 2500;
  encoder_eeprom.S2_minval = 0;
  
  encoder_eeprom.S3_pin = 7;
  encoder_eeprom.S3_maxval = 2500;
  encoder_eeprom.S3_minval = 0;
  
  encoder_eeprom.S4_pin = A1;
  encoder_eeprom.S4_maxval = 2500;
  encoder_eeprom.S4_minval = 0;
  
  encoder_eeprom.S5_pin = 8;
  encoder_eeprom.S5_maxval = 2500;
  encoder_eeprom.S5_minval = 0;
  
  encoder_eeprom.S6_pin = A0;
  encoder_eeprom.S6_maxval = 2500;
  encoder_eeprom.S6_minval = 0;
  
  encoder_eeprom.mid_data = EEPROM_CAL_MID;

  encoder_eeprom.end_data = EEPROM_CAL_END;
}

void Beatle::FloatToEEPROM(int address,int num,float *f)
{
  int i,j,bakupaddress;
  bakupaddress = address +  EEPROM.length()/2;
  for(i=0;i<2;i++)
  {
    for(j=0;j<num;j++)
    {
      EEPROM.put(address, f[j]);  
      address = address + sizeof(float);
    }
    address = bakupaddress;
  }
}

void Beatle::IntToEEPROM(int address,int num, uint16_t *data)
{
  int i,j,bakupaddress;
  bakupaddress = address +  EEPROM.length()/2;
  for(i=0;i<2;i++)
  {
    for(j=0;j<num;j++)
    {
      EEPROM.put(address, data[j]);  
      address = address + sizeof(uint16_t);
    }
    address = bakupaddress;
  }
}

void Beatle::ByteToEEPROM(int address,int num, uint8_t *data)
{
  int i,j,bakupaddress;
  bakupaddress = address +  EEPROM.length()/2;
  for(i=0;i<2;i++)
  {
    for(j=0;j<num;j++)
    {
      EEPROM.put(address, data[j]);  
      address = address + sizeof(uint8_t);
    }
    address = bakupaddress;
  }
}

void Beatle::clearEEPROM(void)
{
 for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);
  } 
  delay(100);
}

void Beatle::writetoEEPROM(void)
{
  int16_t i,address, length;
  length = EEPROM.length();
  for(i = 0; i < 2; i++)
  {
    EEPROM.write(EEPROM_START_POS, EEPROM_IF_HAVECAL_CHECK1);
    EEPROM.write(EEPROM_START_POS + 1, EEPROM_IF_HAVECAL_CHECK2);
    EEPROM.put(STORE_START_ADDR, encoder_eeprom);
    address = length/2;
  } 
  Serial.println("write eeprom done");
}


void Beatle::updatefromBackuparea(void)
{
  int16_t address, length;
  length = EEPROM.length();
  address = length/2;
  if((EEPROM.read(address) == EEPROM_IF_HAVECAL_CHECK1) & (EEPROM.read(address + 1) == EEPROM_IF_HAVECAL_CHECK2))
  {
    address = length/2 + 2;
    EEPROM.get(address, encoder_eeprom);
    if((encoder_eeprom.start_data == EEPROM_CAL_START) & (encoder_eeprom.mid_data == EEPROM_CAL_MID) & (encoder_eeprom.end_data == EEPROM_CAL_END))
    {
      EEPROM.write(EEPROM_START_POS, EEPROM_IF_HAVECAL_CHECK1);
      EEPROM.write(EEPROM_START_POS+1, EEPROM_IF_HAVECAL_CHECK2);
      EEPROM.put(STORE_START_ADDR, encoder_eeprom);
    }
    else
    {
      setDefaultvalue();  
      writetoEEPROM(); 
    }
  }
}

boolean Beatle::readEEPROM(void)
{
  	int16_t length = EEPROM.length();
  	Serial.println( "Read data from EEPROM " );

  //EEPROM.get(STORE_DEVID_ADDR, encoder_eeprom_new.devid);
//  Serial.print("devid:");
 // Serial.println(encoder_eeprom_new.devid,DEC);
   
  if((EEPROM.read(EEPROM_START_POS) == EEPROM_IF_HAVECAL_CHECK1) & (EEPROM.read(EEPROM_START_POS + 1) == EEPROM_IF_HAVECAL_CHECK2))
  {
    EEPROM.get(STORE_START_ADDR, encoder_eeprom);
    
    

    Serial.print("Pin:");
    Serial.print(encoder_eeprom.S0_pin);Serial.print(" ");
    Serial.print(encoder_eeprom.S1_pin);Serial.print(" ");
    Serial.print(encoder_eeprom.S2_pin);Serial.print(" ");
    Serial.print(encoder_eeprom.S3_pin);Serial.print(" "); 
    Serial.print(encoder_eeprom.S4_pin);Serial.print(" ");
    Serial.print(encoder_eeprom.S5_pin);Serial.print(" ");
    Serial.print(encoder_eeprom.S6_pin);Serial.println(" ");
        
          
    Serial.print("Max:");
    Serial.print(encoder_eeprom.S0_maxval);Serial.print(" ");
    Serial.print(encoder_eeprom.S1_maxval);Serial.print(" ");
    Serial.print(encoder_eeprom.S2_maxval);Serial.print(" ");
    Serial.print(encoder_eeprom.S3_maxval);Serial.print(" ");
    Serial.print(encoder_eeprom.S4_maxval);Serial.print(" ");
    Serial.print(encoder_eeprom.S5_maxval);Serial.print(" ");
    Serial.print(encoder_eeprom.S6_maxval);Serial.println(" ");
    
    Serial.print("Min:");
    Serial.print(encoder_eeprom.S0_minval);Serial.print(" ");
    Serial.print(encoder_eeprom.S1_minval);Serial.print(" ");
    Serial.print(encoder_eeprom.S2_minval);Serial.print(" ");
    Serial.print(encoder_eeprom.S3_minval);Serial.print(" ");
    Serial.print(encoder_eeprom.S4_minval);Serial.print(" ");
    Serial.print(encoder_eeprom.S5_minval);Serial.print(" ");
    Serial.print(encoder_eeprom.S6_minval);Serial.println(" ");
 
  
    //Serial.println(sizeof(encoder_eeprom_type));
    //Serial.print("start data:");Serial.println(encoder_eeprom.start_data,HEX);
    //EEPROM.get(STORE_S7_PIN_ADDR, encoder_eeprom.S5_pin);
    //Serial.print("S5 maxval:");Serial.println(encoder_eeprom.S5_pin);

    //  Serial.print("devid:");
     // Serial.println(encoder_eeprom.devid,DEC);
    if((encoder_eeprom.start_data == EEPROM_CAL_START) & (encoder_eeprom.mid_data == EEPROM_CAL_MID) & (encoder_eeprom.end_data == EEPROM_CAL_END))
    {
      return true;
    }
    else
    {
      Serial.println( "updatefromBackuparea" );
      updatefromBackuparea();  
      return true;  
    }
  }
  else if((EEPROM.read(length/2) == EEPROM_IF_HAVECAL_CHECK1) & (EEPROM.read(length/2 + 1) == EEPROM_IF_HAVECAL_CHECK2))
  {
    Serial.println( "updatefromBackuparea 2" );
    updatefromBackuparea(); 
    return true;
  }
  else
  {    
    setDefaultvalue();
    writetoEEPROM();
    return false;
  }


}

void Beatle::readCalibrationData()
{
	LineSensors.init();
	if((EEPROM.read(EEPROM_START_POS) == EEPROM_IF_HAVECAL_CHECK1) & (EEPROM.read(EEPROM_START_POS + 1) == EEPROM_IF_HAVECAL_CHECK2))
  {
    EEPROM.get(STORE_START_ADDR, encoder_eeprom);
	
  	LineSensors.calibratedMaximumOn = (unsigned int*)malloc(sizeof(unsigned int)*7);
  	LineSensors.calibratedMinimumOn = (unsigned int*)malloc(sizeof(unsigned int)*7);
   
  	LineSensors.calibratedMaximumOn[0] = encoder_eeprom.S0_maxval;
  	LineSensors.calibratedMinimumOn[0] = encoder_eeprom.S0_minval;
  	LineSensors.calibratedMaximumOn[1] = encoder_eeprom.S1_maxval;
  	LineSensors.calibratedMinimumOn[1] = encoder_eeprom.S1_minval;
  	LineSensors.calibratedMaximumOn[2] = encoder_eeprom.S2_maxval;
  	LineSensors.calibratedMinimumOn[2] = encoder_eeprom.S2_minval;
  	LineSensors.calibratedMaximumOn[3] = encoder_eeprom.S3_maxval;
  	LineSensors.calibratedMinimumOn[3] = encoder_eeprom.S3_minval;
  	LineSensors.calibratedMaximumOn[4] = encoder_eeprom.S4_maxval;
  	LineSensors.calibratedMinimumOn[4] = encoder_eeprom.S4_minval;
  	LineSensors.calibratedMaximumOn[5] = encoder_eeprom.S5_maxval;
  	LineSensors.calibratedMinimumOn[5] = encoder_eeprom.S5_minval;
  	LineSensors.calibratedMaximumOn[6] = encoder_eeprom.S6_maxval;
  	LineSensors.calibratedMinimumOn[6] = encoder_eeprom.S6_minval;	     
  	if(DEBUG>0)
  	{
  	    Serial.println("Read Calibration Data from EEPROM:");
  	    Serial.print("Max:");                                      
 		    Serial.print(encoder_eeprom.S0_maxval);Serial.print(" ");  
        Serial.print(encoder_eeprom.S1_maxval);Serial.print(" ");  
        Serial.print(encoder_eeprom.S2_maxval);Serial.print(" ");  
        Serial.print(encoder_eeprom.S3_maxval);Serial.print(" ");  
        Serial.print(encoder_eeprom.S4_maxval);Serial.print(" ");  
        Serial.print(encoder_eeprom.S5_maxval);Serial.print(" ");  
        Serial.print(encoder_eeprom.S6_maxval);Serial.println(" ");
                                                                   
        Serial.print("Min:");                                      
        Serial.print(encoder_eeprom.S0_minval);Serial.print(" ");  
        Serial.print(encoder_eeprom.S1_minval);Serial.print(" ");  
        Serial.print(encoder_eeprom.S2_minval);Serial.print(" ");  
        Serial.print(encoder_eeprom.S3_minval);Serial.print(" ");  
        Serial.print(encoder_eeprom.S4_minval);Serial.print(" ");  
        Serial.print(encoder_eeprom.S5_minval);Serial.print(" ");  
        Serial.print(encoder_eeprom.S6_minval);Serial.println(" ");
  	}

  	
	}
	else
	{               
		Serial.println("[ERROR]Read Calibration Data Failed. please do calibration again!");
		buzzer.play(">g32gggggggggggg");
		
	}
}

void Beatle::writeCalibrationData()
{
		 setDefaultvalue();
		 encoder_eeprom.S0_maxval =LineSensors.calibratedMaximumOn[0]; 
  	 encoder_eeprom.S0_minval =LineSensors.calibratedMinimumOn[0];
  	 encoder_eeprom.S1_maxval =LineSensors.calibratedMaximumOn[1];
  	 encoder_eeprom.S1_minval =LineSensors.calibratedMinimumOn[1];
  	 encoder_eeprom.S2_maxval =LineSensors.calibratedMaximumOn[2];
  	 encoder_eeprom.S2_minval =LineSensors.calibratedMinimumOn[2];
  	 encoder_eeprom.S3_maxval =LineSensors.calibratedMaximumOn[3];
  	 encoder_eeprom.S3_minval =LineSensors.calibratedMinimumOn[3];
  	 encoder_eeprom.S4_maxval =LineSensors.calibratedMaximumOn[4];
  	 encoder_eeprom.S4_minval =LineSensors.calibratedMinimumOn[4];
  	 encoder_eeprom.S5_maxval =LineSensors.calibratedMaximumOn[5];
  	 encoder_eeprom.S5_minval =LineSensors.calibratedMinimumOn[5];
  	 encoder_eeprom.S6_maxval =LineSensors.calibratedMaximumOn[6];
  	 encoder_eeprom.S6_minval =LineSensors.calibratedMinimumOn[6];	
  	 //Serial.println("WriteCalibrrationData to EEPROM");
     writetoEEPROM();                                                            
}

void Beatle::writeCalibrationData(unsigned int Max[],unsigned int Min[])
{
		 //setDefaultvalue();
		 LineSensors.init();   
		 LineSensors.calibratedMaximumOn = (unsigned int*)malloc(sizeof(unsigned int)*7);
     LineSensors.calibratedMinimumOn = (unsigned int*)malloc(sizeof(unsigned int)*7);
   
		 LineSensors.calibratedMaximumOn[0] = Max[0];
  	 LineSensors.calibratedMinimumOn[0] = Min[0];
  	 LineSensors.calibratedMaximumOn[1] = Max[1];
  	 LineSensors.calibratedMinimumOn[1] = Min[1];
  	 LineSensors.calibratedMaximumOn[2] = Max[2];
  	 LineSensors.calibratedMinimumOn[2] = Min[2];
  	 LineSensors.calibratedMaximumOn[3] = Max[3];
  	 LineSensors.calibratedMinimumOn[3] = Min[3];
  	 LineSensors.calibratedMaximumOn[4] = Max[4];
  	 LineSensors.calibratedMinimumOn[4] = Min[4];
  	 LineSensors.calibratedMaximumOn[5] = Max[5];
  	 LineSensors.calibratedMinimumOn[5] = Min[5];
  	 LineSensors.calibratedMaximumOn[6] = Max[6];
  	 LineSensors.calibratedMinimumOn[6] = Min[6];	     
  	  
		 encoder_eeprom.S0_maxval =Max[0]; 
  	 encoder_eeprom.S0_minval =Min[0];
  	 encoder_eeprom.S1_maxval =Max[1];
  	 encoder_eeprom.S1_minval =Min[1];
  	 encoder_eeprom.S2_maxval =Max[2];
  	 encoder_eeprom.S2_minval =Min[2];
  	 encoder_eeprom.S3_maxval =Max[3];
  	 encoder_eeprom.S3_minval =Min[3];
  	 encoder_eeprom.S4_maxval =Max[4];
  	 encoder_eeprom.S4_minval =Min[4];
  	 encoder_eeprom.S5_maxval =Max[5];
  	 encoder_eeprom.S5_minval =Min[5];
  	 encoder_eeprom.S6_maxval =Max[6];
  	 encoder_eeprom.S6_minval =Min[6];	
  	 //Serial.println("===============");
     writetoEEPROM();   
     delay(100);
}

void Beatle::LineSensorCalibration(boolean status,int speed, int delay_time)
{	
	
	
  buzzer.play(">>a32");
	LineSensors.init();        
  if(status)
	{
  //Do calibration one time
  int i;
  for(i = 0; i < 80; i++)
  {
    if ((i > 10 && i <= 30) || (i > 50 && i <= 70))
      motors.setSpeeds(-speed, speed);
    else
      motors.setSpeeds(speed, -speed);
      LineSensors.calibrate();

    // Since our counter runs to 80, the total delay will be
    // 80*20 = 1600 ms.
    delay(delay_time);
  }
  	motors.setSpeeds(0,0);
  	writeCalibrationData();
  	delay(100);
  	CalibrationFlag = 1;
	}
	else
	{
		readCalibrationData();
	}
	buzzer.play(">g32>>c32");	
}




// Returns true if the address is between the
// minimum and maximum allowed values, false otherwise.
//
// This function is used by the other, higher-level functions
// to prevent bugs and runtime errors due to invalid addresses.
boolean Beatle::eeprom_is_addr_ok(int addr)
{
	return ((addr >= EEPROM_MIN_ADDR) && (addr <= EEPROM_MAX_ADDR));
}

// Writes a sequence of bytes to eeprom starting at the specified address.
// Returns true if the whole array is successfully written.
// Returns false if the start or end addresses aren't between
// the minimum and maximum allowed values.
// When returning false, nothing gets written to eeprom.
boolean Beatle::eeprom_write_bytes(int startAddr, const byte* array, int numBytes) 
{
	// counter
	int i;
	// both first byte and last byte addresses must fall within
	// the allowed range 
	if (!eeprom_is_addr_ok(startAddr) || !eeprom_is_addr_ok(startAddr + numBytes)) 
	{
		return false;
	}
	for (i = 0; i < numBytes; i++) 
	{
		EEPROM.write(startAddr + i, array[i]);
	}
	return true;
}

// Writes a string starting at the specified address.
// Returns true if the whole string is successfully written.
// Returns false if the address of one or more bytes fall outside the allowed range.
// If false is returned, nothing gets written to the eeprom.
boolean Beatle::eeprom_write_string(int addr, const char* string) 
{

	int numBytes; // actual number of bytes to be written
	//write the string contents plus the string terminator byte (0x00)
	numBytes = strlen(string) + 1;
	return eeprom_write_bytes(addr, (const byte*)string, numBytes);
}

// Reads a string starting from the specified address.
// Returns true if at least one byte (even only the string terminator one) is read.
// Returns false if the start address falls outside the allowed range or declare buffer size is zero.
// 
// The reading might stop for several reasons:
// - no more space in the provided buffer
// - last eeprom address reached
// - string terminator byte (0x00) encountered.
boolean Beatle::eeprom_read_string(int addr, char* buffer, int bufSize) 
{
	byte ch; // byte read from eeprom
	int bytesRead; // number of bytes read so far
	if (!eeprom_is_addr_ok(addr)) 
	{ // check start address
		return false;
	}

	if (bufSize == 0) 
	{ // how can we store bytes in an empty buffer ?
		return false;
	}	
	// is there is room for the string terminator only, no reason to go further
	if (bufSize == 1) 
	{
		buffer[0] = 0;
		return true;
	}
	
	bytesRead = 0; // initialize byte counter
	ch = EEPROM.read(addr + bytesRead); // read next byte from eeprom
	buffer[bytesRead] = ch; // store it into the user buffer
	bytesRead++; // increment byte counter
	// stop conditions:
	// - the character just read is the string terminator one (0x00)
	// - we have filled the user buffer
	// - we have reached the last eeprom address
	while ( (ch != 0x00) && (bytesRead < bufSize) && ((addr + bytesRead) <= EEPROM_MAX_ADDR) )
	{
		// if no stop condition is met, read the next byte from eeprom
		ch = EEPROM.read(addr + bytesRead);
		buffer[bytesRead] = ch; // store it into the user buffer
		bytesRead++; // increment byte counter
	}

	// make sure the user buffer has a string terminator, (0x00) as its last byte
	if ((ch != 0x00) && (bytesRead >= 1)) 
	{
		buffer[bytesRead - 1] = 0;
	}
	return true;
}


void Beatle::setDebugLevel(int idx)
{
	DEBUG = idx;		
}


boolean Beatle::IsSensorCalibrated()
{
	if(CalibrationFlag)
		return false;
	else	
		return true;
}
void Beatle::SetCalibrationFlag(int flag)
{
  	CalibrationFlag = flag;
}

