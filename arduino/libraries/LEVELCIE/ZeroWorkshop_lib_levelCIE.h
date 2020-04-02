
#ifndef ZeroWorkshop_lib_h
#define ZeroWorkshop_lib_h
#include "ZeroWorkshop_lib_levelCIE.h"
//#include "ZeroWorkshop_Macro_Definitions.h"
#include <math.h> 
#include <stdio.h>
#include <Arduino.h>
#include <Servo.h>
#include <Adafruit_NeoPixel.h>
#include <string.h>
#include <Wire.h>
//#include <EasyButton.h>
#include "Adafruit_TCS34725.h"
#include <EEPROM.h>



#if 1
void motor_speed_fillings(int MotorNumber, int RunningStatus,double speedValue );

void MotorControl(int MotorNumber, int RunningStatus,int speedValue);

void motor_changeSpeed(int MotorNumber, int RunningStatus,double speedValue ,double *current);

void Left_Motor(long direction);

void VoiceWord(int idx , int arg1 , int arg2);

void Right_Motor(long direction);


void setRightSpeed(int speed);


boolean checkBolls(char bollChoosed);

void setLeftSpeed(int speed);


void goForward ();


void goReverse();


void goLeftTurn();

boolean isAuto();

void goRightTurn();

void levelS();

void on(int zwB1);

void on(int zwB1, int zwB2);

void on(int zwB1, int zwB2, int zwB3);

void on(int zwB1, int zwB2, int zwB3, int zwB4);

void off(int zwB1);

void off(int zwB1, int zwB2);

void off(int zwB1, int zwB2, int zwB3);

void off(int zwB1, int zwB2, int zwB3, int zwB4);

void default_prog(int *ProgSelected);
void lesson_1_interrupt();

void lesson_1();

void lesson_2();

void lesson_3();

void lesson_4();

void lesson_5();

void lesson_6();

void lesson_7();

void lesson_8();

void lesson_9();

void lesson_10();

void lesson_11();

void goBrake();

void leftLightFlash();

void leftLightOn();

void leftLightOff();

void rightLightFlash();

void loadingCarriage(Servo carrriage_servo);

void unloadingCarriage(Servo carrriage_servo);

void rightLightOn();

void rightLightOff();

void pull_another();

void pull_another2();

void rearLightFlash();

void rearLightOn();

void rearLightOff();

void onRedLED();

void yellowLEDOn(int whichLamp);

void offLED(int whichLampOff);

void left_turn_speed(int speed);

void servoChange(Servo Self_servo,  double *ang , double angleValue, double maxValue);

void optionalServeAng(Servo oServo, double ang);

void right_turn_speed(int speed);

void go_forward_speed(int speed);

void go_reverse_speed(int speed);

void indicatorLightRun(bool runFlag ,int pin, double *ang) ;

int getSensorDistance(int pinOut);

void optionalServeAng(Servo oServo, double ang);

bool PS2_RF_Button(uint16_t ButtonPressed);

void servoTurnto( Servo Self_servo, double Servoangle);

bool PS2_RF_ReadButton(int *Button_Buffer);

void playNote(int Note,int Meter,int Length);

void playNoteShort(int Note,int Meter,int Length);

void playSong(int songSelected);

void PanMoveClockwise(Servo myservo, double *Pos);

void PanMoveCounterclockwise(Servo myservo, double *Pos);

void TiltMoveUp(Servo myservo, double *Pos);

void TiltMoveDown(Servo myservo, double *Pos);

void StartProgram(int *ProgramSelector);

void servopulse(int servopin, int angle);

void ServoSteeringLeft(Servo steer_servo1, Servo steer_servo2, double *Pos);

void ServoSteeringRight(Servo steer_servo1, Servo steer_servo2, double *Pos);

void ServoSteeringCenter(Servo steer_servo1, Servo steer_servo2, double *Pos);

void ActionGrab(Servo arm_servo, Servo hand_servo);


void ActionPut(Servo arm_servo, Servo hand_servo);

void TailControlUp(Servo tail_servo, double *tail_position);

void TailControlDown(Servo tail_servo, double *tail_position);
void throwTheBall(Servo B1_mian_servo, Servo B2_throw_servo);

void filterTheBall(Servo B1_mian_servo, Servo B2_throw_servo);

void leftPunches(Servo left_fist_servo);

void leftTakeAFist(Servo left_fist_servo);

void rightPunches(Servo right_fist_servo);

void rightTakeAFist(Servo right_fist_servo);

void ArmControlUp(Servo arm_servo, double *arm_position);


void ArmControlDown(Servo arm_servo, double *arm_position);


void ActionGrab_Liang(Servo arm_servo, Servo hand_servo);


void ActionPut_Liang(Servo arm_servo, Servo hand_servo);


void ArmControlUp_Liang(Servo arm_servo, double *arm_position);

void ArmControlDown_Liang(Servo arm_servo, double *arm_position);

void HandControlClose(Servo hand_servo, double *hand_position);


void HandControlOpen(Servo hand_servo, double *hand_position);


void LeftWheelForward();


void LeftWheelBackward();


void RightWheelForward();

void turnonlight();

void turnofflight();


