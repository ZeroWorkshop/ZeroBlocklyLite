
#ifndef ZeroWorkshop_lib_h
#define ZeroWorkshop_lib_h
#include "ZeroWorkshop_lib.h"
#include "ZeroWorkshop_Macro_Definitions.h"
#include <math.h> 
#include <stdio.h>
#include <Arduino.h>
#include <Servo.h>
#include <Adafruit_NeoPixel.h>
#include <string.h>
#include <Wire.h>
#include <EasyButton.h>
#include "Adafruit_TCS34725.h"
#include <EEPROM.h>
#ifndef __HX711__H__
#define __HX711__H__

#include <Arduino.h>

#define HX711_SCK A0
#define HX711_DT A1

#include <OneWire.h>
#include <DallasTemperature.h>
extern void Init_Hx711();
extern unsigned long HX711_Read(void);
extern long Get_Weight();
extern void Get_Maopi();

#endif

#if 1

double readInfraredDistanceValueSBT(int dropdown_IR);

bool getTemperatureSBT(double min,double max);

double returnUltrasonicValueSBT(int pin);

bool readInfraredDistanceSBT(int dropdown_IR , int min , int max);

bool getUltrasonicSBT(int pin , int min , int max ) ;

double getTemperatureValueSBT(OneWire TempSensor);

bool singleServo(double speed,int radius,Servo servo,double *ang);

bool singleServoPD(double angleValue,int maxValue,Servo Self_servo,double *ang);


void MultipleServoSet(double b1s,int b1r,double b2s,int b2r,double b3s, int b3r,double b4s,int b4r,double a1s ,int a1r,double a2s ,int a2r,double a3s,int a3r,double a4s,int a4r,double *angb1,double *angb2,double *angb3,double *angb4,double *anga1,double *anga2,double *anga3,double *anga4,Servo Pb1,Servo Pb2,Servo Pb3,Servo Pb4,Servo Pa1,Servo Pa2,Servo Pa3,Servo Pa4);

void MultipleServoSetPD(double b1s,int b1r,double b2s,int b2r,double b3s, int b3r,double b4s,int b4r,double a1s ,int a1r,double a2s ,int a2r,double a3s,int a3r,double a4s,int a4r,double *angb1,double *angb2,double *angb3,double *angb4,double *anga1,double *anga2,double *anga3,double *anga4,Servo Pb1,Servo Pb2,Servo Pb3,Servo Pb4,Servo Pa1,Servo Pa2,Servo Pa3,Servo Pa4);

void MultipleMotorSet(int m1Speed, int m2Speed,int m3Speed,int m4Speed,int time);

void VoiceWord(int idx , int arg1 , int arg2);

void VoiceNum(int num , int arg1 , int arg2);

void motor_speed_fillings(int MotorNumber, int RunningStatus,double speedValue );

void lesson_3();

void motor(int Left_speed, int Right_speed, double delayT);

void MotorControlTime(int MotorNumber, int RunningStatus,int speedValue,int timeValue);

long Get_Weight();

void Get_Maopi();

float pressureTransducer ( );

void optional_LED ( int pin , int state);

void servoIncrementPro(Servo Self_servo,  double *ang , double angleValue , double limitValue);

float readInfraredDistance_single(int dropdown_IR );

void danceStop();

void dance(Servo B1_servo , double *b1ServoPos  ,Servo B2_servo , double *b2ServoPos);

double getTemperatureValue();

void wagTheTail(Servo B1_servo , double *tailPos);

void servoIncrement(Servo Self_servo,  double *ang , double angleValue);

bool getUltrasonic(int min , int max ) ;

void custom_lamp (int lampNumber , int lampColor ,int lampPinNumber) ;

bool getTemperature(double min,double max ,int relation);

float getTemperatureVal(int Sensor);

bool readInfraredDistance( int min , int max , int relation);

void MotorControl(int MotorNumber, int RunningStatus,int speedValue);

void servoSpeedTurnto(Servo Self_servo, double toAngle  ,   double speed,   double *ang);

void Left_Motor(long direction);


void Right_Motor(long direction);


void setRightSpeed(int speed);


boolean checkBolls(char bollChoosed);

void setLeftSpeed(int speed);


void goForward ();


void goReverse();


void goLeftTurn();

#ifdef ROBOTCOM_REVA
void goForwardRight();

void goForwardLeft();

void goReverseRight();

void goReverseLeft();
#endif

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

void handlebar(Servo Self_servo,  double *ang , double angleValue, double maxValue);

void shovel(Servo Self_servo,  double *ang , double angleValue, double maxValue);

void forkliftLampOn (int num);

void forkliftTopLampOn (int num);

void motorbikeDirectionReturnBack(Servo Self_servo, double *ang);

void carTopLight (int lampsNum);

void skLight();

void defaultLight(int num,int PartNum);

void arm(Servo Self_servo,  double *ang , double angleValue, double maxValue);

void optionalServeAng(Servo oServo, double ang);

void right_turn_speed(int speed);

void go_forward_speed(int speed);

void go_reverse_speed(int speed);

void indicatorLightRun(bool runFlag ,int pin, double *ang) ;

void optionalServeAng(Servo oServo, double ang);

bool PS2_RF_Button(uint16_t ButtonPressed);

void servoTurnto( Servo Self_servo, double Servoangle);

void MultLEDLampOn (int  whichColor) ;

void MultLEDLampOff (int num) ;

void LEDLampOn (int  whichColor) ;

void LEDLampOff (int num) ;

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

void fanHeadPosition(Servo fanHeadZ_servo, int headPosition , double *fanHeadPosition);

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




