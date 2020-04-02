/*
  moto_4wd_dfs.h
  2012 Copyright (c) Seeed Technology Inc.  All right reserved.

  Author: Loovee

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
#ifndef __ZEROMOTORDRIVER_DFS_H__
#define __ZEROMOTORDRIVER_DFS_H__


//#define LevelFOURV1.0
//#define LevelFOURV2.0

#define BUFSIZE    128

#define FREQPWM         10000       // 10khZ

//For RF Remote controller
#define ButtonUp        (0x10 & PS2_Button_Read[2])
#define ButtonRight     (0x20 & PS2_Button_Read[2])
#define ButtonDown      (0x40 & PS2_Button_Read[2])
#define ButtonLeft      (0x80 & PS2_Button_Read[2])
#define ButtonTriangle  (0x10 & PS2_Button_Read[3])
#define ButtonCircle    (0x20 & PS2_Button_Read[3])
#define ButtonCross     (0x40 & PS2_Button_Read[3])
#define ButtonSquare    (0x80 & PS2_Button_Read[3])
#define ButtonL1        (0x4 & PS2_Button_Read[3])
#define ButtonL2        (0x1 & PS2_Button_Read[3])
#define ButtonR1        (0x8 & PS2_Button_Read[3])
#define ButtonR2        (0x2 & PS2_Button_Read[3])
#define ButtonSelect    (0x1 & PS2_Button_Read[2])
#define ButtonStart     (0x8 & PS2_Button_Read[2])



// order SEND
#define RETM1SPEED      0x87
#define RETM2SPEED      0x88
#define RETM3SPEED      0x89
#define RETM4SPEED      0x86
#define RETM1STATE      0x90
#define RETM2STATE      0x91
#define RETM1STATE      0x92
#define RETM2STATE      0x93


// motor state
#define STOP            0x00        // motor stop
#define RUN             0x01        // motor run

#define DIRF            0x00        // Forward
#define DIRR            0x01        // Reversion



#ifdef LevelFOURV1.0

// pin ctrl

#define MOTOR1P 9
#define MOTOR1M 5
#define MOTOR2P 3
#define MOTOR2M 6
#define MOTOR3P 10
#define MOTOR3M 12
#define MOTOR4P 11
#define MOTOR4M 8



#define ZW_L1 A3
#define ZW_L2 A2
#define ZW_L3 A1
#define ZW_L4 A0


#define ZW_R1 0 //13  //PB5
#define ZW_R2 1
#define ZW_R3 2     //TX
#define ZW_R4 13  //RX

#define ZW_BEEP  7 //PD6

#define ZW_START 4

#endif



/***  Register Map ****/
#define StatusReg     0x01
#define PWMFreq       0x02
#define DirectionSet  0x03
#define SpeedSet      0x04


///// Para 1
//only 1 motor
#define M1   0x01     //D9
#define M2   0x02     //D10
#define M3   0x04     //D11
#define M4   0x08     //D3

//two motor3
#define M1M2   0x03
#define M1M3   0x05
#define M1M4   0x09
#define M2M3   0x06
#define M2M4   0x0A
#define M3M4   0x0C

// three motors
#define M3M2M1   0x07
#define M4M2M1   0x0B
#define M4M3M2   0x0E
#define M4M3M1   0x0D

//four motors
#define M4M3M2M1   0x0F

/*
     M4 M3 M2 M1
     0  0  0  0     None motor selected
     0  0  0  1     M1 only
     0  0  1  0     M2 only
     0  0  1  1     M1 and M2
     0  1  0  0     M3 only
     0  1  0  1     M3 and M1
     0  1  1  0     M3 and M2
     0  1  1  1     M1 M2 and M3
     1  0  0  0     M4 only
     1  0  0  1     M4 and M1
     1  0  1  0     M4 and M2
     1  0  1  1     M1 M2 and M4
     1  1  0  0     M3 and M4
     1  1  0  1     M1 M3 and M4
     1  1  1  0     M2 M3 and M4
     1  1  1  1     M1 M2 M3 and M4
*/




//para2  Motor direction

//for Direction
#define CW  0x00
#define ACW 0x01

//for PWM frequency
#define F_31372Hz    0x01
#define F_3921Hz     0x08
#define F_490Hz      0x40  //64
#define F_122Hz      0x100  //256
#define F_30Hz       0x400  //1024



/*
 * if we recieve I2C COMMAND AS BWLOW
    0x02  0x0F  0x01   //  set All motor's PWM frequency to 31372Hz
    0x03  0x01  0x00   //  Set motor 1 drection as clockwise
    0x03  0x02  0x01   //  set motor 2 drection as anti-clockwsie
    0x03  0x04  0x00   //  set motor 3 direction as clock wise
    0x03  0x08  0x01   //  set motor 4 direction as anti-clockwise
    0x03  0x03  0x01   //  set motor 1 and 2  direction as clockwise
    0x04  0x0f  0xFF  //  set the speed of all motor to 0xFF
*/


#endif
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/