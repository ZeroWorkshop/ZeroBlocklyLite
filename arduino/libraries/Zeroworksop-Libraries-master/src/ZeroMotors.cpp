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
  


// constructor (doesn't do anything)

#define BOARD_PRO_V11 1
#define BOARD_PRO     0


ZeroMotors::ZeroMotors()
{
     M1_PWM = 3;
     M2_PWM = 5;
     M3_PWM = 11;
     M4_PWM = 6;
     M1_DIR = 13;
     M2_DIR = 12;
     M3_DIR = 10;
     M4_DIR = 9; 
     
     left_PWM = M1_PWM;
     left_DIR = M1_DIR;
     right_PWM = M2_PWM;
     right_DIR = M2_DIR;
     
     flipM1 = false;
     flipM2 = false;
     flipM3 = false;
     flipM4 = false;
}
ZeroMotors::ZeroMotors(uint8_t pwm_1,uint8_t dir_1,uint8_t pwm_2,uint8_t dir_2)
{
     M1_PWM = pwm_1;
     M2_PWM = pwm_2;
     M3_PWM = 0;
     M4_PWM = 0;
     M1_DIR = dir_1;
     M2_DIR = dir_2;
     M3_DIR = 0;
     M4_DIR = 0; 
     
     left_PWM = M1_PWM;
     left_DIR = M1_DIR;
     right_PWM = M2_PWM;
     right_DIR = M2_DIR;
              
     flipM1 = false;
     flipM2 = false;
     flipM3 = false;
     flipM4 = false;
}

ZeroMotors::ZeroMotors(uint8_t pwm_1,uint8_t dir_1,uint8_t pwm_2,uint8_t dir_2,uint8_t boardVersion)
{
	if (boardVersion == BOARD_PRO_V11) {
     M1_PWM_P = pwm_1;
     M2_PWM_P = pwm_2;
     M3_PWM_P = 0;
     M4_PWM_P = 0;
     M1_PWM_M = dir_1;
     M2_PWM_M = dir_2;
     M3_PWM_M = 0;
     M4_PWM_M = 0; 
     
     left_PWM_P = M1_PWM_P;
     left_PWM_M = M1_PWM_M;
     right_PWM_P = M2_PWM_P;
     right_PWM_M = M2_PWM_M;
              
     flipM1 = false;
     flipM2 = false;
     flipM3 = false;
     flipM4 = false;
   }
   else if (boardVersion == BOARD_PRO) {
     M1_PWM = pwm_1;
     M2_PWM = pwm_2;
     M3_PWM = 0;
     M4_PWM = 0;
     M1_DIR = dir_1;
     M2_DIR = dir_2;
     M3_DIR = 0;
     M4_DIR = 0; 
     
     left_PWM = M1_PWM;
     left_DIR = M1_DIR;
     right_PWM = M2_PWM;
     right_DIR = M2_DIR;
              
     flipM1 = false;
     flipM2 = false;
     flipM3 = false;
     flipM4 = false;
   }
}

ZeroMotors::ZeroMotors(uint8_t pwm_1,uint8_t dir_1,uint8_t pwm_2,uint8_t dir_2,uint8_t pwm_3,uint8_t dir_3,uint8_t pwm_4,uint8_t dir_4)
{
     M1_PWM = pwm_1;
     M2_PWM = pwm_2;
     M3_PWM = pwm_3;
     M4_PWM = pwm_4;
     M1_DIR = dir_1;
     M2_DIR = dir_2;
     M3_DIR = dir_3;
     M4_DIR = dir_4; 
     
     left_PWM = M1_PWM;
     left_DIR = M1_DIR;
     right_PWM = M2_PWM;
     right_DIR = M2_DIR;
          
     flipM1 = false;
     flipM2 = false;
     flipM3 = false;
     flipM4 = false;
}

