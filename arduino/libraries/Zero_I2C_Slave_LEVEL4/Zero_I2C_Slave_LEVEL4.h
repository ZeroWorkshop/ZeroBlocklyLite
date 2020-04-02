/*
  Zero_LEVEL4.h
  2017 Copyright (c) ZeroWorkshop Corp.  All right reserved.

  Author: Lyell

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

*/
#ifndef __ZEROMOTORDRIVER_H__
#define __ZEROMOTORDRIVER_H__

#include "ZeroMotorDriver_dfs.h"
#include <Servo.h>
#include <DES.h>
#include <SoftPWM.h>
#include <EEPROM.h>

#define DEBUG 0


//static void (*reset_this_CPU)(void) = 0x0000; // ***濠㈣泛绉崇紞鍛村嫉閻濈睌U闁告垼濮ら弳鐔煎箰閸ヮ剚瀚�

struct ProgNumInEPROM {
  int lastProgSelected;
};

class ZeroLEVEL4: public Servo
{

	public:
	int _ZW_L1_;//pin of L1
	int _ZW_L2_;//pin of L2
	int _ZW_L3_;//pin of L3
	int _ZW_L4_;//pin of L4

	int _ZW_R1_;//pin of R1
	int _ZW_R2_;//pin of R2
	int _ZW_R3_;//pin of R3
	int _ZW_R4_;//pin of R4

	int _ZW_BEEP_;
	int _ZW_START_;

	int  Rev;

    String LeftFront;
	String LeftRear;
	String RightFront;
	String RightRear;


    private:




	int _ZW_M1_P_;
	int _ZW_M1_N_;
	int _ZW_M2_P_;
	int _ZW_M2_N_;
	int _ZW_M3_P_;
	int _ZW_M3_N_;
	int _ZW_M4_P_;
	int _ZW_M4_N_;





	int ButtonState;                    // variable to store button state

	int lastButtonState;

	int ProgramSelector;

	bool KeepOnReadButton;

	bool ReadButtonState;

	long ButtonInterval = 2000;

	long startTime ;                    // start time for stop watch

	long elapsedTime ;                  // elapsed time for stop watch

	int NumberOfProgram;
    unsigned char motorSpeed1;      // pwm: 0-100
    unsigned char motorSpeed2;      // pwm: 0-100
    unsigned char motorSpeed3;      // pwm: 0-100
    unsigned char motorSpeed4;      // pwm: 0-100

    unsigned char motorDir1;
    unsigned char motorDir2;
    unsigned char motorDir3;
    unsigned char motorDir4;

    unsigned char motorState1;
    unsigned char motorState2;
    unsigned char motorState3;
    unsigned char motorState4;

    int motorPWMFreq1;
    int motorPWMFreq2;
    int motorPWMFreq3;
    int motorPWMFreq4;

    int EEPROM_MIN_ADDR;
    int EEPROM_MAX_ADDR;

    int eeAddr_RUBERBAND_LOADER;// 0           //define the EEPROM start address from where the servo position is saved

	int eeAddr_LEVEL1_DEFAULT_PROG ;//    100      //define the EEPROM start address from where the default prog(last time selected) number is saved


    DES des;
    public:

    Servo servo0;
    Servo servo1;
    Servo servo2;
    Servo servo3;


	int buffer_index = 0;


	ZeroLEVEL4::ZeroLEVEL4(int Rev);
    void StartProgram(int *ProgramSelector);
   // void playNote(int Note, int Meter, int Length);
   // void playSong(int songSelected);

    void init();
	void setMotor(String LF,String LR, String RF, String RR);

	void setLeftFrontMotor	(String motor,int ispeed,unsigned char dir);
	void setLeftRearMotor	(String motor,int ispeed,unsigned char dir);
	void setRightFrontMotor	(String motor,int ispeed,unsigned char dir);
	void setRightRearMotor	(String motor,int ispeed,unsigned char dir);

	void goForward	(int ispeed = 255);
	void goLeftTurn	(int ispeed = 255);
	void goRightTurn(int ispeed = 255);
	void goReverse	(int ispeed = 255);
	void goBrake();
	
	void goForwardSingleMotor	(int ispeed = 255);
	void goLeftTurnSingleMotor	(int ispeed = 255);
	void goRightTurnSingleMotor(int ispeed = 255);
	void goReverseSingleMotor	(int ispeed = 255);
	void goBrakeSingleMotor();

    void setStop1();
    void setStop2();
    void setStop3();
    void setStop4();


    void setSpeed1(int ispeed);       // pwm, 0-100
    void setSpeed2(int ispeed);       // pwm, 0-100
    void setSpeed3(int ispeed);       // pwm, 0-100
    void setSpeed4(int ispeed);       // pwm, 0-100

    void setDir1(unsigned char dir);
    void setDir2(unsigned char dir);
    void setDir3(unsigned char dir);
    void setDir4(unsigned char dir);

    void setSpeedDir(int ispeed, unsigned char dir);
    void setSpeedDir1(int ispeed, unsigned char dir);
    void setSpeedDir2(int ispeed, unsigned char dir);
    void setSpeedDir3(int ispeed, unsigned char dir);
    void setSpeedDir4(int ispeed, unsigned char dir);


    void setPwm(char pin, int ispeed,int frequency );
    void setPwmfrequency(char  pin, int divisor);


	void SetDirection(int MotorSet, int Direction);
	void SetSpeed(int MotorSet, int Speed);
	//void toneMolody();

	//Access eeprom
	boolean eeprom_is_addr_ok(int addr) ;
	boolean eeprom_write_bytes(int startAddr, const byte* array, int numBytes) ;
	boolean eeprom_write_string(int addr, const char* string) ;
	boolean eeprom_read_string(int addr, char* buffer, int bufSize);

	void Encryption(const char* string);
	boolean Decryption(char* string);

	bool PS2_RF_ReadButton(int *Button_Buffer);

	long UltrasonicSensor(int pin);

	void ServoInit(int pin);
	void ServoWrite(int pos);





};

extern ZeroLEVEL4 LEVEL4;

#endif
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/


