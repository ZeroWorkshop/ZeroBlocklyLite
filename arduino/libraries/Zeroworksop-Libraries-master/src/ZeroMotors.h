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
#include <StarterPro.h>
#include <Arduino.h>


class ZeroMotors
{
  public:

    
    // constructor (doesn't do anything)
    ZeroMotors();     
    ZeroMotors(uint8_t pwm_1 ,uint8_t dir_1,uint8_t pwm_2 ,uint8_t dir_2) ;
    ZeroMotors(uint8_t pwm_1,uint8_t dir_1,uint8_t pwm_2 ,uint8_t dir_2,
               uint8_t pwm_3,uint8_t dir_3,uint8_t pwm_4 ,uint8_t dir_4) ;

    // enable/disable flipping of motors
     void flipM1Motor(boolean flip);
     void flipM2Motor(boolean flip);
     void flipM3Motor(boolean flip);
     void flipM4Motor(boolean flip);
     
    
   
     void  motorControl(int MotorNumber,int speed);
    // set speed for left, right, or both motors
    
    
    // set speed for left, right, or both motors
     void configMotor(int left_motor,int right_motor);  // default use M1 and M2
     void setLeftSpeed(int speed);
     void setRightSpeed(int speed);
     void setSpeeds(int leftSpeed, int rightSpeed);
     void forward(int speed = 255);
     void turnRight(int speed = 255);
     void turnLeft(int speed = 255);
     void backward(int speed = 255);
     void stop();
   

  private:
  
    int M1_PWM;
    int M1_DIR;
    
    int M2_PWM;
    int M2_DIR;
    
    int M3_PWM;
    int M3_DIR;
    
    int M4_PWM;
    int M4_DIR;
    
    
    int left_PWM;
    int left_DIR;
    int right_PWM;
    int right_DIR;
    
    
    boolean flipM1;// = true;
    boolean flipM2;// = true;
    boolean flipM3; //= true;
    boolean flipM4;// = true;

  

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