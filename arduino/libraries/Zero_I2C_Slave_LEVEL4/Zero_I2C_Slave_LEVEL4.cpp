/*
  moto_4wd.cpp
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

#include <Arduino.h>


#include "pitches.h"
#include "Zero_I2C_Slave_LEVEL4.h"


ZeroLEVEL4::ZeroLEVEL4(int Revision)
{
	Rev = Revision;
	if(Rev == 1)
	{
	_ZW_L1_ =A3;//pin of L1
	_ZW_L2_	=A2;//pin of L2
	_ZW_L3_	=A1;//pin of L3
	_ZW_L4_	=A0;//pin of L4

	_ZW_R1_	=0;//pin of R1
	_ZW_R2_	=1;//pin of R2
	_ZW_R3_	=2;//pin of R3
	_ZW_R4_	=13;//pin of R4

	_ZW_M1_P_	=9;
	_ZW_M1_N_	=5;
	_ZW_M2_P_	=3;
	_ZW_M2_N_	=6;
	_ZW_M3_P_	=10;
	_ZW_M3_N_	=12;
	_ZW_M4_P_	=11;
	_ZW_M4_N_	=8;

	_ZW_BEEP_	=7;
	_ZW_START_	=4;

	LeftFront 	= "M1";
	LeftRear  	= "M2";
	RightFront 	= "M3";
	RightRear	= "M4";
	}

	if(Rev == 2)
	{
	_ZW_L1_ = 4;//pin of L1   B1
	_ZW_L2_	= 5;//pin of L2   B2
	_ZW_L3_	= 6;//pin of L3   B3
	_ZW_L4_	= 7;//pin of L4   B4

    _ZW_R1_ =A2;//pin of R3   A1
    _ZW_R2_	=A3;//pin of R4   A2
	_ZW_R3_	=A4;//pin of R1   A3
	_ZW_R4_	=A5;//pin of R2   A4

	_ZW_M1_P_	=3;
	_ZW_M1_N_	=A1;
	_ZW_M2_P_	=12;
	_ZW_M2_N_	=13;
	_ZW_M3_P_	=8;
	_ZW_M3_N_	=2;
	_ZW_M4_P_	=11;
	_ZW_M4_N_	=10;

	_ZW_BEEP_	= 9;
	_ZW_START_	=A0;

	LeftFront 	= "M1";
	LeftRear  	= "M2";
	RightFront 	= "M3";
	RightRear	= "M4";
	}

	if(Rev == 3)
	{
		//Serial.println("333333333333333333333");
	_ZW_L1_ =A3;//pin of L1
	_ZW_L2_	=A2;//pin of L2
	_ZW_L3_	=A1;//pin of L3
	_ZW_L4_	=A0;//pin of L4

	_ZW_R1_	=0;//pin of R1
	_ZW_R2_	=3;//pin of R2
	_ZW_R3_	=2;//pin of R3
	_ZW_R4_	=13;//pin of R4

	_ZW_M1_P_	=9;
	_ZW_M1_N_	=11;
	_ZW_M2_P_	=5;
	_ZW_M2_N_	=7;
	_ZW_M3_P_	=10;
	_ZW_M3_N_	=12;
	_ZW_M4_P_	=6;
	_ZW_M4_N_	=8;

	_ZW_BEEP_	=3;
	_ZW_START_	=4;

	LeftFront 	= "M1";
	LeftRear  	= "M2";
	RightFront 	= "M3";
	RightRear	  = "M4";
	}

	if(Rev == 4)
		{
			//Serial.println("333333333333333333333");
		_ZW_L1_ =A0;//pin of L1
		_ZW_L2_	=A1;//pin of L2
		_ZW_L3_	=A4;//pin of L3
		_ZW_L4_	=A5;//pin of L4

		_ZW_R1_	=A2;//pin of R1
		_ZW_R2_	=A3;//pin of R2
		_ZW_R3_	=2;//pin of R3
		_ZW_R4_	=7;//pin of R4

		_ZW_M1_P_	=3;
		_ZW_M1_N_	=13;
		_ZW_M2_P_	=5;
		_ZW_M2_N_	=12;
		_ZW_M3_P_	=11;
		_ZW_M3_N_	=10;
		_ZW_M4_P_	=6;
		_ZW_M4_N_	=9;

		_ZW_BEEP_	=8;
		_ZW_START_	=4;

		LeftFront 	= "M1";
		LeftRear  	= "M2";
		RightFront 	= "M3";
		RightRear	  = "M4";
	}
}


/*********************************************************************************************************
** Function name: init
** Descriptions:  init all pins
*********************************************************************************************************/
void ZeroLEVEL4::init()
{

	SoftPWMBegin();

	NumberOfProgram = 1;
	EEPROM_MIN_ADDR = 0;
	EEPROM_MAX_ADDR = 512;

	eeAddr_LEVEL1_DEFAULT_PROG = 100;

	eeAddr_RUBERBAND_LOADER = 128;

    motorSpeed1     = 0;
    motorSpeed2     = 0;
    motorSpeed3     = 0;
    motorSpeed4     = 0;

    motorDir1       = 0;
    motorDir2       = 0;
    motorDir3       = 0;
    motorDir4       = 0;

    motorState1     = STOP;
    motorState2     = STOP;
    motorState3     = STOP;
    motorState4     = STOP;

    //Serial.end();  //Set R1 R2 to GPIO

    pinMode(_ZW_M1_P_, OUTPUT);
    pinMode(_ZW_M1_N_, OUTPUT);
    pinMode(_ZW_M2_P_, OUTPUT);
    pinMode(_ZW_M2_N_, OUTPUT);
    pinMode(_ZW_M3_P_, OUTPUT);
    pinMode(_ZW_M3_N_, OUTPUT);
    pinMode(_ZW_M4_P_, OUTPUT);
    pinMode(_ZW_M4_N_, OUTPUT);

    pinMode(_ZW_START_, INPUT);
    pinMode(_ZW_BEEP_, OUTPUT);

    if(Rev ==2)
    {
	  	pinMode(_ZW_R1_, INPUT);
  	  	pinMode(_ZW_R2_, INPUT);
  	  	pinMode(_ZW_R3_, INPUT);
  	  	pinMode(_ZW_R4_, INPUT);

    	pinMode(_ZW_L1_, OUTPUT);
    	pinMode(_ZW_L2_, OUTPUT);
    	pinMode(_ZW_L3_, OUTPUT);
   		pinMode(_ZW_L4_, OUTPUT);

   		digitalWrite(_ZW_L1_, LOW);
		digitalWrite(_ZW_L1_, LOW);
		digitalWrite(_ZW_L3_, LOW);
    	digitalWrite(_ZW_L4_, LOW);
	}



    digitalWrite(_ZW_START_, HIGH);
    SoftPWMSet(_ZW_M1_P_, 0);
	SoftPWMSet(_ZW_M2_P_, 0);
	SoftPWMSet(_ZW_M3_P_, 0);
	SoftPWMSet(_ZW_M4_P_, 0);

    //digitalWrite(_ZW_M1_P_, LOW);
    digitalWrite(_ZW_M1_N_, LOW);
    //digitalWrite(_ZW_M2_P_, LOW);
    digitalWrite(_ZW_M2_N_, LOW);
    //digitalWrite(_ZW_M3_P_, LOW);
 	digitalWrite(_ZW_M3_N_, LOW);
 	//digitalWrite(_ZW_M4_P_, LOW);
    digitalWrite(_ZW_M4_N_, LOW);



    //des.init("ZeroWorkshop-Shanghai-2018\0",(unsigned long long int)0);

}
//New Start program without tone
void ZeroLEVEL4::StartProgram(int *ProgramSelector)
{

  ProgNumInEPROM ProgToBeSelected;
  ProgNumInEPROM lastRunProg;

  int eepromAddr = eeAddr_LEVEL1_DEFAULT_PROG;

  EEPROM.get(eepromAddr, lastRunProg);
  if (lastRunProg.lastProgSelected == 0) {
    ProgToBeSelected.lastProgSelected = 1;
    EEPROM.put(eepromAddr, ProgToBeSelected);
  }

  //Serial.begin(115200);

  pinMode(_ZW_BEEP_, OUTPUT);
  pinMode(_ZW_START_, INPUT);
  digitalWrite(_ZW_START_, HIGH);


  (*ProgramSelector) = -1;
  KeepOnReadButton = true;

  while (KeepOnReadButton) {


    ReadButtonState = true;
    while (ReadButtonState) {
      //TuningLoader(bulletLoader_servo, bulletTrigger_servo, &bullet_left) ;
      lastButtonState = ButtonState;
      delay(10);                                           //make a 10ms interval between successive reading. This is to make sure the button state is stable enough
      ButtonState = digitalRead(_ZW_START_);

      if ((*ProgramSelector) == -1 && ButtonState == HIGH) {    //if no program is selected, keep on read the button state
        //      if (ButtonState == HIGH) {    //if no program is selected, keep on read the button state
        ReadButtonState = true;
      }
      else if ((*ProgramSelector) >= 0 && ButtonState == HIGH && lastButtonState == HIGH) {     //if one program is selected and the next program is not selected in ButtonInterval(initially 2 seconds) time, the program selected will  run
        elapsedTime =   millis() - startTime;   // store elapsed time

        if (elapsedTime > ButtonInterval) {
          ReadButtonState = false;
          KeepOnReadButton = false;
        }
        else {
          ReadButtonState = true;
          KeepOnReadButton = true;
        }
      }
      else if (ButtonState == LOW && lastButtonState == LOW) {      //if the button is kept on being pressed, keep on reading the the state until the button is released.
        ReadButtonState = true;

      }
      else if (ButtonState == HIGH && lastButtonState == LOW) {      //if a low to high transition is found, it means the user just release the button. Reset the timer and wait button to be pressed for ButtonInterval(intially 2 seconds).
        startTime = millis();                                   // reset the start time
        ReadButtonState = true;

      }
      else if (ButtonState == LOW && lastButtonState == HIGH) {        //if a high to low transition is found, it means the user can select program. Stop reading the button, the corresponding tone will be played.
        ReadButtonState = false;
        (*ProgramSelector)++;
        break;
      }
    }

    if ((*ProgramSelector) > NumberOfProgram) {          //If times of StartButton pressed more than the number of program, program selector goes to the first program
      (*ProgramSelector) = 1;
    }

  }
  ProgToBeSelected.lastProgSelected = (*ProgramSelector);

  if (ProgToBeSelected.lastProgSelected != 0) {

    Serial.print("Program To be saved in EEPROM = ");
    Serial.println(ProgToBeSelected.lastProgSelected);

    EEPROM.put(eepromAddr, ProgToBeSelected);
  }
  else {
    EEPROM.get(eepromAddr, lastRunProg);

    (*ProgramSelector) = lastRunProg.lastProgSelected;
  }
}
/*
void ZeroLEVEL4::StartProgram(int *ProgramSelector)
{
  int noteDurations[] = {4, 4, 4, 4, 4, 4, 4, 4};
  int NOTE[] = {c5, c4, d4, e4, f4, g4, a4, b4};

  ProgNumInEPROM ProgToBeSelected;
  ProgNumInEPROM lastRunProg;

  int eepromAddr = eeAddr_LEVEL1_DEFAULT_PROG;

  EEPROM.get(eepromAddr, lastRunProg);
  if (lastRunProg.lastProgSelected == 0) {
    ProgToBeSelected.lastProgSelected = 1;
    EEPROM.put(eepromAddr, ProgToBeSelected);
  }


  //Serial.begin(115200);

  pinMode(_ZW_BEEP_, OUTPUT);
  pinMode(_ZW_START_, INPUT);
  digitalWrite(_ZW_START_, HIGH);


  int noteDuration = 1000 / noteDurations[0];
  int pauseBetweenNotes = noteDuration * 1.30;

  playNote(c4, eighthNote, meters_x1);
  playNote(e4, eighthNote, meters_x1);
  playNote(g4, eighthNote, meters_x1);
  playNote(c5, quaterNote, meters_x1);

  (*ProgramSelector) = -1;
  KeepOnReadButton = true;

  while (KeepOnReadButton) {


    ReadButtonState = true;
    while (ReadButtonState) {
      //TuningLoader(bulletLoader_servo, bulletTrigger_servo, &bullet_left) ;
      lastButtonState = ButtonState;
      delay(10);                                           //make a 10ms interval between successive reading. This is to make sure the button state is stable enough
      ButtonState = digitalRead(_ZW_START_);

      if ((*ProgramSelector) == -1 && ButtonState == HIGH) {    //if no program is selected, keep on read the button state
        //      if (ButtonState == HIGH) {    //if no program is selected, keep on read the button state
        ReadButtonState = true;
      }
      else if ((*ProgramSelector) >= 0 && ButtonState == HIGH && lastButtonState == HIGH) {     //if one program is selected and the next program is not selected in ButtonInterval(initially 2 seconds) time, the program selected will  run
        elapsedTime =   millis() - startTime;   // store elapsed time

        if (elapsedTime > ButtonInterval) {
          ReadButtonState = false;
          KeepOnReadButton = false;
        }
        else {
          ReadButtonState = true;
          KeepOnReadButton = true;
        }
      }
      else if (ButtonState == LOW && lastButtonState == LOW) {      //if the button is kept on being pressed, keep on reading the the state until the button is released.
        ReadButtonState = true;

      }
      else if (ButtonState == HIGH && lastButtonState == LOW) {      //if a low to high transition is found, it means the user just release the button. Reset the timer and wait button to be pressed for ButtonInterval(intially 2 seconds).
        startTime = millis();                                   // reset the start time
        ReadButtonState = true;

      }
      else if (ButtonState == LOW && lastButtonState == HIGH) {        //if a high to low transition is found, it means the user can select program. Stop reading the button, the corresponding tone will be played.
        ReadButtonState = false;
        (*ProgramSelector)++;
        break;
      }
    }

    if ((*ProgramSelector) > NumberOfProgram) {          //If times of StartButton pressed more than the number of program, program selector goes to the first program
      (*ProgramSelector) = 1;
    }


    if (ButtonState == LOW && lastButtonState == HIGH) {

      startTime = millis();                                   // store the start time

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      noteDuration = 1000 / noteDurations[(*ProgramSelector)];
      tone(_ZW_BEEP_, NOTE[(*ProgramSelector)], noteDuration);

      // the note's duration + 30% seems to work well:
      pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      noTone(_ZW_BEEP_);


    }
  }
  ProgToBeSelected.lastProgSelected = (*ProgramSelector);

  if (ProgToBeSelected.lastProgSelected != 0) {

    Serial.print("Program To be saved in EEPROM = ");
    Serial.println(ProgToBeSelected.lastProgSelected);

    EEPROM.put(eepromAddr, ProgToBeSelected);
  }
  else {
    EEPROM.get(eepromAddr, lastRunProg);

    (*ProgramSelector) = lastRunProg.lastProgSelected;
  }
}*/