void RightWheelBackward();

void LeftWheelForward_SpeedControl(int SpeedSet);


void LeftWheelBackward_SpeedControl(int SpeedSet);


void RightWheelForward_SpeedControl(int SpeedSet);


void RightWheelBackward_SpeedControl(int SpeedSet);

boolean howFollow(int LEFT_IR_SENSOR,int RIGHT_IR_SENSOR,int leftOne , int rightOne);

void changeFollowFlagTrue () ;

void changeFollowFlagFalse ();

void LeftWheelClockwise();        


void LeftWheelCounterClockwise();  


void RightWheelClockwise();        


void RightWheelCounterClockwise();  


void LeftWheelStop();

void VoiceNum(int num , int arg1 , int arg2);

void VoiceWord(int idx , int arg1 , int arg2);

void RightWheelStop();

void getServoAngleEEPROM(int *standbyPos);

void reloadAllBullets(Servo bulletLoader_servo);


void loadBullet(Servo bulletLoader_servo, int *bullet_left);


void fireBullet(Servo bulletTrigger_servo, Servo bulletLoader_servo, int *bullet_left);


void RubberbandFireSingle(Servo bulletLoader_servo, Servo bulletTrigger_servo, int *bullet_left);


void RubberbandFireAll(Servo bulletLoader_servo, Servo bulletTrigger_servo, int *bullet_left);


void TuningLoader(Servo Loader_servo, Servo Trigger_servo, int *bullet_left);

void FanRunning(int SelectSpeed, bool fanIsRunning);

void FanHeadMove(Servo fanHeadServo, bool allowFanHeadMoving, double *fanHeadPos);

void fanHeadPosition(Servo fanHeadZ_servo, int headPosition);

void loadBatteryBullet(Servo batterybulletLoader_servo, int *battery_left);

void fireBatteryBullet(Servo batterybulletTrigger_servo, int *battery_left);

void BatteryFireAll(Servo batterybulletLoader_servo, Servo batterybulletTrigger_servo, int *battery_left);

void BatteryFireSingle(Servo batterybulletLoader_servo, Servo batterybulletTrigger_servo, int *battery_left);

void resetScoreboard();

void scoreboardChange(int speedSel);

void checkBall(int selection, int SensorPin, int *Points);

void backboard_noMove(double *backboard_pos, Servo backboard_servo);

void backboard_slowMove(double *backboard_pos, Servo backboard_servo);

void backboard_fastMove(double *backboard_pos, Servo backboard_servo);

void backboardMove(int *points, Servo backboard_servo, double *backboard_pos, int backboard_nomove_sel, int backboard_slowmove_sel, int backboard_fastmove_sel);

void checkMouthTouch(int MouthSensorPin, Servo cathand_servo);

void checkHeadTouch(int HeadSensorPin);

void indicatorLightOff();

void radarStart(Servo radar_servo,  bool moveFlag , double *ang);

void lampMoveL(Servo lamp_servo,  double *angL);
void lampMoveR(Servo lamp_servo,  double *angL);
void chassisMoveL(Servo chassis_servo,  double *ang);
void chassisMoveR(Servo chassis_servo,  double *ang);

void lampMoveF(Servo lamp_servo,  double *ang);

void fire(Servo fire_servo,  double *ang);
void acc(Servo fire_servo,  double *ang);
void fired(Servo fire_servo,  double *ang);

void pull();
void pull2();


void RaptorCruise(Servo head_servo, double *head_pos, int *moving_direction);

void avoidObstacle(int RaptorSensorPin, int *head_moving_direction, double *raptorHead_pos, Servo head_servo);

void ControlLeftWheel(int LeftWheelButton, int BackwardButton);

void ControlRightWheel(int RightWheelButton, int BackwardButton);

void ControlTwoWheelBackward(int BackwardButton, int LeftWheelButton, int RightWheelButton);

void HammerKnock(Servo hammer_servo);

void checkIfAttacked(int *number_of_attacked, int AttackedSensor, int max_attacked_times);
extern bool firstRun;
void GreenOnAll();

void OneLED_RGB(uint8_t pixel, uint32_t c);

void FlashOneLED_RGB(int flash_speed, uint8_t pixel, uint32_t c);

void FlashOneLED_RGB(int flash_speed, uint8_t pixel, uint32_t c, int swap);

void FlashStrip1LED_RGB(int flash_speed, uint8_t pixel, uint32_t c);

void FlashStrip2LED_RGB(int flash_speed, uint8_t pixel, uint32_t c);

void policeLightWipe(int pix_num, int *pixel);

void Wipe();

void policeLightFlash(int pix_num, int flashSpeed, int swap);

void Strip1Flash(int pix_num, int flashSpeed);

void Strip2Flash(int pix_num, int flashSpeed);

void policeLightRun(int TotalPix, int *pixels);

void onGreenLED();

void onRedLED();

void onBlueLED();

void onYellowLED();

void offLED();

void TailSwing(Servo TServo, double *servo_pos);

void BirdTailSwing(int SensorButton, Servo TailServo, double *TailServoPos);

void BirdFollowTarget(int LeftSensor, int RightSensor);
#endif

#endif