// initialize timer1 to generate the proper PWM outputs to the motor drivers
void ZeroMotors::init2()
{
  pinMode(M1_PWM,  OUTPUT);
  pinMode(M2_PWM,  OUTPUT);
  pinMode(M3_PWM,  OUTPUT);
  pinMode(M4_PWM,  OUTPUT);
  pinMode(M1_DIR, OUTPUT);
  pinMode(M2_DIR, OUTPUT);
  pinMode(M3_DIR, OUTPUT);
  pinMode(M4_DIR, OUTPUT);
  digitalWrite(M1_PWM,LOW);
  digitalWrite(M2_PWM,LOW);
  digitalWrite(M3_PWM,LOW);
  digitalWrite(M4_PWM,LOW);
  digitalWrite(M1_DIR,LOW);
  digitalWrite(M2_DIR,LOW);
  digitalWrite(M3_DIR,LOW);
  digitalWrite(M4_DIR,LOW);

}
void ZeroMotors::init2(uint8_t boardVersion)
{
	if (boardVersion == BOARD_PRO_V11) {
  pinMode(M1_PWM_P,  OUTPUT);
  pinMode(M2_PWM_P,  OUTPUT);
  pinMode(M3_PWM_P,  OUTPUT);
  pinMode(M4_PWM_P,  OUTPUT);
  pinMode(M1_PWM_M, OUTPUT);
  pinMode(M2_PWM_M, OUTPUT);
  pinMode(M3_PWM_M, OUTPUT);
  pinMode(M4_PWM_M, OUTPUT);
  digitalWrite(M1_PWM_P,LOW);
  digitalWrite(M2_PWM_P,LOW);
  digitalWrite(M3_PWM_P,LOW);
  digitalWrite(M4_PWM_P,LOW);
  digitalWrite(M1_PWM_M,LOW);
  digitalWrite(M2_PWM_M,LOW);
  digitalWrite(M3_PWM_M,LOW);
  digitalWrite(M4_PWM_M,LOW);
  }
  else if (boardVersion == BOARD_PRO) {
  pinMode(M1_PWM,  OUTPUT);
  pinMode(M2_PWM,  OUTPUT);
  pinMode(M3_PWM,  OUTPUT);
  pinMode(M4_PWM,  OUTPUT);
  pinMode(M1_DIR, OUTPUT);
  pinMode(M2_DIR, OUTPUT);
  pinMode(M3_DIR, OUTPUT);
  pinMode(M4_DIR, OUTPUT);
  digitalWrite(M1_PWM,LOW);
  digitalWrite(M2_PWM,LOW);
  digitalWrite(M3_PWM,LOW);
  digitalWrite(M4_PWM,LOW);
  digitalWrite(M1_DIR,LOW);
  digitalWrite(M2_DIR,LOW);
  digitalWrite(M3_DIR,LOW);
  digitalWrite(M4_DIR,LOW);
  }

}
// enable/disable flipping of left motor
void ZeroMotors::flipM1Motor(boolean flip)
{
  flipM1 = flip;
}

// enable/disable flipping of right motor
void ZeroMotors::flipM2Motor(boolean flip)
{
  flipM2 = flip;
}


// enable/disable flipping of left motor
void ZeroMotors::flipM3Motor(boolean flip)
{
  flipM3 = flip;
}

// enable/disable flipping of right motor
void ZeroMotors::flipM4Motor(boolean flip)
{
  flipM4 = flip;
}

// set speed for left motor; speed is a number between -400 and 400
void ZeroMotors::motorControl(int MotorNumber,int speed)
{
  init(); // initialize if necessary

  boolean reverse = 0;

  if (speed < 0)
  {
    speed = -speed; // make speed a positive quantity
    reverse = 1;    // preserve the direction
  }
  if (speed > 254)  // Max
    speed = 254;
       
    
  switch (MotorNumber) {
  case 1:  
    if(reverse ^ flipM1)
    {
        analogWrite(M1_PWM,speed);
        digitalWrite(M1_DIR,HIGH);  
    }
    else
    {
        analogWrite(M1_PWM,speed);
        digitalWrite(M1_DIR,LOW);  
    }    
    break;
  case 2:
   if(reverse ^ flipM2)
    {
        analogWrite(M2_PWM,speed);
        digitalWrite(M2_DIR,HIGH);  
    }
    else
    {
        analogWrite(M2_PWM,speed);
        digitalWrite(M2_DIR,LOW);  
    }
    break;
  case 3:
     if(reverse ^ flipM3)
    {
        analogWrite(M3_PWM,speed);
        digitalWrite(M3_DIR,HIGH);  
    }
    else
    {
        analogWrite(M3_PWM,speed);
        digitalWrite(M3_DIR,LOW);  
    }
    break;
  case 4:
     if(reverse ^ flipM4)
    {
        analogWrite(M4_PWM,speed);
        digitalWrite(M4_DIR,HIGH);  
    }
    else
    {
        analogWrite(M4_PWM,speed);
        digitalWrite(M4_DIR,LOW);  
    }
    break;
  default:
    break;
  }   
 
}