/*void ZeroLEVEL4::StartProgram()
{
  //Serial.begin(115200);

  // note durations: 4 = quarter note, 8 = eighth note, etc.:
  int noteDurations[] = {4, 4, 4, 4, 4, 4, 4, 4};
  int NOTE[] = {c5, c4, d4, e4, f4, g4, a4, b4};

  pinMode(_ZW_BEEP_, OUTPUT);
  pinMode(_ZW_START_, INPUT);
  digitalWrite(_ZW_START_, HIGH);

  int noteDuration = 1000 / noteDurations[0];
  int pauseBetweenNotes = noteDuration * 1.30;

  playNote(c4, eighthNote, meters_x1);
  playNote(e4, eighthNote, meters_x1);
  playNote(g4, eighthNote, meters_x1);
  playNote(c5, quaterNote, meters_x1);

  ProgramSelector = 0;
  KeepOnReadButton = true;

  while (KeepOnReadButton) {


    ReadButtonState = true;
    while (ReadButtonState) {
      //TuningLoader(bulletLoader_servo, bulletTrigger_servo, &bullet_left) ;
      lastButtonState = ButtonState;
      delay(10);                                           //make a 10ms interval between successive reading. This is to make sure the button state is stable enough
      ButtonState = digitalRead(_ZW_START_);

      if (ProgramSelector == 0 && ButtonState == HIGH) {    //if no program is selected, keep on read the button state
        ReadButtonState = true;
      }
      else if (ProgramSelector > 0 && ButtonState == HIGH && lastButtonState == HIGH) {     //if one program is selected and the next program is not selected in ButtonInterval(initially 2 seconds) time, the program selected will  run
        elapsedTime =   millis() - startTime;   // store elapsed time

        if (elapsedTime > ButtonInterval) {
          ReadButtonState = false;
          KeepOnReadButton = false;
        }
        else {
          ReadButtonState = true;
          KeepOnReadButton = true;
        }
      }
      else if (ButtonState == LOW && lastButtonState == LOW) {      //if the button is kept on being pressed, keep on reading the the state until the button is released.
        ReadButtonState = true;

      }
      else if (ButtonState == HIGH && lastButtonState == LOW) {      //if a low to high transition is found, it means the user just release the button. Reset the timer and wait button to be pressed for ButtonInterval(intially 2 seconds).
        startTime = millis();                                   // reset the start time
        ReadButtonState = true;

      }
      else if (ButtonState == LOW && lastButtonState == HIGH) {        //if a high to low transition is found, it means the user can select program. Stop reading the button, the corresponding tone will be played.
        ReadButtonState = false;
        ProgramSelector++;
        break;
      }
    }

    if (ProgramSelector > NumberOfProgram) {          //If times of StartButton pressed more than the number of program, program selector goes to the first program
      ProgramSelector = 1;
    }


    if (ButtonState == LOW && lastButtonState == HIGH) {

      startTime = millis();                                   // store the start time

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      noteDuration = 1000 / noteDurations[ProgramSelector];
      tone(_ZW_BEEP_, NOTE[ProgramSelector], noteDuration);

      // the note's duration + 30% seems to work well:
      pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      noTone(_ZW_BEEP_);


    }

  }
}
*/

