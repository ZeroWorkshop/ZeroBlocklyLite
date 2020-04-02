#include "ZumoMotors.h"

#define PWM_L 9
#define DIR_L 5
#define PWM_R 6
#define DIR_R 10

#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega328P__) || defined (__AVR_ATmega32U4__)
  #define USE_20KHZ_PWM
#endif

static boolean flipLeft = false;
static boolean flipRight = false;

// constructor (doesn't do anything)
ZumoMotors::ZumoMotors()
{
}

// initialize timer1 to generate the proper PWM outputs to the motor drivers
void ZumoMotors::init2()
{
  pinMode(PWM_L,  OUTPUT);
  pinMode(PWM_R,  OUTPUT);
  pinMode(DIR_L, OUTPUT);
  pinMode(DIR_R, OUTPUT);
  digitalWrite(PWM_L,LOW);
  digitalWrite(PWM_R,LOW);
  digitalWrite(DIR_L,LOW);
  digitalWrite(DIR_R,LOW);

}

// enable/disable flipping of left motor
void ZumoMotors::flipLeftMotor(boolean flip)
{
  flipLeft = flip;
}

// enable/disable flipping of right motor
void ZumoMotors::flipRightMotor(boolean flip)
{
  flipRight = flip;
}

// set speed for left motor; speed is a number between -400 and 400
void ZumoMotors::setLeftSpeed(int speed)
{
  init(); // initialize if necessary
    
  boolean reverse = 0;
  
  if (speed < 0)
  {
    speed = -speed; // make speed a positive quantity
    reverse = 1;    // preserve the direction
  }
  if (speed > 255)  // Max 
    speed = 255;
    

  if (reverse ^ flipLeft) // flip if speed was negative or flipLeft setting is active, but not both
  	{
  		analogWrite(PWM_L, speed); 
  		digitalWrite(DIR_L,LOW);
  		
  	}
    
  else
  	{
  		digitalWrite(PWM_L,LOW);
  		analogWrite(DIR_L, speed);  		
  	}
    
}

// set speed for right motor; speed is a number between -400 and 400
void ZumoMotors::setRightSpeed(int speed)
{
  init(); // initialize if necessary
    
  boolean reverse = 0;
  
  if (speed < 0)
  {
    speed = -speed;  // Make speed a positive quantity
    reverse = 1;  // Preserve the direction
  }
  if (speed > 255)  // Max PWM dutycycle
    speed = 255;
    

  if (reverse ^ flipRight) // flip if speed was negative or flipRight setting is active, but not both
   	{
   		analogWrite(PWM_R, speed); 
  		digitalWrite(DIR_R,LOW);
  	}
  else
  	{
      digitalWrite(PWM_R,0); 
 		  analogWrite(DIR_R, speed );
  	}
    
}

// set speed for both motors
void ZumoMotors::setSpeeds(int leftSpeed, int rightSpeed)
{
  setLeftSpeed(leftSpeed);
  setRightSpeed(rightSpeed);
}