void ZeroMotors::motorControl(int MotorNumber,int speed, uint8_t boardVersion)
{
	if (boardVersion == BOARD_PRO_V11) {
  init(boardVersion); // initialize if necessary

  boolean reverse = 0;

  if (speed < 0)
  {
    speed = -speed; // make speed a positive quantity
    reverse = 1;    // preserve the direction
  }
  if (speed > 254)  // Max
    speed = 254;
       
    
  switch (MotorNumber) {
  case 1:  
    if(reverse ^ flipM1)  
    {
        analogWrite(M1_PWM_M,speed);
        digitalWrite(M1_PWM_P,LOW);  
    }
    else  
    {
        analogWrite(M1_PWM_P,speed);
        digitalWrite(M1_PWM_M,LOW);  
    }    
    break;
  case 2:
   if(reverse ^ flipM2)  
    {
        analogWrite(M2_PWM_M,speed);
        digitalWrite(M2_PWM_P,LOW);  
    }
    else
    {
        analogWrite(M2_PWM_P,speed);
        digitalWrite(M2_PWM_M,LOW);  
    }
    break;
  case 3:
     if(reverse ^ flipM3)
    {
        analogWrite(M3_PWM_M,speed);
        digitalWrite(M3_PWM_P,LOW);  
    }
    else
    {
        analogWrite(M3_PWM_P,speed);
        digitalWrite(M3_PWM_M,LOW);  
    }
    break;
  case 4:
     if(reverse ^ flipM4)
    {
        analogWrite(M4_PWM_M,speed);
        digitalWrite(M4_PWM_P,LOW);  
    }
    else
    {
        analogWrite(M4_PWM_P,speed);
        digitalWrite(M4_PWM_M,LOW);  
    }
    break;
  default:
    break;
  }   
 }
 else if (boardVersion == BOARD_PRO) {
 	init(); // initialize if necessary

  boolean reverse = 0;

  if (speed < 0)
  {
    speed = -speed; // make speed a positive quantity
    reverse = 1;    // preserve the direction
  }
  if (speed > 254)  // Max
    speed = 254;
       
    
  switch (MotorNumber) {
  case 1:  
    if(reverse ^ flipM1)
    {
        analogWrite(M1_PWM,speed);
        digitalWrite(M1_DIR,HIGH);  
    }
    else
    {
        analogWrite(M1_PWM,speed);
        digitalWrite(M1_DIR,LOW);  
    }    
    break;
  case 2:
   if(reverse ^ flipM2)
    {
        analogWrite(M2_PWM,speed);
        digitalWrite(M2_DIR,HIGH);  
    }
    else
    {
        analogWrite(M2_PWM,speed);
        digitalWrite(M2_DIR,LOW);  
    }
    break;
  case 3:
     if(reverse ^ flipM3)
    {
        analogWrite(M3_PWM,speed);
        digitalWrite(M3_DIR,HIGH);  
    }
    else
    {
        analogWrite(M3_PWM,speed);
        digitalWrite(M3_DIR,LOW);  
    }
    break;
  case 4:
     if(reverse ^ flipM4)
    {
        analogWrite(M4_PWM,speed);
        digitalWrite(M4_DIR,HIGH);  
    }
    else
    {
        analogWrite(M4_PWM,speed);
        digitalWrite(M4_DIR,LOW);  
    }
    break;
  default:
    break;
  }   
 }
}

void ZeroMotors::configMotor(int left_motor,int right_motor)
{
       
  switch (left_motor) {
  case M1:  
    left_PWM = M1_PWM;
    left_DIR = M1_DIR;
    break;
  case M2:
      left_PWM = M1_PWM;
    left_DIR = M1_DIR;
    break;
  case M3:
    left_PWM = M1_PWM;
    left_DIR = M1_DIR;
    break;
  case M4:
    left_PWM = M1_PWM;
    left_DIR = M1_DIR;
    break;
  default:
    break;
  }   
  
  switch (right_motor) {
  case M1:  
    right_PWM = M1_PWM;
    right_DIR = M1_DIR;
    break;
  case M2:
    right_PWM = M1_PWM;
    right_DIR = M1_DIR;
    break;
  case M3:
    right_PWM = M1_PWM;
    right_DIR = M1_DIR;
    break;
  case M4:
    right_PWM = M1_PWM;
    right_DIR = M1_DIR;
    break;
  default:
    break;
  }  

}