/*void ZeroLEVEL4::playNote(int Note, int Meter, int Length) {
  tone(_ZW_BEEP_, Note, Meter * Length);
  delay(Meter * 1.3 * Length);
  noTone(_ZW_BEEP_);
}

void ZeroLEVEL4::playSong(int songSelected) {
  switch (songSelected) {
    case 1:
      playNote(e4, eighthNote, meters_x1);
      playNote(e4, eighthNote, meters_x1);
      playNote(f4, eighthNote, meters_x1);
      playNote(g4, eighthNote, meters_x1);

      playNote(g4, eighthNote, meters_x1);
      playNote(f4, eighthNote, meters_x1);
      playNote(e4, eighthNote, meters_x1);
      playNote(d4, eighthNote, meters_x1);

      playNote(c4, eighthNote, meters_x1);
      playNote(c4, eighthNote, meters_x1);
      playNote(d4, eighthNote, meters_x1);
      playNote(e4, eighthNote, meters_x1);

      playNote(e4, sixteenthNote, meters_x3);
      playNote(d4, sixteenthNote, meters_x1);
      playNote(d4, eighthNote, meters_x2);



      playNote(e4, eighthNote, meters_x1);
      playNote(e4, eighthNote, meters_x1);
      playNote(f4, eighthNote, meters_x1);
      playNote(g4, eighthNote, meters_x1);

      playNote(g4, eighthNote, meters_x1);
      playNote(f4, eighthNote, meters_x1);
      playNote(e4, eighthNote, meters_x1);
      playNote(d4, eighthNote, meters_x1);

      playNote(c4, eighthNote, meters_x1);
      playNote(c4, eighthNote, meters_x1);
      playNote(d4, eighthNote, meters_x1);
      playNote(e4, eighthNote, meters_x1);

      playNote(d4, sixteenthNote, meters_x3);
      playNote(c4, sixteenthNote, meters_x1);
      playNote(c4, eighthNote, meters_x2);


      for (int i = 0; i < 2; i++) {
        playNote(d4, eighthNote, meters_x1);
        playNote(d4, eighthNote, meters_x1);
        playNote(e4, eighthNote, meters_x1);
        playNote(c4, eighthNote, meters_x1);

        playNote(d4, eighthNote, meters_x1);
        playNote(e4, sixteenthNote, meters_x1);
        playNote(f4, sixteenthNote, meters_x1);
        playNote(e4, eighthNote, meters_x1);
        playNote(c4, eighthNote, meters_x1);

        playNote(d4, eighthNote, meters_x1);
        playNote(e4, sixteenthNote, meters_x1);
        playNote(f4, sixteenthNote, meters_x1);
        playNote(e4, eighthNote, meters_x1);
        playNote(d4, eighthNote, meters_x1);

        playNote(c4, eighthNote, meters_x1);
        playNote(d4, eighthNote, meters_x1);
        playNote(g3, eighthNote, meters_x1);
        playNote(e4, eighthNote, meters_x2);

        //playNote(e4,eighthNote,meters_x1);
        playNote(e4, eighthNote, meters_x1);
        playNote(f4, eighthNote, meters_x1);
        playNote(g4, eighthNote, meters_x1);

        playNote(g4, eighthNote, meters_x1);
        playNote(f4, eighthNote, meters_x1);
        playNote(e4, eighthNote, meters_x1);
        playNote(d4, eighthNote, meters_x1);

        playNote(c4, eighthNote, meters_x1);
        playNote(c4, eighthNote, meters_x1);
        playNote(d4, eighthNote, meters_x1);
        playNote(e4, eighthNote, meters_x1);

        playNote(d4, sixteenthNote, meters_x3);
        playNote(c4, sixteenthNote, meters_x1);
        playNote(c4, eighthNote, meters_x2);
      }
      break;

    case 2:
      playNote(c4, sixteenthNote, meters_x3);
      playNote(e4, sixteenthNote, meters_x1);
      playNote(g4, eighthNote, meters_x1);
      playNote(g4, eighthNote, meters_x1);

      playNote(a4, quaterNote, meters_x1);
      playNote(g4, quaterNote, meters_x1);

      playNote(e4, sixteenthNote, meters_x3);
      playNote(c4, sixteenthNote, meters_x1);
      playNote(g4, quaterNote / 3, meters_x1);
      playNote(g4, quaterNote / 3, meters_x1);
      playNote(g4, quaterNote / 3, meters_x1);

      playNote(e4, quaterNote, meters_x1);
      playNote(c4, quaterNote, meters_x1);

      playNote(g3, quaterNote / 3, meters_x1);
      playNote(g3, quaterNote / 3, meters_x1);
      playNote(g3, quaterNote / 3, meters_x1);
      playNote(g3, quaterNote / 3, meters_x1);
      playNote(g3, quaterNote / 3, meters_x1);
      playNote(g3, quaterNote / 3, meters_x1);

      playNote(c4, quaterNote, meters_x1);
      delay(eighthNote * 1.3 * meters_x1);
      playNote(g3, eighthNote, meters_x1);

      playNote(c4, eighthNote, meters_x3);
      playNote(c4, eighthNote, meters_x1);

      playNote(c4, sixteenthNote, meters_x3);
      playNote(c4, sixteenthNote, meters_x1);
      playNote(g3, eighthNote, meters_x1);
      playNote(a3, sixteenthNote, meters_x1);
      playNote(b3, sixteenthNote, meters_x1);

      playNote(c4, quaterNote, meters_x1);
      playNote(c4, quaterNote, meters_x1);
      delay(eighthNote * 1.3 * meters_x1);

      playNote(e4, eighthNote, meters_x1);
      playNote(c4, eighthNote, meters_x1);
      playNote(d4, sixteenthNote, meters_x1);
      playNote(e4, sixteenthNote, meters_x1);

      playNote(g4, quaterNote, meters_x1);
      playNote(g4, quaterNote, meters_x1);

      playNote(e4, sixteenthNote, meters_x3);
      playNote(e4, sixteenthNote, meters_x1);
      playNote(c4, sixteenthNote, meters_x3);
      playNote(e4, sixteenthNote, meters_x1);

      playNote(g4, sixteenthNote, meters_x3);
      playNote(e4, sixteenthNote, meters_x1);
      playNote(d4, quaterNote, meters_x1);

      playNote(d4, quaterNote, meters_x2);

      playNote(a4, quaterNote, meters_x1);
      playNote(g4, quaterNote, meters_x1);

      playNote(d4, quaterNote, meters_x1);
      playNote(e4, quaterNote, meters_x1);

      playNote(g4, eighthNote, meters_x1);
      playNote(e4, eighthNote, meters_x1);
      delay(eighthNote * 1.3 * meters_x1);
      playNote(g4, eighthNote, meters_x1);

      playNote(e4, eighthNote, meters_x1);
      playNote(d4, sixteenthNote, meters_x1);
      playNote(e4, sixteenthNote, meters_x1);
      playNote(c4, quaterNote, meters_x1);

      playNote(e4, quaterNote, meters_x1);
      delay(quaterNote * 1.3 * meters_x1);

      playNote(g3, sixteenthNote, meters_x3);
      playNote(a3, sixteenthNote, meters_x1);
      playNote(c4, eighthNote, meters_x1);
      playNote(c4, eighthNote, meters_x1);

      playNote(e4, sixteenthNote, meters_x3);
      playNote(e4, sixteenthNote, meters_x1);
      playNote(g4, eighthNote, meters_x1);
      playNote(g4, eighthNote, meters_x1);

      playNote(d4, eighthNote, meters_x1);
      playNote(d4, sixteenthNote, meters_x1);
      playNote(d4, sixteenthNote, meters_x1);
      playNote(a3, quaterNote, meters_x1);

      playNote(d4, eighthNote, meters_x3);
      playNote(g3, eighthNote, meters_x1);

      playNote(c4, eighthNote, meters_x3);
      playNote(c4, eighthNote, meters_x1);

      playNote(e4, eighthNote, meters_x3);
      playNote(e4, eighthNote, meters_x1);

      playNote(g4, quaterNote, meters_x2);

      playNote(c4, sixteenthNote, meters_x3);
      playNote(e4, sixteenthNote, meters_x1);
      playNote(g4, eighthNote, meters_x1);
      playNote(g4, eighthNote, meters_x1);

      playNote(a4, quaterNote, meters_x1);
      playNote(g4, quaterNote, meters_x1);

      playNote(e4, sixteenthNote, meters_x3);
      playNote(c4, sixteenthNote, meters_x1);
      playNote(g4, quaterNote / 3, meters_x1);
      playNote(g4, quaterNote / 3, meters_x1);
      playNote(g4, quaterNote / 3, meters_x1);

      playNote(e4, eighthNote, meters_x1);
      delay(eighthNote * 1.3 * meters_x1);
      playNote(c4, eighthNote, meters_x1);
      delay(eighthNote * 1.3 * meters_x1);

      playNote(g3, quaterNote, meters_x1);
      playNote(c4, quaterNote, meters_x1);

      playNote(e4, sixteenthNote, meters_x3);
      playNote(c4, sixteenthNote, meters_x1);
      playNote(g4, quaterNote / 3, meters_x1);
      playNote(g4, quaterNote / 3, meters_x1);
      playNote(g4, quaterNote / 3, meters_x1);

      playNote(e4, eighthNote, meters_x1);
      delay(eighthNote * 1.3 * meters_x1);
      playNote(c4, eighthNote, meters_x1);
      delay(eighthNote * 1.3 * meters_x1);

      playNote(g3, quaterNote, meters_x1);
      playNote(c4, quaterNote, meters_x1);

      playNote(g3, quaterNote, meters_x1);
      playNote(c4, quaterNote, meters_x1);

      playNote(g3, quaterNote, meters_x1);
      playNote(c4, quaterNote, meters_x1);

      playNote(c4, quaterNote, meters_x1);
      delay(quaterNote * 1.3 * meters_x1);
      break;

    case 3:
      break;
    case 4:
      break;

    case 5:
      break;

    default:
      break;
  }

}
*/
void ZeroLEVEL4::setLeftFrontMotor(String motor,int ispeed,unsigned char dir)
{
	//Serial.print("setLeftFrontMotor  ");
	//Serial.println(motor+" "+ispeed+"  "+ dir);
	if(motor == "M1")
	{
		setSpeedDir1(ispeed, dir);
		//Serial.println("LeftFrontMotor M1");
		#if DEBUG
			Serial.println("LeftFrontMotor M1");
		#endif
	}
	else if(motor == "M2")
	{
		setSpeedDir2(ispeed, dir);
		#if DEBUG
			Serial.println("LeftFrontMotor M2");
		#endif
	}
	else if(motor == "M3")
	{
		setSpeedDir3(ispeed, dir);
		#if DEBUG
			Serial.println("LeftFrontMotor M3");
		#endif
	}
	else if(motor == "M4")
	{
		setSpeedDir4(ispeed, dir);
		#if DEBUG
			Serial.println("LeftFrontMotor M4");
		#endif
	}
	else
	{

	}
}

