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
    
    ZeroMotors(uint8_t pwm_1 ,uint8_t dir_1,uint8_t pwm_2 ,uint8_t dir_2, uint8_t boardVersion) ;
    // enable/disable flipping of motors
     void flipM1Motor(boolean flip);
     void flipM2Motor(boolean flip);
     void flipM3Motor(boolean flip);
     void flipM4Motor(boolean flip);
     
    
   
     void  motorControl(int MotorNumber,int speed);
     void  motorControl(int MotorNumber,int speed,uint8_t boardVersion);
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
   
     void configMotor(int left_motor,int right_motor,uint8_t boardVersion);  // default use M1 and M2
     void setLeftSpeed(int speed,uint8_t boardVersion);
     void setRightSpeed(int speed,uint8_t boardVersion);
     void setSpeeds(int leftSpeed, int rightSpeed,uint8_t boardVersion);
     void forward(int speed = 255,uint8_t boardVersion = BOARD_VERSION);
     void turnRight(int speed = 255,uint8_t boardVersion = BOARD_VERSION);
     void turnLeft(int speed = 255,uint8_t boardVersion = BOARD_VERSION);
     void backward(int speed = 255,uint8_t boardVersion = BOARD_VERSION);
     void stop(uint8_t boardVersion);

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
    
    int M1_PWM_P;
    int M1_PWM_M;
    
    int M2_PWM_P;
    int M2_PWM_M;
    
    int M3_PWM_P;
    int M3_PWM_M;
    
    int M4_PWM_P;
    int M4_PWM_M;
    
    
    int left_PWM_P;
    int left_PWM_M;
    int right_PWM_P;
    int right_PWM_M;
    
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
    
    inline void init(uint8_t boardVersion)
    {
      static boolean initialized = false;

      if (!initialized)
      {
        initialized = true;
        init2(boardVersion);
      }
    }

    // initializes timer1 for proper PWM generation
     void init2();
     void init2(uint8_t boardVersion);
};

#endif