#include <Beatle.h>
#include <BeatleSerial.h>
#include <EEPROM.h>
#include <DES.h>


DES des;

unsigned long ms;

#define  EEPROM_MIN_ADDR  0
#define  EEPROM_MAX_ADDR  1024
#define BUFSIZE    128

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

const char myMelody[] PROGMEM =
  "! O5 L16 agafaea dac+adaea fa<aa<bac#a dac#adaea f"
  "O6 dcd<b-d<ad<g d<f+d<gd<ad<b- d<dd<ed<f+d<g d<f+d<gd<ad"
  "L8 MS <b-d<b-d MLe-<ge-<g MSc<ac<a ML d<fd<f O5 MS b-gb-g"
  "ML >c#e>c#e MS afaf ML gc#gc# MS fdfd ML e<b-e<b-"
  "O6 L16ragafaea dac#adaea fa<aa<bac#a dac#adaea faeadaca"
  "<b-acadg<b-g egdgcg<b-g <ag<b-gcf<af dfcf<b-f<af"
  "<gf<af<b-e<ge c#e<b-e<ae<ge <fe<ge<ad<fd"
  "O5 e>ee>ef>df>d b->c#b->c#a>df>d e>ee>ef>df>d"
  "e>d>c#>db>d>c#b >c#agaegfe f O6 dc#dfdc#<b c#4";

// Returns true if the address is between the
// minimum and maximum allowed values, false otherwise.
//
// This function is used by the other, higher-level functions
// to prevent bugs and runtime errors due to invalid addresses.
boolean eeprom_is_addr_ok(int addr) {
  return ((addr >= EEPROM_MIN_ADDR) && (addr <= EEPROM_MAX_ADDR));
}