void ZeroLEVEL4::setLeftRearMotor(String motor,int ispeed,unsigned char dir)
{
	//Serial.print("setLeftRearMotor ");
	//Serial.println(motor+" "+ispeed+"  "+ dir);
	if(motor == "M1")
	{
		setSpeedDir1(ispeed, dir);
		#if DEBUG
			Serial.println("setLeftRearMotor M1");
		#endif
	}
	else if(motor == "M2")
	{
		setSpeedDir2(ispeed, dir);
		//Serial.println("LeftRearMotor M2");
		#if DEBUG
			Serial.println("setLeftRearMotor M2");
		#endif
	}
	else if(motor == "M3")
	{
		setSpeedDir3(ispeed, dir);
		#if DEBUG
			Serial.println("setLeftRearMotor M3");
		#endif
	}
	else if(motor == "M4")
	{
		setSpeedDir4(ispeed, dir);
		#if DEBUG
			Serial.println("setLeftRearMotor M4");
		#endif
	}
	else
	{
		//Serial.println("*************************************");
	}
}

void ZeroLEVEL4::setRightFrontMotor(String motor,int ispeed,unsigned char dir)
{
	//Serial.print("setRightFrontMotor ");
	//Serial.println(motor+" "+ispeed+"  "+ dir);

	if(motor == "M1")
	{
		setSpeedDir1(ispeed, dir);
		#if DEBUG
			Serial.println("setRightFrontMotor M1");
		#endif
	}
	else if(motor == "M2")
	{
		setSpeedDir2(ispeed, dir);
		#if DEBUG
			Serial.println("setRightFrontMotor M2");
		#endif
	}
	else if(motor == "M3")
	{
		setSpeedDir3(ispeed, dir);
		#if DEBUG
			Serial.println("setRightFrontMotor M3");
		#endif
	}
	else if(motor == "M4")
	{
		setSpeedDir4(ispeed, dir);
		#if DEBUG
			Serial.println("setRightFrontMotor M4");
		#endif
	}
	else
	{

	}
}
void ZeroLEVEL4::setRightRearMotor(String motor,int ispeed,unsigned char dir)
{
	//Serial.print("setRightRearMotor ");
	//Serial.println(motor+" "+ispeed+"  "+ dir);
	if(motor == "M1")
	{
		setSpeedDir1(ispeed, dir);
		#if DEBUG
			Serial.println("setRightRearMotor M1");
		#endif
	}
	else if(motor == "M2")
	{
		setSpeedDir2(ispeed, dir);
		#if DEBUG
			Serial.println("setRightRearMotor M2");
		#endif
	}
	else if(motor == "M3")
	{
		setSpeedDir3(ispeed, dir);
		#if DEBUG
			Serial.println("setRightRearMotor M3");
		#endif
	}
	else if(motor == "M4")
	{
		setSpeedDir4(ispeed, dir);
		#if DEBUG
			Serial.println("setRightRearMotor M4");
		#endif
	}
	else
	{

	}
}
void ZeroLEVEL4::goForward(int ispeed)
{

	setLeftFrontMotor	(LeftFront  , ispeed, DIRR);
	setLeftRearMotor	(LeftRear 	, ispeed, DIRR);
	setRightFrontMotor	(RightFront , ispeed, DIRF);
	setRightRearMotor	(RightRear 	, ispeed, DIRF);
}