void ZeroMotors::configMotor(int left_motor,int right_motor,uint8_t boardVersion)
{
  if (boardVersion == BOARD_PRO_V11) {    
  switch (left_motor) {
  case M1:  
    left_PWM_P = M1_PWM_P;
    left_PWM_M = M1_PWM_M;
    break;
  case M2:
    left_PWM_P = M1_PWM_P;
    left_PWM_M = M1_PWM_M;
    break;
  case M3:
    left_PWM_P = M1_PWM_P;
    left_PWM_M = M1_PWM_M;
    break;
  case M4:
    left_PWM_P = M1_PWM_P;
    left_PWM_M = M1_PWM_M;
    break;
  default:
    break;
  }   
  
  switch (right_motor) {
  case M1:  
    right_PWM_P = M1_PWM_P;
    right_PWM_M = M1_PWM_M;
    break;
  case M2:
    right_PWM_P = M1_PWM_P;
    right_PWM_M = M1_PWM_M;
    break;
  case M3:
    right_PWM_P = M1_PWM_P;
    right_PWM_M = M1_PWM_M;
    break;
  case M4:
    right_PWM_P = M1_PWM_P;
    right_PWM_M = M1_PWM_M;
    break;
  default:
    break;
  }  
}
else if (boardVersion == BOARD_PRO) {
	switch (left_motor) {
  case M1:  
    left_PWM = M1_PWM;
    left_DIR = M1_DIR;
    break;
  case M2:
      left_PWM = M1_PWM;
    left_DIR = M1_DIR;
    break;
  case M3:
    left_PWM = M1_PWM;
    left_DIR = M1_DIR;
    break;
  case M4:
    left_PWM = M1_PWM;
    left_DIR = M1_DIR;
    break;
  default:
    break;
  }   
  
  switch (right_motor) {
  case M1:  
    right_PWM = M1_PWM;
    right_DIR = M1_DIR;
    break;
  case M2:
    right_PWM = M1_PWM;
    right_DIR = M1_DIR;
    break;
  case M3:
    right_PWM = M1_PWM;
    right_DIR = M1_DIR;
    break;
  case M4:
    right_PWM = M1_PWM;
    right_DIR = M1_DIR;
    break;
  default:
    break;
  }
}
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
  if (speed > 254)  // Max
    speed = 254;
    
    
    if(reverse ^flipM1)
    {
        analogWrite(left_PWM,speed);
        digitalWrite(left_DIR,HIGH);  
    }
    else
    {
        analogWrite(left_PWM,speed);
        digitalWrite(left_DIR,LOW);  
    }


}

void ZeroMotors::setLeftSpeed(int speed,uint8_t boardVersion)
{
	if (boardVersion == BOARD_PRO_V11) {
  init(boardVersion); // initialize if necessary

  boolean reverse = 0;

  if (speed < 0)
  {
    speed = -speed; // make speed a positive quantity
    reverse = 1;    // preserve the direction
  }
  if (speed > 254)  // Max
    speed = 254;
    
    
    if(reverse ^flipM1)
    {
        analogWrite(left_PWM_P,speed);
        digitalWrite(left_PWM_M,LOW);  
    }
    else
    {
        analogWrite(left_PWM_M,speed);
        digitalWrite(left_PWM_P,LOW);  
    }
  }
  else if (boardVersion == BOARD_PRO) {
  	init(); // initialize if necessary

  boolean reverse = 0;

  if (speed < 0)
  {
    speed = -speed; // make speed a positive quantity
    reverse = 1;    // preserve the direction
  }
  if (speed > 254)  // Max
    speed = 254;
    
    
    if(reverse ^flipM1)
    {
        analogWrite(left_PWM,speed);
        digitalWrite(left_DIR,HIGH);  
    }
    else
    {
        analogWrite(left_PWM,speed);
        digitalWrite(left_DIR,LOW);  
    }
  }

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
  if (speed > 254)  // Max PWM dutycycle
    speed = 254;

  if(reverse ^ flipM2)                                           
    {
        analogWrite(right_PWM,speed);
        digitalWrite(right_DIR,HIGH);  
    }
    else
    {
        analogWrite(right_PWM,speed);
        digitalWrite(right_DIR,LOW);  
    }

}

