/*! \file ZumoMotors.h
 *
 * See the ZumoMotors class reference for more information about this library.
 *
 * \class ZumoMotors ZumoMotors.h
 * \brief Control motor speed and direction
 *
 */

#ifndef ZeroMotors_h
#define ZeroMotors_h

#include <Arduino.h>
#define _PWM_L_  5
#define _PWM_R_  6
#define _DIR_L_  12
#define _DIR_R_  9

class ZeroMotors
{
  public:

    
    // constructor (doesn't do anything)
    //ZeroMotors();     
    ZeroMotors(uint8_t pwm_1 = _PWM_L_,uint8_t dir_1=_DIR_L_,uint8_t pwm_2 = _PWM_R_,uint8_t dir_2= _DIR_R_) ;

    // enable/disable flipping of motors
     void flipLeftMotor(boolean flip);
     void flipRightMotor(boolean flip);

    // set speed for left, right, or both motors
     void setLeftSpeed(int speed);
     void setRightSpeed(int speed);
     void setSpeeds(int leftSpeed, int rightSpeed);

  private:
  
    int PWM_L;
    int PWM_R;
    int DIR_L;
    int DIR_R;

     inline void init()
    {
      static boolean initialized = false;

      if (!initialized)
      {
        initialized = true;
        init2();
      }
    }

    // initializes timer1 for proper PWM generation
     void init2();
};

#endif