void ZeroLEVEL4::goLeftTurn(int ispeed)
{
	setLeftFrontMotor	(LeftFront 	, ispeed, DIRF);
	setLeftRearMotor	(LeftRear 	, ispeed, DIRF);
	setRightFrontMotor	(RightFront , ispeed, DIRF);
	setRightRearMotor	(RightRear 	, ispeed, DIRF);

}

void ZeroLEVEL4::goRightTurn(int ispeed)
{
	setLeftFrontMotor	(LeftFront 	, ispeed, DIRR);
	setLeftRearMotor	(LeftRear 	, ispeed, DIRR);
	setRightFrontMotor	(RightFront , ispeed, DIRR);
	setRightRearMotor	(RightRear 	, ispeed, DIRR);
}

void ZeroLEVEL4::goReverse(int ispeed)
{

	setLeftFrontMotor	(LeftFront 	, ispeed, DIRF);
	setLeftRearMotor	(LeftRear 	, ispeed, DIRF);
	setRightFrontMotor	(RightFront , ispeed, DIRR);
	setRightRearMotor	(RightRear 	, ispeed, DIRR);
}

void ZeroLEVEL4::goBrake()
{

	setLeftFrontMotor	(LeftFront 	, 0, DIRR);
	setLeftRearMotor	(LeftRear 	, 0, DIRR);
	setRightFrontMotor	(RightFront , 0, DIRF);
	setRightRearMotor	(RightRear 	, 0, DIRF);

}


void ZeroLEVEL4::goForwardSingleMotor(int ispeed)
{

	setLeftFrontMotor	(LeftFront  , ispeed, DIRR);
	//setLeftRearMotor	(LeftRear 	, ispeed, DIRR);
	setRightFrontMotor	(RightFront , ispeed, DIRF);
	//setRightRearMotor	(RightRear 	, ispeed, DIRF);
}


void ZeroLEVEL4::goLeftTurnSingleMotor(int ispeed)
{
	setLeftFrontMotor	(LeftFront 	, ispeed, DIRF);
	//setLeftRearMotor	(LeftRear 	, ispeed, DIRF);
	setRightFrontMotor	(RightFront , ispeed, DIRF);
	//setRightRearMotor	(RightRear 	, ispeed, DIRF);

}

void ZeroLEVEL4::goRightTurnSingleMotor(int ispeed)
{
	setLeftFrontMotor	(LeftFront 	, ispeed, DIRR);
	//setLeftRearMotor	(LeftRear 	, ispeed, DIRR);
	setRightFrontMotor	(RightFront , ispeed, DIRR);
	//setRightRearMotor	(RightRear 	, ispeed, DIRR);
}

void ZeroLEVEL4::goReverseSingleMotor(int ispeed)
{

	setLeftFrontMotor	(LeftFront 	, ispeed, DIRF);
	//setLeftRearMotor	(LeftRear 	, ispeed, DIRF);
	setRightFrontMotor	(RightFront , ispeed, DIRR);
	//setRightRearMotor	(RightRear 	, ispeed, DIRR);
}

void ZeroLEVEL4::goBrakeSingleMotor()
{

	setLeftFrontMotor	(LeftFront 	, 0, DIRR);
	//setLeftRearMotor	(LeftRear 	, 0, DIRR);
	setRightFrontMotor	(RightFront , 0, DIRF);
	//setRightRearMotor	(RightRear 	, 0, DIRF);

}



void ZeroLEVEL4::setMotor(String LF,String LR, String RF, String RR)
{

	LeftFront = LF;
	LeftRear  = LR;
	RightFront = RF;
	RightRear  = RR;

	Serial.println("LeftFront ="+ LeftFront);
	Serial.println("LeftRear ="+ LeftRear);
	Serial.println("RightFront ="+ RightFront);
	Serial.println("RightRear ="+ RightRear);
}


bool ZeroLEVEL4::PS2_RF_ReadButton(int *Button_Buffer)
{

  byte PS2_RF_buffer[6];
  bool PAD_LeftKey;
  int temp;
  bool Re_read_buffer = false;
  int startPosition = 0;

  int bytes = Serial.available();

  /*
    Button_Buffer[2] = 0;
    Button_Buffer[3] = 0;
    Button_Buffer[4] = 0;
    Button_Buffer[5] = 0;
  */
  if (bytes > 0 ) {

    for (int j = 0; j < bytes; j++) {
      temp = Serial.read();
       #if DEBUG
      Serial.print("Byte ");
      Serial.print(j);
      Serial.print(":   ");
      Serial.println(temp, HEX);
       #endif
      if (temp == 0xAA) buffer_index = 0;

      Button_Buffer[buffer_index] = temp;
      #if DEBUG
      Serial.print("Byte[");
      Serial.print(buffer_index);
      Serial.print("]: 0x");
      Serial.println(Button_Buffer[buffer_index], HEX);
      #endif
      buffer_index++;


    }
  }
}



/*
 For some unknown reason, the controller data into the serial port sometimes give the wrong sequence.
 The right sequence is AA 55 RR SS TT UU. A right data is a 6-byte with AA 55 as the first two bytes.
 However sometimes the byte sequence is less than 6 byte which is a wrong number. It maybe caused by some missing capture.
 This function is to pick up the right 6-byte sequence as the correct controller data.
 SerialEvent occurs whenever a new data comes in the hardware serial RX.
 Normally several consective 6-byte data are recieved. But sometimes there are some missing bytes.
 In this case, we collect the latest valid 6-byte data as the valid controller data.
 */
 /*
void ZeroLEVEL4::serialEvent() {
  if (Serial.available() < 6) return;  //If the total bytes in buffer is less than 6, the data is invalid. Stop the routine without get the data.
#if DEBUG
  Serial.print("Bytes in buffer is : ");
  Serial.println(Serial.available());
  if (Serial.available() % 6) Serial.println("ERROR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
#endif


  int TotalBytesInBuffer = Serial.available();
  int latestStartByte = 0;
  int lastStartByte = 0;
  int index;
  int inChar;
  bool valid_controller_data = false;

  for (int j = 0; j < TotalBytesInBuffer; j++) {   //Read out the controller data byte by byte.
    // get the new byte:

    inChar = Serial.read();

#if DEBUG
    Serial.print(j);
    Serial.print(" : ");
    Serial.println(inChar, HEX);
#endif
    if (inChar == 0xAA) {  //Find the head of a controller data. If AA is found, store it as the first byte of a temp controller data.
      index = 0;
    }
    temp[index++] = inChar;


    if (index == 6) valid_controller_data = true;  //If there is no another 0xAA before the first 6 byte end, it means the first 6-byte data is valid.
    else valid_controller_data = false;            //Otherwise the data captured is less than 6 bytes which is invalid data.

    if (valid_controller_data) {                   //Give the lastes valid data as the controller data.
      for (int i = 0; i < index; i++) {
        Rx_Buffer[i] = temp[i];
#if DEBUG
        Serial.print("Latest Controller value is : ");
        Serial.println(Rx_Buffer[i], HEX);
#endif
      }
    }

  }
#if DEBUG
  Serial.println("****************************************************************************************");
#endif
}
*/

/**
 * Divides a given PWM pin frequency by a divisor.
 *
 * The resulting frequency is equal to the base frequency divided by
 * the given divisor:
 *   - Base frequencies:
 *      o The base frequency for pins 3, 9, 10, and 11 is 31250 Hz.
 *      o The base frequency for pins 5 and 6 is 62500 Hz.
 *   - Divisors:
 *      o The divisors available on pins 5, 6, 9 and 10 are: 1, 8, 64,
 *        256, and 1024.
 *      o The divisors available on pins 3 and 11 are: 1, 8, 32, 64,
 *        128, 256, and 1024.
 *
 * PWM frequencies are tied together in pairs of pins. If one in a
 * pair is changed, the other is also changed to match:
 *   - Pins 5 and 6 are paired on timer0
 *   - Pins 9 and 10 are paired on timer1
 *   - Pins 3 and 11 are paired on timer2
 *
 * Note that this function will have side effects on anything else
 * that uses timers:
 *   - Changes on pins 3, 5, 6, or 11 may cause the delay() and
 *     millis() functions to stop working. Other timing-related
 *     functions may also be affected.
 *   - Changes on pins 9 or 10 will cause the Servo library to function
 *     incorrectly.
 *
 * Thanks to macegr of the Arduino forums for his documentation of the
 * PWM frequency divisors. His post can be viewed at:
 *   http://forum.arduino.cc/index.php?topic=16612#msg121031
 */
