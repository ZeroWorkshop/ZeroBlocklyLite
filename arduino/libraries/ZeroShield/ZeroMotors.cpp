#include "ZeroMotors.h"

// T3
//#define MOTOR1P 3
//#define MOTOR1M 13
//#define MOTOR2P 5
//#define MOTOR2M 12
//#define MOTOR3P 11
//#define MOTOR3M 10
//#define MOTOR4P 6
//#define MOTOR4M 9

//for onesheeld broad


  
    //for T4 broad
//#define PWM_L  5     //M2
//#define PWM_R  6     //M4
//#define DIR_L  12
//#define DIR_R  9 
  
#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega328P__) || defined (__AVR_ATmega32U4__)
  //#define USE_20KHZ_PWM
#endif

static boolean flipLeft = true;
static boolean flipRight = true;

// constructor (doesn't do anything)

ZeroMotors::ZeroMotors(uint8_t pwm_1,uint8_t dir_1,uint8_t pwm_2,uint8_t dir_2)
{
     PWM_L = pwm_1;
     PWM_R = pwm_2;
     DIR_L = dir_1;
     DIR_R = dir_2; 
}

// initialize timer1 to generate the proper PWM outputs to the motor drivers
void ZeroMotors::init2()
{
  pinMode(PWM_L,  OUTPUT);
  pinMode(PWM_R,  OUTPUT);
  pinMode(DIR_L, OUTPUT);
  pinMode(DIR_R, OUTPUT);

#ifdef USE_20KHZ_PWM
  // Timer 1 configuration
  // prescaler: clockI/O / 1
  // outputs enabled
  // phase-correct PWM
  // top of 400
  //
  // PWM frequency calculation
  // 16MHz / 1 (prescaler) / 2 (phase-correct) / 400 (top) = 20kHz
  TCCR1A = 0b10100000;
  TCCR1B = 0b00010001;
  ICR1 = 400;
#endif
}

// enable/disable flipping of left motor
void ZeroMotors::flipLeftMotor(boolean flip)
{
  flipLeft = flip;
}

// enable/disable flipping of right motor
void ZeroMotors::flipRightMotor(boolean flip)
{
  flipRight = flip;
}

// set speed for left motor; speed is a number between -400 and 400
void ZeroMotors::setLeftSpeed(int speed)
{
  init(); // initialize if necessary

  boolean reverse = 0;

  if (speed < 0)
  {
    speed = -speed; // make speed a positive quantity
    reverse = 1;    // preserve the direction
  }
  if (speed > 400)  // Max
    speed = 400;

#ifdef USE_20KHZ_PWM
  OCR1B = speed;
#else
  analogWrite(PWM_L, speed * 51 / 80); // default to using analogWrite, mapping 400 to 255
#endif

  if (reverse ^ flipLeft) // flip if speed was negative or flipLeft setting is active, but not both
    digitalWrite(DIR_L, HIGH);
  else
    digitalWrite(DIR_L, LOW);
}

// set speed for right motor; speed is a number between -400 and 400
void ZeroMotors::setRightSpeed(int speed)
{
  init(); // initialize if necessary

  boolean reverse = 0;

  if (speed < 0)
  {
    speed = -speed;  // Make speed a positive quantity
    reverse = 1;  // Preserve the direction
  }
  if (speed > 400)  // Max PWM dutycycle
    speed = 400;

#ifdef USE_20KHZ_PWM
  OCR1A = speed;
#else
  analogWrite(PWM_R, speed * 51 / 80); // default to using analogWrite, mapping 400 to 255
#endif

  if (reverse ^ flipRight) // flip if speed was negative or flipRight setting is active, but not both
    digitalWrite(DIR_R, HIGH);
  else
    digitalWrite(DIR_R, LOW);
}

// set speed for both motors
void ZeroMotors::setSpeeds(int leftSpeed, int rightSpeed)
{
  setLeftSpeed(leftSpeed);
  setRightSpeed(rightSpeed);
}