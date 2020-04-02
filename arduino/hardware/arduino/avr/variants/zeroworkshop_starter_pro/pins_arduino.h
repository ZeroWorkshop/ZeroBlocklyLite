/*
  pins_arduino.h - Pin definition functions for Arduino
  Part of Arduino - http://www.arduino.cc/

  Copyright (c) 2007 David A. Mellis

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA
*/

#include "../standard/pins_arduino.h"
#define ROBOTCOM_REVA  

/****************************************************************/
/******  PIN DEFINITION FOR ROBOTCOM_REVA with I2C CPU BOARD ******/
/****************************************************************/
#ifdef  ROBOTCOM_REVA       //Pins below are for Kim level 1
#define ZW_A1 A0
#define ZW_A2 A1
#define ZW_A3 A4
#define ZW_A4 A5

#define ZW_B1 A2
#define ZW_B2 A3
#define ZW_B3 2
#define ZW_B4 7

#define MOTOR1P 3
#define MOTOR1M 13
#define MOTOR2P 5
#define MOTOR2M 12
#define MOTOR3P 11
#define MOTOR3M 10
#define MOTOR4P 6
#define MOTOR4M 9

#define START_BUTTON 4
#define ENA     0
#define ENB     0     //dummy defintions

#define INPUT_VALUE_BT1 !digitalRead(BT1)
#define INPUT_VALUE_BT2 !digitalRead(BT2)
#define INPUT_VALUE_BT3 !digitalRead(BT3)
#define INPUT_VALUE_BT4 !digitalRead(BT4)
#define Left_Fist_SERVO  ZW_B2
#define Right_Fist_SERVO  ZW_B1

#define BuzzerPin  8
#define SpeakerPIN 8

#define IR_IN1   A0
#define IR_IN2   A1
#define IR_IN3   A4
#define IR_IN4   A5

#define LED_A2   0
#define LED_A3   0
#define LED_9    0
#endif
/****************************************************************/
/*****  END OF PIN DEFINITION FOR ROBOTCOM_REVA CPU BOARD *******/
/****************************************************************/


#undef NUM_ANALOG_INPUTS
#define NUM_ANALOG_INPUTS           8