void ZeroLEVEL4::setPwmfrequency(char pin, int divisor) {
  byte mode;
  if(pin == 5 || pin == 6 || pin == 9 || pin == 10) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 64: mode = 0x03; break;
      case 256: mode = 0x04; break;
      case 1024: mode = 0x05; break;
      default: return;
    }
    if(pin == 5 || pin == 6) {
      TCCR0B = TCCR0B & 0b11111000 | mode;
    } else {
      TCCR1B = TCCR1B & 0b11111000 | mode;
    }
  } else if(pin == 3 || pin == 11) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 32: mode = 0x03; break;
      case 64: mode = 0x04; break;
      case 128: mode = 0x05; break;
      case 256: mode = 0x06; break;
      case 1024: mode = 0x07; break;
      default: return;
    }
    TCCR2B = TCCR2B & 0b11111000 | mode;
  }
}

/*********************************************************************************************************
** Function name: setPwm
** Descriptions:  set motor pwm
*********************************************************************************************************/
void ZeroLEVEL4::setPwm(char pin, int ispeed,int frequency )
{

/*	 //sets the frequency for the specified pin
	  bool success = SetPinfrequencySafe(pin, frequency);

	  //if the pin frequency was set successfully, turn pin 13 on
	  if(success) {
	    pinMode(pin, OUTPUT);
	    //digitalWrite(13, HIGH);
	    //use this functions instead of analogWrite on 'initialized' pins
	  pwmWrite(pin, ispeed);

  }
  */

  // Set pin 9's PWM frequency to 3906 Hz (31250/8 = 3906)
  // Note that the base frequency for pins 3, 9, 10, and 11 is 31250 Hz
   setPwmfrequency(pin, frequency);

   analogWrite(pin,ispeed);  //use default frequency
}


/*********************************************************************************************************
** Function name: setStop1
** Descriptions:  set motor 1 stop
*********************************************************************************************************/
void ZeroLEVEL4::setStop1()
{
    //setPwm(PWM1, 0, FREQPWM);

    digitalWrite(_ZW_M1_P_, LOW);
    digitalWrite(_ZW_M1_N_, LOW);
    motorState1 = STOP;
}

/*********************************************************************************************************
** Function name: setStop2
** Descriptions:  set motor 2 stop
*********************************************************************************************************/
void ZeroLEVEL4::setStop2()
{

    digitalWrite(_ZW_M2_P_, LOW);
    digitalWrite(_ZW_M2_N_, LOW);
    motorState2 = STOP;
}

/*********************************************************************************************************
** Function name: setStop3
** Descriptions:  set motor 3 stop
*********************************************************************************************************/
void ZeroLEVEL4::setStop3()
{

    digitalWrite(_ZW_M3_P_, LOW);
    digitalWrite(_ZW_M3_N_, LOW);
    motorState3 = STOP;
}


/*********************************************************************************************************
** Function name: setStop4
** Descriptions:  set motor 4 stop
*********************************************************************************************************/
void ZeroLEVEL4::setStop4()
{

    digitalWrite(_ZW_M4_P_, LOW);
    digitalWrite(_ZW_M4_N_, LOW);
    motorState4 = STOP;
}



/*********************************************************************************************************
** Function name: setSpeed1
** Descriptions:  set motor 1 speed
*********************************************************************************************************/
void ZeroLEVEL4::setSpeed1(int ispeed)       // pwm, 0-100
{
    motorSpeed1 = ispeed < 255 ? ispeed : 254;
    if((Rev == 1) || (Rev ==2))
    {
	if(motorDir1 == DIRF)
 	{
	 	 SoftPWMSet(_ZW_M1_P_, motorSpeed1);
		 digitalWrite(_ZW_M1_N_, LOW);
	}
	else
	{
		int PWMvalue = 255 - motorSpeed1;
	    SoftPWMSet(_ZW_M1_P_, PWMvalue);
	    digitalWrite(_ZW_M1_N_, HIGH);
	}
}
else if (Rev == 3)
{
	SoftPWMSet(_ZW_M1_P_, motorSpeed1);
	if(motorDir1 == DIRF)
 	{
		 digitalWrite(_ZW_M1_N_, LOW);
	}
	else
	{
		 digitalWrite(_ZW_M1_N_, HIGH);
	}


}

	 motorState1 = RUN;

}

/*********************************************************************************************************
** Function name: setSpeed2
** Descriptions:  set motor 2 speed
*********************************************************************************************************/
void ZeroLEVEL4::setSpeed2(int ispeed)       // pwm, 0-100
{
    motorSpeed2 = ispeed < 255 ? ispeed : 254;
	if(Rev == 1)
	{
		if(motorDir2 == DIRF)
 		{
	 	 	SoftPWMSet(_ZW_M2_P_, motorSpeed2);
		 	digitalWrite(_ZW_M2_N_, LOW);
		}
		else
		{
			int PWMvalue = 255 - motorSpeed2;
	    	SoftPWMSet(_ZW_M2_P_, PWMvalue);
	    	digitalWrite(_ZW_M2_N_, HIGH);
		}

	}
	else if(Rev == 2)
	{
		if(motorDir2 == DIRF)
		{
	 	 	digitalWrite(_ZW_M2_P_, HIGH);
		 	digitalWrite(_ZW_M2_N_, LOW);
		}
		else
		{
			digitalWrite(_ZW_M2_P_, LOW);
			digitalWrite(_ZW_M2_N_, HIGH);
		}
	}
	else if(Rev == 3)
	{
		if(motorDir2 == DIRF)
	 	{
		 	 SoftPWMSet(_ZW_M2_P_, motorSpeed2);
			 digitalWrite(_ZW_M2_N_, LOW);
		}
		else
		{
			SoftPWMSet(_ZW_M2_P_, motorSpeed2);
		    digitalWrite(_ZW_M2_N_, HIGH);
		}
	}
	motorState2 = RUN;

}