// Writes a sequence of bytes to eeprom starting at the specified address.
// Returns true if the whole array is successfully written.
// Returns false if the start or end addresses aren't between
// the minimum and maximum allowed values.
// When returning false, nothing gets written to eeprom.
boolean eeprom_write_bytes(int startAddr, const byte* array, int numBytes) {
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
boolean eeprom_write_string(int addr, const char* string) {

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
boolean eeprom_read_string(int addr, char* buffer, int bufSize) {
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


void Encryption(const char* string) {

  des.iv_inc();
  byte plaintext[BUFSIZE];
  strcpy((char *)plaintext, string);
  des.calc_size_n_pad(sizeof(plaintext));

  byte plaintext_p[BUFSIZE];
  des.padPlaintext(plaintext, plaintext_p);
  byte cyphertext[des.get_size()];
  des.tdesCbcEncipher(plaintext_p, cyphertext);
  //eeprom_write_bytes(257,cyphertext,sizeof(cyphertext));
  eeprom_write_bytes(893, cyphertext, sizeof(cyphertext));
  return;
}

uint8_t prod_year;
uint8_t prod_month;
uint8_t prod_day;
uint8_t deliver_year;
uint8_t deliver_month;
uint8_t deliver_day;
uint8_t expire_year;
uint8_t expire_month;
uint8_t expire_day;
char eeprom_str[128];

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
  Serial.print("Command Recieved is : 0x"); Serial.println(bSerial.recStack.commandValue, HEX);
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
    case beatleCMD::PLAYBUZZER:
      if (!beatle.buzzer.isPlaying()) {
        beatle.buzzer.playFromProgramSpace(myMelody);
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
      /*if (bSerial.recStack.paramMSB == beatleCMD::LEDOFF) {
        for (int i = 1; i <= 12; i = i + (1)) {
          LEDStrip_2.strip.setPixelColor((i) - 1, LEDStrip_2.strip.Color(0, 0, 0));
        }
        LEDStrip_2.strip.show();
        }
        else if (bSerial.recStack.paramMSB == beatleCMD::LEDON) {
        for (int i = 1; i <= 12; i = i + (1)) {
          if (bSerial.recStack.paramLSB == beatleCMD::LEDWHITE) {
            LEDStrip_2.strip.setPixelColor((i) - 1, LEDStrip_2.strip.Color(255, 255, 255));
          }
          else if (bSerial.recStack.paramLSB == beatleCMD::LEDRED) {
            LEDStrip_2.strip.setPixelColor((i) - 1, LEDStrip_2.strip.Color(255, 0, 0));
          }
          else if (bSerial.recStack.paramLSB == beatleCMD::LEDGREEN) {
            LEDStrip_2.strip.setPixelColor((i) - 1, LEDStrip_2.strip.Color(0, 255, 0));
          }
          else if (bSerial.recStack.paramLSB == beatleCMD::LEDBLUE) {
            LEDStrip_2.strip.setPixelColor((i) - 1, LEDStrip_2.strip.Color(0, 0, 255));
          }
        }
        LEDStrip_2.strip.show();
        }*/
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

    case beatleCMD::WRITE_EEPROM:
      deliver_year = (bSerial.recStack.paramMSB >> 3) & 0x1F;  //bit7~bit3 of paraMSB represent YEAR, totaly 5 bits
      deliver_month = ((bSerial.recStack.paramMSB & 0x7) << 1) | ((bSerial.recStack.paramLSB >> 7) & 0x1) ;  //bit2~bit0 of paramMSB and bit7 of paramLSB combines the MONTH, totally 4 bits
      deliver_day = (bSerial.recStack.paramLSB >> 2) & 0x1F; //bit6~bit2 of paramLSB represent DAY, totally 5 bits

      expire_year = deliver_year;
      expire_month = deliver_month + 3;
      expire_day = deliver_day - 1;
      //      Serial.print("Deliver YEAR : "); Serial.println(deliver_year);
      //      Serial.print("Deliver MON  : "); Serial.println(deliver_month);
      //      Serial.print("Deliver DAY  : "); Serial.println(deliver_day);

      if (expire_month > 12) {
        expire_month -= 12;
        expire_year = deliver_year + 1;
      }
      sprintf(eeprom_str, "***ZeroWorkshop PD:20%d-%d-%d DOD:20%d-%d-%d EXP: 20%d-%d-%d***", prod_year, prod_month, prod_day, deliver_year, deliver_month, deliver_day, expire_year, expire_month, expire_day);
      //      Serial.println(eeprom_str);
      des.init("ZeroWorkshop-Shanghai-2018\0", (unsigned long long int)0);
      Encryption(eeprom_str);

      break;

    case beatleCMD::SET_PRODDATE:

      prod_year = (bSerial.recStack.paramMSB >> 3) & 0x1F;  //bit7~bit3 of paraMSB represent YEAR, totaly 5 bits
      prod_month = ((bSerial.recStack.paramMSB & 0x7) << 1) | ((bSerial.recStack.paramLSB >> 7) & 0x1) ;  //bit2~bit0 of paramMSB and bit7 of paramLSB combines the MONTH, totally 4 bits
      prod_day = (bSerial.recStack.paramLSB >> 2) & 0x1F; //bit6~bit2 of paramLSB represent DAY, totally 5 bits
      //      Serial.print("Prod YEAR : "); Serial.println(prod_year);
      //      Serial.print("Prod MON  : "); Serial.println(prod_month);
      //      Serial.print("Prod DAY  : "); Serial.println(prod_day);
      break;

    ///////////////////////////////////////////////////////////////////////////
    case beatleCMD::SEND_MZSTR_P1:
      //Serial.print(bSerial.recStack.paramMSB); Serial.print("\t"); Serial.println(bSerial.recStack.paramLSB);
      if (!MZString_END) {   //If the command is end already, no character will be added
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

      if (!MZString_END) {   //The last 1 or 2 command character will be added to the command string, then no command character will be recieved
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

      if (!MZString_END) {   //The last 1 or 2 command character will be added to the command string, then no command character will be recieved
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
      beatle.goToTarget();
      
      //After the beatle reach the target intersection, beatle chasis send a status indicating target reached.
      //Reuse the code of GET_STATUS
      delay(10);
      bSerial.sendStack.commandValue = beatleCMD::GET_STATUS_;
      bSerial.sendStack.feedbackValue = beatleCMD::FEEDBACK;
      bSerial.sendStack.paramMSB = 0xCC;
      bSerial.sendStack.paramLSB = 0xDD;

      bSerial.findChecksum(&bSerial.sendStack);
      bSerial.sendData();
      break;
  }

  bSerial.recStack.commandValue  = 0x00;
}
