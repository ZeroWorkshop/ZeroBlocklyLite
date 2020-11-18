﻿#include <Beatle.h>
#include <BeatleSerial.h>


unsigned long ms;


BeatleSerial bSerial;
Beatle beatle;
ZeroRGBLED LEDStrip_2(2, 12);
unsigned int sensor_values[7];

#define WHITE_LOW   0
#define WHITE_HIGH  400
#define BLACK_LOW   600
#define BLACK_HIGH  2500

#define CMD_S 0x0
#define CMD_B 0x1
#define CMD_R 0x2
#define CMD_L 0x3
static void (*reset_this_CPU)(void) = 0x0000;



String cmd_str = "";
bool MZString_END = false;
void beatleSlavesetup() {
  // put your setup code here, to run once:
  pinMode(DSL, INPUT);
  pinMode(DSR, INPUT);
  Serial.begin(115200);
  bSerial.begin(Serial);
  LEDStrip_2.init();
  beatle.LineSensors.init();

  for (int i = 1; i <= 12; i = i + (1)) {
    LEDStrip_2.strip.setPixelColor((i) - 1, LEDStrip_2.strip.Color(0, 0, 0));
  }
  LEDStrip_2.strip.show();

  beatle.Setup_MazeSolver();
}

void beatleSlaveloop() {
  uint8_t tempBuffer;
  uint8_t cmdBuffer[beatleCMD::STACK_SIZE];
  uint8_t tmp[beatleCMD::STACK_SIZE];
  uint8_t index = 0;
  uint8_t offset;
  uint8_t MZstart_byte;
  uint8_t MZversion;
  uint8_t MZlength;
  uint8_t MZcommandValue;
  uint8_t MZend_byte;
  uint8_t MZString[MZlength];
  bool runOnceAlready;

  while (Serial.available() < beatleCMD::STACK_SIZE);



  while (Serial.available()) {
    tempBuffer = Serial.read();
    cmdBuffer[index++] = tempBuffer;
  }

  for (uint8_t i = 0; i < beatleCMD::STACK_SIZE; i++) {
    if (cmdBuffer[i] == beatleCMD::SB &&
        cmdBuffer[(i + 1) > 9 ? (i - 9) : (i + 1)] == beatleCMD::VER &&
        cmdBuffer[(i + 2) > 9 ? (i - 8) : (i + 2)] == beatleCMD::LEN) {
      offset = i;
    }
  }

  for (uint8_t j = 0; j < beatleCMD::STACK_SIZE; j++) {
    tmp[j] = cmdBuffer[offset + j > 9 ? (offset + j - 10) : (offset + j)];
  }

  bSerial.recStack.start_byte    = tmp[0];
  bSerial.recStack.version       = tmp[1];
  bSerial.recStack.length        = tmp[2];
  bSerial.recStack.commandValue  = tmp[3];
  bSerial.recStack.feedbackValue = tmp[4];
  bSerial.recStack.paramMSB      = tmp[5];
  bSerial.recStack.paramLSB      = tmp[6];
  bSerial.recStack.checksumMSB   = tmp[7];
  bSerial.recStack.checksumLSB   = tmp[8];
  bSerial.recStack.end_byte      = tmp[9];
  //Serial.print("Command Recieved is : 0x"); Serial.println(bSerial.recStack.commandValue, HEX);
  switch (bSerial.recStack.commandValue) {
    //////////////////////////////////////////////////////////////////////////////////////////////

    case beatleCMD::RUNWHEELS:

      Serial.print(bSerial.recStack.paramMSB); Serial.print("\t"); Serial.println(bSerial.recStack.paramLSB);
      if (bSerial.recStack.paramMSB == beatleCMD::RUNFORWARD) {
        beatle.motors.setSpeeds(bSerial.recStack.paramLSB, bSerial.recStack.paramLSB);
      }
      else if (bSerial.recStack.paramMSB == beatleCMD::RUNBACKWARD) {
        beatle.motors.setSpeeds((-1) * bSerial.recStack.paramLSB, (-1) * bSerial.recStack.paramLSB);
      }
      break;

    case beatleCMD::RUNLEFT:
      Serial.print(bSerial.recStack.paramMSB); Serial.print("\t"); Serial.println(bSerial.recStack.paramLSB);
      if (bSerial.recStack.paramMSB == beatleCMD::RUNFORWARD) {
        beatle.motors.setLeftSpeed(bSerial.recStack.paramLSB);
      }
      else if (bSerial.recStack.paramMSB == beatleCMD::RUNBACKWARD) {
        beatle.motors.setLeftSpeed((-1) * bSerial.recStack.paramLSB);
      }
      break;

    case beatleCMD::RUNRIGHT:
      Serial.print(bSerial.recStack.paramMSB); Serial.print("\t"); Serial.println(bSerial.recStack.paramLSB);
      if (bSerial.recStack.paramMSB == beatleCMD::RUNFORWARD) {
        beatle.motors.setRightSpeed(bSerial.recStack.paramLSB);
      }
      else if (bSerial.recStack.paramMSB == beatleCMD::RUNBACKWARD) {
        beatle.motors.setRightSpeed((-1) * bSerial.recStack.paramLSB);
      }
      break;
    
    //////////////////////////////////////////////////////////////////////////////////////////////
    case beatleCMD::SETLED:
      uint8_t current_id;
      uint8_t current_red;
      uint8_t current_green;
      uint8_t current_blue;
      if (bSerial.recStack.paramMSB == beatleCMD::SETLED_ID)
      {
        current_id  = bSerial.recStack.paramLSB ;
      }
      else if (bSerial.recStack.paramMSB == beatleCMD::SETLED_RED)
      {
        current_red = bSerial.recStack.paramLSB ;
      }
      else if (bSerial.recStack.paramMSB == beatleCMD::SETLED_GREEN)
      {
        current_green = bSerial.recStack.paramLSB ;
      }
      else if (bSerial.recStack.paramMSB == beatleCMD::SETLED_BLUE)
      {
        current_blue = bSerial.recStack.paramLSB ;
      }

      if (current_id == beatleCMD::ALL_LED)
      {
        for (int i = 0; i < 12; i = i + (1)) {
          bSerial.rgb_data[i].red = current_red;
          bSerial.rgb_data[i].green = current_green;
          bSerial.rgb_data[i].blue = current_blue;
        }
      }
      else
      {
        bSerial.rgb_data[current_id].red = current_red;
        bSerial.rgb_data[current_id].green = current_green;
        bSerial.rgb_data[current_id].blue = current_blue;
      }
      
      break;
    case beatleCMD::EXELED:
      for (int i = 1; i <= 12; i = i + (1)) {
        LEDStrip_2.strip.setPixelColor((i) - 1, LEDStrip_2.strip.Color(bSerial.rgb_data[i].red, bSerial.rgb_data[i].green, bSerial.rgb_data[i].blue));
      }
      LEDStrip_2.strip.show();
      break;

    //////////////////////////////////////////////////////////////////////////////////////////////
    case beatleCMD::GET_STATUS_:
      {
        delay(10);
        bSerial.sendStack.commandValue = beatleCMD::GET_STATUS_;
        bSerial.sendStack.feedbackValue = beatleCMD::FEEDBACK;
        bSerial.sendStack.paramMSB = 0xCC;
        bSerial.sendStack.paramLSB = 0xDD;

        bSerial.findChecksum(&bSerial.sendStack);
        bSerial.sendData();
      }
      break;

    //////////////////////////////////////////////////////////////////////////////////////////////
    case beatleCMD::GET_BUTTON_STATE:
      {
        delay(10);
        uint8_t buttonPin = bSerial.recStack.paramLSB;
        pinMode(buttonPin, INPUT);

        if (digitalRead(buttonPin) == HIGH)
          bSerial.sendStack.paramMSB = 0xF1;
        else
          bSerial.sendStack.paramMSB = 0xF0;
        {
          bSerial.sendStack.commandValue = beatleCMD::GET_BUTTON_STATE;
          bSerial.sendStack.feedbackValue = beatleCMD::FEEDBACK;
          bSerial.sendStack.paramLSB = bSerial.recStack.paramLSB;

          bSerial.findChecksum(&bSerial.sendStack);
          bSerial.sendData();
        }
      }
      break;




    //////////////////////////////////////////////////////////////////////////////////////////////
    case beatleCMD::GET_IRSENSORS:
      delay(10);
      if (digitalRead(DSL) == LOW)
        bSerial.sendStack.paramMSB = 0xA0;
      else if (digitalRead(DSL) == HIGH)
        bSerial.sendStack.paramMSB = 0xA1;

      if (digitalRead(DSR) == LOW)
        bSerial.sendStack.paramLSB = 0xA0;
      else if (digitalRead(DSR) == HIGH)
        bSerial.sendStack.paramLSB = 0xA1;

      bSerial.sendStack.commandValue = beatleCMD::GET_IRSENSORS;
      bSerial.sendStack.feedbackValue = beatleCMD::FEEDBACK;

      bSerial.findChecksum(&bSerial.sendStack);
      bSerial.sendData();


      break;



    //////////////////////////////////////////////////////////////////////////////////////////////
    case beatleCMD::GET_LINESENSORS:
      delay(10);
      bSerial.sendStack.paramMSB = 0x0;
      bSerial.sendStack.paramLSB = 0x0;
      beatle.LineSensors.read(sensor_values);
      for (int i = 0; i < 7; i++) {
        if (sensor_values[i] >= WHITE_LOW && sensor_values[i] <= WHITE_HIGH) {
          //Serial.print(i); Serial.print(": white ---- "); Serial.println(sensor_values[i]);
          bSerial.sendStack.paramMSB &= ~(1 << i);    //set corresponding bit of paraMSB to 0, it means the value is a valid white/black
          bSerial.sendStack.paramLSB &= ~(1 << i);    //set corresponding bit of paraLSB to 0, it means the sensor read a WHITE
        }
        else if (sensor_values[i] >= BLACK_LOW && sensor_values[i] <= BLACK_HIGH) {
          //Serial.print(i); Serial.print(": black ---- "); Serial.println(sensor_values[i]);
          bSerial.sendStack.paramMSB &= ~(1 << i);    //set corresponding bit of paraMSB to 0, it means the value is a valid white/black
          bSerial.sendStack.paramLSB |= 1 << i;       //set corresponding bit of paraLSB to 1, it means the sensor read a BLACK
        }
        else if (sensor_values[i] > WHITE_HIGH && sensor_values[i] < BLACK_LOW) {
          //Serial.print(i); Serial.print(": invalid ---- "); Serial.println(sensor_values[i]);
          bSerial.sendStack.paramMSB |=  1 << i;    //set corresponding bit of paraMSB to 1, it means the value is an invalid value
        }
      }



      bSerial.sendStack.commandValue = beatleCMD::GET_LINESENSORS;
      bSerial.sendStack.feedbackValue = beatleCMD::FEEDBACK;

      bSerial.findChecksum(&bSerial.sendStack);
      bSerial.sendData();
      break;

    case beatleCMD::RESET_BEATLE:
      reset_this_CPU();
      break;

    
    ///////////////////////////////////////////////////////////////////////////
    case beatleCMD::SEND_MZSTR_P1:
      //Serial.print(bSerial.recStack.paramMSB); Serial.print("\t"); Serial.println(bSerial.recStack.paramLSB);
      //if (!MZString_END)
      { //If the command is end already, no character will be added
        if (bSerial.recStack.paramMSB == beatleCMD::GOSTRAIGHT) {
          cmd_str += "S";
        }
        else if (bSerial.recStack.paramMSB == beatleCMD::GOBACK) {
          cmd_str += "B";
        }
        else if (bSerial.recStack.paramMSB == beatleCMD::GORIGHT) {
          cmd_str += "R";
        }
        else if (bSerial.recStack.paramMSB == beatleCMD::GOLEFT) {
          cmd_str += "L";
        }

        if (bSerial.recStack.paramLSB == beatleCMD::GOSTRAIGHT) {
          cmd_str += "S";
        }
        else if (bSerial.recStack.paramLSB == beatleCMD::GOBACK) {
          cmd_str += "B";
        }
        else if (bSerial.recStack.paramLSB == beatleCMD::GORIGHT) {
          cmd_str += "R";
        }
        else if (bSerial.recStack.paramLSB == beatleCMD::GOLEFT) {
          cmd_str += "L";
        }
      }
      //Serial.print("cmd_str = "); Serial.println(cmd_str);

      break;

    case beatleCMD::SEND_MZSTR_FP2:    //go to FinishLine command

      //if (!MZString_END)
      { //The last 1 or 2 command character will be added to the command string, then no command character will be recieved
        if (bSerial.recStack.paramMSB == beatleCMD::GOSTRAIGHT) {
          cmd_str += "S";
        }
        else if (bSerial.recStack.paramMSB == beatleCMD::GOBACK) {
          cmd_str += "B";
        }
        else if (bSerial.recStack.paramMSB == beatleCMD::GORIGHT) {
          cmd_str += "R";
        }
        else if (bSerial.recStack.paramMSB == beatleCMD::GOLEFT) {
          cmd_str += "L";
        }

        if (bSerial.recStack.paramLSB == beatleCMD::GOSTRAIGHT) {
          cmd_str += "S";
        }
        else if (bSerial.recStack.paramLSB == beatleCMD::GOBACK) {
          cmd_str += "B";
        }
        else if (bSerial.recStack.paramLSB == beatleCMD::GORIGHT) {
          cmd_str += "R";
        }
        else if (bSerial.recStack.paramLSB == beatleCMD::GOLEFT) {
          cmd_str += "L";
        }
      }
      MZString_END = true;
      //Serial.println(cmd_str);
      strcpy(beatle.maze_path, cmd_str.c_str());
      beatle.maze_path_length = cmd_str.length();
      beatle.goToFinishLine();


    case beatleCMD::SEND_MZSTR_TP2:    //go to target intersection command

      //if (!MZString_END)
      { //The last 1 or 2 command character will be added to the command string, then no command character will be recieved
        if (bSerial.recStack.paramMSB == beatleCMD::GOSTRAIGHT) {
          cmd_str += "S";
        }
        else if (bSerial.recStack.paramMSB == beatleCMD::GOBACK) {
          cmd_str += "B";
        }
        else if (bSerial.recStack.paramMSB == beatleCMD::GORIGHT) {
          cmd_str += "R";
        }
        else if (bSerial.recStack.paramMSB == beatleCMD::GOLEFT) {
          cmd_str += "L";
        }

        if (bSerial.recStack.paramLSB == beatleCMD::GOSTRAIGHT) {
          cmd_str += "S";
        }
        else if (bSerial.recStack.paramLSB == beatleCMD::GOBACK) {
          cmd_str += "B";
        }
        else if (bSerial.recStack.paramLSB == beatleCMD::GORIGHT) {
          cmd_str += "R";
        }
        else if (bSerial.recStack.paramLSB == beatleCMD::GOLEFT) {
          cmd_str += "L";
        }
      }
      MZString_END = true;
      //Serial.println(cmd_str);
      strcpy(beatle.maze_path, cmd_str.c_str());
      beatle.maze_path_length = cmd_str.length();
      //      beatle.goToTarget();

      //After the beatle reach the target intersection, beatle chasis send a status indicating target reached.
      //Reuse the code of GET_STATUS
      //      delay(10);
      //      bSerial.sendStack.commandValue = beatleCMD::GET_STATUS_;
      //      bSerial.sendStack.feedbackValue = beatleCMD::FEEDBACK;
      //      bSerial.sendStack.paramMSB = 0xCC;
      //      bSerial.sendStack.paramLSB = 0xDD;
      //
      //      bSerial.findChecksum(&bSerial.sendStack);
      //      bSerial.sendData();
      runOnceAlready = false;
      break;
  }
  if (!runOnceAlready)
  {
    bSerial.sendStack.commandValue = beatleCMD::GET_STATUS_;
    bSerial.sendStack.feedbackValue = beatleCMD::FEEDBACK;
    bSerial.sendStack.paramMSB = 0xCC;
    bSerial.sendStack.paramLSB = 0xDD;

    bSerial.findChecksum(&bSerial.sendStack);
    bSerial.sendData();
    runOnceAlready = true;
  }
  bSerial.recStack.commandValue  = 0x00;
}