/*********************************************************************************************************
** Function name: setSpeed3
** Descriptions:  set motor 3 speed
*********************************************************************************************************/
void ZeroLEVEL4::setSpeed3(int ispeed)       // pwm, 0-100
{
    motorSpeed3 = ispeed < 255 ? ispeed : 254;

	 if((Rev == 1))
	{
		if(motorDir3 == DIRF)
 		{
	 	 SoftPWMSet(_ZW_M3_P_, motorSpeed3);
		 digitalWrite(_ZW_M3_N_, LOW);
		}
		else
		{
		int PWMvalue = 255 - motorSpeed3;
	    SoftPWMSet(_ZW_M3_P_, PWMvalue);
	    digitalWrite(_ZW_M3_N_, HIGH);
		}
	}
	else if((Rev == 2))
	{
		if(motorDir3 == DIRF)
 		{
	 	 digitalWrite(_ZW_M3_P_, HIGH);
		 digitalWrite(_ZW_M3_N_, LOW);
		}
		else
		{

	    digitalWrite(_ZW_M3_P_, LOW);
	    digitalWrite(_ZW_M3_N_, HIGH);
		}
	}
	else if(Rev == 3)
	{
		if(motorDir3 == DIRF)
	 	{
		 	 SoftPWMSet(_ZW_M3_P_, motorSpeed3);
			 digitalWrite(_ZW_M3_N_, LOW);
		}
		else
		{
		    SoftPWMSet(_ZW_M3_P_, motorSpeed3);
		    digitalWrite(_ZW_M3_N_, HIGH);
		}
	}

	motorState3 = RUN;

}
/*********************************************************************************************************
** Function name: setSpeed=4
** Descriptions:  set motor 4 speed
*********************************************************************************************************/
void ZeroLEVEL4::setSpeed4(int ispeed)       // pwm, 0-100
{
    motorSpeed4 = ispeed < 255 ? ispeed : 254;
	 if((Rev == 1) || (Rev ==2))
	{
		if(motorDir4 == DIRF)
 		{
	 	 SoftPWMSet(_ZW_M4_P_, motorSpeed4);
		 digitalWrite(_ZW_M4_N_, LOW);
		}
		else
		{
		int PWMvalue = 255 - motorSpeed4;
	    SoftPWMSet(_ZW_M4_P_, PWMvalue);
	    digitalWrite(_ZW_M4_N_, HIGH);
		}
	}
	else if(Rev == 3)
	{
		if(motorDir4 == DIRF)
	 	{
		 	 SoftPWMSet(_ZW_M4_P_, motorSpeed4);
			 digitalWrite(_ZW_M4_N_, LOW);
		}
		else
		{

		    SoftPWMSet(_ZW_M4_P_, motorSpeed4);
		    digitalWrite(_ZW_M4_N_, HIGH);
		}
	}

	motorState4 = RUN;

}
/*********************************************************************************************************
** Function name: setDir1
** Descriptions:  set motor 1 direction
*********************************************************************************************************/
void ZeroLEVEL4::setDir1(unsigned char dir)
{
	if(motorDir1 == dir)
	{

	}
	else
	{

		if(motorDir1 == DIRF)
		{
			digitalWrite(_ZW_M1_N_, LOW);
			SoftPWMSet(_ZW_M1_P_, motorSpeed1);

		}
		else
		{

		    digitalWrite(_ZW_M1_N_, HIGH);
		    if((Rev == 1) || (Rev ==2))
		    {
				int PWMvalue = 255 - motorSpeed1;
		 		SoftPWMSet(_ZW_M1_P_, PWMvalue);
			}
			else if(Rev ==3)
			{
				SoftPWMSet(_ZW_M1_P_, motorSpeed1);

			}
		}
	}
    motorDir1 = dir;
    motorState1 = RUN;
}

/*********************************************************************************************************
** Function name: setDir2
** Descriptions:  set motor 2 direction
*********************************************************************************************************/
void ZeroLEVEL4::setDir2(unsigned char dir)
{
    if(motorDir2 == dir)
	{

	}
	else
	{
		if(motorDir2 == DIRF)
		{
			digitalWrite(_ZW_M2_N_, LOW);
			if(Rev == 2)
			{
				digitalWrite(_ZW_M2_P_,HIGH);
			}
			else
			{
			SoftPWMSet(_ZW_M2_P_, motorSpeed2);
			}

		}
		else
		{
		    digitalWrite(_ZW_M2_N_, HIGH);
		    if((Rev == 1) )
		    {
			int PWMvalue = 255 - motorSpeed2;
		 	SoftPWMSet(_ZW_M2_P_, PWMvalue);
			}

			else if(Rev == 2)
			{
				digitalWrite(_ZW_M2_P_, LOW);
			}
			else if(Rev == 3)
			{
			SoftPWMSet(_ZW_M2_P_, motorSpeed2);

			}
		}


	}
	motorDir2 = dir;
    motorState2 = RUN;
}

/*********************************************************************************************************
** Function name: setDir3
** Descriptions:  set motor 3 direction
*********************************************************************************************************/
void ZeroLEVEL4::setDir3(unsigned char dir)
{
    if(motorDir3 == dir)
	{

	}
	else
	{
		if(motorDir3 == DIRF)
		{
			digitalWrite(_ZW_M3_N_, LOW);
			if(Rev ==2)
			{
				digitalWrite(_ZW_M3_P_, HIGH);
			}
			else
			{
				SoftPWMSet(_ZW_M3_P_, motorSpeed3);
			}

		}
		else
		{
		    digitalWrite(_ZW_M3_N_, HIGH);
		    if((Rev == 1) )
		    {
			int PWMvalue = 255 - motorSpeed3;
		 	SoftPWMSet(_ZW_M3_P_, PWMvalue);
			}
			else if(Rev ==2)
			{
				digitalWrite(_ZW_M3_P_, LOW);
			}

			else if(Rev ==3)
			{
				SoftPWMSet(_ZW_M3_P_, motorSpeed3);
			}
		}


	}
	motorDir3 = dir;
    motorState3 = RUN;
}
/*********************************************************************************************************
** Function name: setDir4
** Descriptions:  set motor 4 direction
*********************************************************************************************************/
void ZeroLEVEL4::setDir4(unsigned char dir)
{
    if(motorDir4 == dir)
	{

	}
	else
	{
		if(motorDir4 == DIRF)
		{
			digitalWrite(_ZW_M4_N_, LOW);
			SoftPWMSet(_ZW_M4_P_, motorSpeed4);

		}
		else
		{
		    digitalWrite(_ZW_M4_N_, HIGH);
		     if((Rev == 1) || (Rev ==2))
		    {
			int PWMvalue = 255 - motorSpeed4;
		 	SoftPWMSet(_ZW_M4_P_, PWMvalue);
			}
			else if(Rev ==3)
			{
				SoftPWMSet(_ZW_M4_P_, motorSpeed4);
			}
		}


	}
	motorDir4 = dir;
    motorState4 = RUN;
}

/*********************************************************************************************************
** Function name: setSpeedDir
** Descriptions:  set motor  direction
*********************************************************************************************************/
void ZeroLEVEL4::setSpeedDir(int ispeed, unsigned char dir)
{
    setSpeedDir1(ispeed, dir);
    setSpeedDir2(ispeed, dir);
    setSpeedDir3(ispeed, dir);
    setSpeedDir4(ispeed, dir);
}

/*********************************************************************************************************
** Function name: setSpeedDir1
** Descriptions:  set motor1 speed and direction
*********************************************************************************************************/
void ZeroLEVEL4::setSpeedDir1(int ispeed, unsigned char dir)
{
     motorDir1 = dir;


	if(motorDir1 == DIRF)
	{
		digitalWrite(_ZW_M1_N_, LOW);
		SoftPWMSet(_ZW_M1_P_, ispeed);

	}
	else
	{
	    digitalWrite(_ZW_M1_N_, HIGH);
	     if((Rev == 1) || (Rev ==2))
	    {
		int PWMvalue = 255 - ispeed;
	 	SoftPWMSet(_ZW_M1_P_, PWMvalue);
	 	}
		else if(Rev ==3)
		{
			SoftPWMSet(_ZW_M1_P_, ispeed);

		}
	}

    motorState1 = RUN;

}

/*********************************************************************************************************
** Function name: setSpeedDir
** Descriptions:  set motor 2 direction
*********************************************************************************************************/
void ZeroLEVEL4::setSpeedDir2(int ispeed, unsigned char dir)
{
	motorDir2 = dir;
	if(motorDir2 == DIRF)
	{
		digitalWrite(_ZW_M2_N_, LOW);
		if(Rev ==2)
		{
			digitalWrite(_ZW_M2_P_,HIGH);
		}
		else
		{
			SoftPWMSet(_ZW_M2_P_, ispeed);
		}
	}
	else
	{
		digitalWrite(_ZW_M2_N_, HIGH);
		 if((Rev == 1))
		{
		int PWMvalue = 255 - ispeed;
	 	SoftPWMSet(_ZW_M2_P_, PWMvalue);
		}
		else if(Rev ==2)
		{
			digitalWrite(_ZW_M2_P_,LOW);
		}
		else if(Rev == 3)
		{
		SoftPWMSet(_ZW_M2_P_, ispeed);
		}
	}

    motorState2 = RUN;
}



/*********************************************************************************************************
** Function name: setSpeedDir
** Descriptions:  set motor 3 direction
*********************************************************************************************************/
void ZeroLEVEL4::setSpeedDir3(int ispeed, unsigned char dir)
{
	motorDir3 = dir;
	if(motorDir3 == DIRF)
	{
		digitalWrite(_ZW_M3_N_, LOW);

		if(Rev ==2)
		{
			digitalWrite(_ZW_M3_P_,HIGH);
		}
		else
		{
			SoftPWMSet(_ZW_M3_P_, ispeed);

		}

	}
	else
	{
	    digitalWrite(_ZW_M3_N_, HIGH);
	     if((Rev == 1))
	    {
		int PWMvalue = 255 - ispeed;
	 	SoftPWMSet(_ZW_M3_P_, PWMvalue);
		}
		else if(Rev ==2)
		{
			digitalWrite(_ZW_M3_P_,LOW);
		}
		else if(Rev == 3)
		{
		SoftPWMSet(_ZW_M3_P_, ispeed);
		}
	}

    motorState3 = RUN;
}