void ZeroMotors::setRightSpeed(int speed,uint8_t boardVersion)
{
	if (boardVersion == BOARD_PRO_V11) {
  init(boardVersion); // initialize if necessary

  boolean reverse = 0;

  if (speed < 0)
  {
    speed = -speed;  // Make speed a positive quantity
    reverse = 1;  // Preserve the direction
  }
  if (speed > 254)  // Max PWM dutycycle
    speed = 254;

  if(reverse ^ flipM2)                                           
    {
        analogWrite(right_PWM_P,speed);
        digitalWrite(right_PWM_M,LOW);  
    }
    else
    {
        analogWrite(right_PWM_M,speed);
        digitalWrite(right_PWM_P,LOW);  
    }
  }
  else if (boardVersion == BOARD_PRO) {
  	init(); // initialize if necessary

  boolean reverse = 0;

  if (speed < 0)
  {
    speed = -speed;  // Make speed a positive quantity
    reverse = 1;  // Preserve the direction
  }
  if (speed > 254)  // Max PWM dutycycle
    speed = 254;

  if(reverse ^ flipM2)                                           
    {
        analogWrite(right_PWM,speed);
        digitalWrite(right_DIR,HIGH);  
    }
    else
    {
        analogWrite(right_PWM,speed);
        digitalWrite(right_DIR,LOW);  
    }
  }
}

// set speed for both motors
void ZeroMotors::setSpeeds(int leftSpeed, int rightSpeed)
{
  setLeftSpeed(leftSpeed);
  setRightSpeed(rightSpeed);
}

void ZeroMotors::setSpeeds(int leftSpeed, int rightSpeed, uint8_t boardVersion)
{
	if (boardVersion == BOARD_PRO_V11) {
  setLeftSpeed(leftSpeed,boardVersion);
  setRightSpeed(rightSpeed,boardVersion);
  }
  else if (boardVersion == BOARD_PRO) {
  	setLeftSpeed(leftSpeed);
  setRightSpeed(rightSpeed);
  }
}

void ZeroMotors::forward(int speed)
{
  setLeftSpeed(speed);
  setRightSpeed(-speed);
}

void ZeroMotors::forward(int speed,uint8_t boardVersion)
{
	if (boardVersion == BOARD_PRO_V11) {
  setLeftSpeed(speed,boardVersion);
  setRightSpeed(-speed,boardVersion);
  }
  else if (boardVersion == BOARD_PRO) {
  setLeftSpeed(speed);
  setRightSpeed(-speed);
  }
}
void ZeroMotors::backward(int speed)
{
  setLeftSpeed(-speed);
  setRightSpeed(speed);
}

void ZeroMotors::backward(int speed,uint8_t boardVersion)
{
	if (boardVersion == BOARD_PRO_V11) {
  setLeftSpeed(-speed,boardVersion);
  setRightSpeed(speed,boardVersion);
  }
  else if (boardVersion == BOARD_PRO) {
  setLeftSpeed(-speed);
  setRightSpeed(speed);
  }
}
void ZeroMotors::turnRight(int speed)
{
	setLeftSpeed(speed);
  setRightSpeed(speed);
}
void ZeroMotors::turnRight(int speed,uint8_t boardVersion)
{
  if (boardVersion == BOARD_PRO_V11) {
  setLeftSpeed(speed,boardVersion);
  setRightSpeed(speed,boardVersion);
  }
  else if (boardVersion == BOARD_PRO) {
  setLeftSpeed(speed);
  setRightSpeed(speed);
  }
}

void ZeroMotors::turnLeft(int speed)
{
  setLeftSpeed(-speed);
  setRightSpeed(-speed);
}
void ZeroMotors::turnLeft(int speed,uint8_t boardVersion)
{
	if (boardVersion == BOARD_PRO_V11) {
  setLeftSpeed(-speed,boardVersion);
  setRightSpeed(-speed,boardVersion);
  }
  else if (boardVersion == BOARD_PRO) {
  setLeftSpeed(-speed);
  setRightSpeed(-speed);
  }
}

void ZeroMotors::stop()
{
  setLeftSpeed(0);
  setRightSpeed(0);
}

void ZeroMotors::stop(uint8_t boardVersion)
{
	if (boardVersion == BOARD_PRO_V11) {
  setLeftSpeed(0,boardVersion);
  setRightSpeed(0),boardVersion;
  }
  else if (boardVersion == BOARD_PRO) {
  setLeftSpeed(0);
  setRightSpeed(0);
  }
}