/*********************************************************************************************************
** Function name: setSpeedDir
** Descriptions:  set motor 4 direction
*********************************************************************************************************/
void ZeroLEVEL4::setSpeedDir4(int ispeed, unsigned char dir)
{
	motorDir4 = dir;
	if(motorDir4 == DIRF)
	{
		digitalWrite(_ZW_M4_N_, LOW);
		SoftPWMSet(_ZW_M4_P_, ispeed);

	}
	else
	{
	    digitalWrite(_ZW_M4_N_, HIGH);
	     if((Rev == 1) || (Rev ==2))
	    {
		int PWMvalue = 255 - ispeed;
	 	SoftPWMSet(_ZW_M4_P_, PWMvalue);
		}
		else if(Rev ==3)
		{
			SoftPWMSet(_ZW_M4_P_, ispeed);
		}

	}

    motorState4 = RUN;
}


void ZeroLEVEL4::SetDirection(int MotorSet, int Direction)
{
   switch(MotorSet){
   case M1:
   setDir1(Direction);
   break;
   case M2:
   setDir2(Direction);
   break;
   case M1M2:
   setDir1(Direction);
   setDir2(Direction);
   break;
   default:
   break;
}
return;
}

void ZeroLEVEL4::SetSpeed(int MotorSet, int Speed)
{

   switch(MotorSet){
   case M1:
   setSpeed1(Speed);
   break;
   case M2:
   setSpeed2(Speed);
   break;
   case M1M2:
   setSpeed1(Speed);
   setSpeed2(Speed);
   break;
   default:
   break;
	}
	return;
}
/*
void ZeroLEVEL4::toneMolody()
{
	// notes in the melody:
	int melody[] = {
	  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
	};
	// note durations: 4 = quarter note, 8 = eighth note, etc.:
	int noteDurations[] = {
	  4, 8, 8, 4, 4, 4, 4, 4};

  for (int thisNote = 0; thisNote < 8; thisNote++) {
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(_ZW_BEEP_, melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(_ZW_BEEP_);
  }


return;
}*/



// Returns true if the address is between the
// minimum and maximum allowed values, false otherwise.
//
// This function is used by the other, higher-level functions
// to prevent bugs and runtime errors due to invalid addresses.
boolean ZeroLEVEL4::eeprom_is_addr_ok(int addr) {
	return ((addr >= EEPROM_MIN_ADDR) && (addr <= EEPROM_MAX_ADDR));
}

// Writes a sequence of bytes to eeprom starting at the specified address.
// Returns true if the whole array is successfully written.
// Returns false if the start or end addresses aren't between
// the minimum and maximum allowed values.
// When returning false, nothing gets written to eeprom.
boolean ZeroLEVEL4::eeprom_write_bytes(int startAddr, const byte* array, int numBytes) {
// counter
int i;
// both first byte and last byte addresses must fall within
// the allowed range
if (!eeprom_is_addr_ok(startAddr) || !eeprom_is_addr_ok(startAddr + numBytes)) {
return false;
}
for (i = 0; i < numBytes; i++) {
EEPROM.write(startAddr + i, array[i]);
}
return true;
}

// Writes a string starting at the specified address.
// Returns true if the whole string is successfully written.
// Returns false if the address of one or more bytes fall outside the allowed range.
// If false is returned, nothing gets written to the eeprom.
boolean ZeroLEVEL4::eeprom_write_string(int addr, const char* string) {

int numBytes; // actual number of bytes to be written
//write the string contents plus the string terminator byte (0x00)
numBytes = strlen(string) + 1;
return eeprom_write_bytes(addr, (const byte*)string, numBytes);
}

// Reads a string starting from the specified address.
// Returns true if at least one byte (even only the string terminator one) is read.
// Returns false if the start address falls outside the allowed range or declare buffer size is zero.
//
// The reading might stop for several reasons:
// - no more space in the provided buffer
// - last eeprom address reached
// - string terminator byte (0x00) encountered.
boolean ZeroLEVEL4::eeprom_read_string(int addr, char* buffer, int bufSize) {
byte ch; // byte read from eeprom
int bytesRead; // number of bytes read so far
if (!eeprom_is_addr_ok(addr)) { // check start address
return false;
}

if (bufSize == 0) { // how can we store bytes in an empty buffer ?
return false;
}
// is there is room for the string terminator only, no reason to go further
if (bufSize == 1) {
buffer[0] = 0;
return true;
}
bytesRead = 0; // initialize byte counter
ch = EEPROM.read(addr + bytesRead); // read next byte from eeprom
buffer[bytesRead] = ch; // store it into the user buffer
bytesRead++; // increment byte counter
// stop conditions:
// - the character just read is the string terminator one (0x00)
// - we have filled the user buffer
// - we have reached the last eeprom address
while ( (ch != 0x00) && (bytesRead < bufSize) && ((addr + bytesRead) <= EEPROM_MAX_ADDR) ) {
// if no stop condition is met, read the next byte from eeprom
ch = EEPROM.read(addr + bytesRead);
buffer[bytesRead] = ch; // store it into the user buffer
bytesRead++; // increment byte counter
}
// make sure the user buffer has a string terminator, (0x00) as its last byte
if ((ch != 0x00) && (bytesRead >= 1)) {
buffer[bytesRead - 1] = 0;
}
return true;
}


void ZeroLEVEL4::Encryption(const char* string){

	des.iv_inc();
	byte plaintext[100];
	strcpy((char *)plaintext,string);
	des.calc_size_n_pad(sizeof(plaintext));

    byte plaintext_p[BUFSIZE];
    des.padPlaintext(plaintext,plaintext_p);
    byte cyphertext[des.get_size()];
    des.tdesCbcEncipher(plaintext_p,cyphertext);
	eeprom_write_bytes(0,cyphertext,sizeof(cyphertext));
	return;
}

boolean ZeroLEVEL4::Decryption(char* plaintext_p)
{
	  char buf[BUFSIZE];
  	  char myStringChar[BUFSIZE];

  //	  byte plaintext_p[BUFSIZE];

  	  des.iv_inc();

  	   eeprom_read_string(0, buf, BUFSIZE);
	   // printf(" Encryption took %lu micros\n",(micros()  - ms));

	    des.calc_size_n_pad(sizeof(buf));
	    des.tdesCbcDecipher(buf,plaintext_p);
	    bool ok = des.CheckPad(plaintext_p,sizeof(plaintext_p));

	   // myString = plaintext_p;
	    //Serial.println(plaintext_p);

	  //    myString = String((char *)plaintext_p);

	   // Serial.println(plaintext_p);
	   if (ok)
	      return true;
	    else
	      return false;
	   //   printf("padding corrupted!");
	   // printf(" Decryption took %lu micros",(micros() - ms));

}

long ZeroLEVEL4::UltrasonicSensor(int _pin)
{
	int Time_out = 40000; //3000us = 50cm  30000 = 5m
	pinMode(_pin, OUTPUT);
	digitalWrite(_pin, LOW);
	delayMicroseconds(2);
	digitalWrite(_pin, HIGH);
	delayMicroseconds(5);
	digitalWrite(_pin,LOW);
	pinMode(_pin,INPUT);

	long duration;
	duration = pulseIn(_pin,HIGH);
	long distance_cm;
	distance_cm = duration/29/2;  //cm
	//distance_cm = duration/74/2; //Inch

	return distance_cm;

}

void ZeroLEVEL4::ServoInit(int pin)
{
	servo0.attach(pin);
}

void ZeroLEVEL4::ServoWrite(int pos)
{

    servo0.write(pos);
}

ZeroLEVEL4 LEVEL4(3);



/*********************************************************************************************************
  END FILE
*********************************************************************************************************/