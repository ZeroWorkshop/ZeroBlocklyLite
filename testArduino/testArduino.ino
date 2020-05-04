#include <Wire.h>
#include <SoftwareSerial.h>
#include "ZeroMotors.h"
#include "Pushbutton.h"
//#include "ZeroBuzzer.h"

//ZeroBuzzer buzzer;

#define PWM_L  5     //M2
#define PWM_R  6     //M4
#define DIR_L  12
#define DIR_R  9
/*
#define PWM_L  6
#define PWM_R  5
#define DIR_L  12
#define DIR_R  13
*/
ZeroMotors motors(PWM_L,DIR_L,PWM_R,DIR_R);
//ZeroMotors motors();
Pushbutton button(ZERO_BUTTON);

#define SENSOR_THRESHOLD  200

#define ABOVE_LINE(sensor)   ((sensor) >SENSOR_THRESHOLD)

#define TURN_SPEED  200
#define SPEED       200
#define _OVERSHOOOT_     100 //(50000/SPEED)

// path[] keeps a log of all the turns made
// since starting the maze
char path[100] = "";
unsigned char path_length = 0; // the length of the path

const int enable_cal = 1;

// move state and function
#define CMD_RESET         0x00

#define CMD_SET_CAL_DATA  0x14
#define CMD_SET_EMITTER   0x15
#define CMD_SET_MAX_VAL   0x16
#define CMD_SET_DEVID     0x17

#define CMD_GET_CAL_DATA        0x24
#define CMD_GET_POSITION_DATA        0x26
#define CMD_GET_FINAL_DATA      0x27
#define CMD_GET_RAW_DATA        0x28
#define I2C_DEFAULT_ADDR        0x9
#define _slot                   0x0
char cmdBuf[18];

long _CAL_MAX_[8]={0,0,0,0,0,0,0,0};
long _CAL_MIN_[8]={5000,5000,5000,5000,5000,5000,5000,5000};

/*************************************************
 * Public Constants
 *************************************************/

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations_[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

void toneMelody();
void goToFinishLine();
void simplifyPath();
void solveMaze();
void followSegment();
char selectTurn(unsigned char found_left, unsigned char found_straight,
  unsigned char found_right);
  void turn(char dir);

/**
 * par Function
 *    sendCmd
 * par Description
 *    Send command to Motor.
 * param[in]
 *    None
 * par Output
 *    None
 * par Return
 *    None
 * par Others
 *    None
 */
void sendCmd(uint8_t address)
{
  Wire.beginTransmission(address);
  for(int i=0;i<18;i++)
    Wire.write(cmdBuf[i]);
  Wire.endTransmission();
}

/**
 * par Function
 *    reset
 * par Description
 *    Reset the parameter of Motor.
 * par Output
 *    None
 * par Return
 *    None
 * par Others
 *    None
 */
void reset(uint8_t address)
{
  cmdBuf[0] = _slot;
  cmdBuf[1] = CMD_RESET;
  sendCmd(address);
  delay(2);
}

/**
 * par Function
 *    setDevid
 * par Description
 *    Set the devid to Motor.
 * param[in]
 *    devid - the I2C adress
 * par Output
 *    None
 * par Return
 *    None
 * par Others
 *    None
 */
void setDevid(uint8_t address,uint8_t devid)
{
  cmdBuf[0] = _slot;
  cmdBuf[1] = CMD_SET_DEVID;
  cmdBuf[2] = devid;
  sendCmd(address);
}

void setEmitterOn(uint8_t address)
{
  cmdBuf[0] = _slot;
  cmdBuf[1] = CMD_SET_EMITTER;
  cmdBuf[2] = 0x1;
  sendCmd(address);
}

void setEmitterOff(uint8_t address)
{
  cmdBuf[0] = _slot;
  cmdBuf[1] = CMD_SET_EMITTER;
  cmdBuf[2] = 0x1;
  sendCmd(address);

}

void setMaxVal(uint8_t address,long max_val)
{
  cmdBuf[0] = _slot;
  cmdBuf[1] = CMD_SET_MAX_VAL;
  memcpy(cmdBuf+2,&max_val,4);
  sendCmd(address);

}

void setCalData(uint8_t address, uint8_t sensor_id, long * max_val, long * min_val)
{
  cmdBuf[0] = sensor_id;
  cmdBuf[1] = CMD_SET_CAL_DATA;
  memcpy(cmdBuf+2,&max_val,4);
  memcpy(cmdBuf+6,&min_val,4);
  sendCmd(address);
  delay(10);
}

void getCalData(uint8_t address, uint8_t sensor_id, long * max_val, long * min_val)
{
   char buf[8];
  Wire.beginTransmission(address);
  Wire.write(sensor_id);
  Wire.write(CMD_GET_CAL_DATA);
  Wire.endTransmission(0);
  Wire.requestFrom(address,(uint8_t)8);
  for(int i=0;i<4;i++)
  {
    buf[i] = Wire.read();
  }
  *max_val = *(long*)buf;
  for(int i=0;i<4;i++)
  {
    buf[i] = Wire.read();
  }
  *min_val = *(long*)buf;
}

void getRawData(uint8_t address,long *d)
{
  long raw_value;
  char buf[8];
  Wire.beginTransmission(address);
  Wire.write(_slot);
  Wire.write(CMD_GET_RAW_DATA);
  Wire.endTransmission(0);
  Wire.requestFrom(address,(uint8_t)32);

  for(int j = 0;j<8;j++)
  {
  for(int i=0;i<4;i++)
  {
    buf[i] = Wire.read();
  }
  *(d+j) = *(long*)buf;

   Serial.print( *(d+j));
    Serial.print(" ");
  }
  Serial.println();
 // delayMicroseconds(1000);
}

void getFinalData(uint8_t address,long *d)
{
  long raw_value;
  char buf[8];
  Wire.beginTransmission(address);
  Wire.write(_slot);
  Wire.write(CMD_GET_FINAL_DATA);
  Wire.endTransmission(0);
  Wire.requestFrom(address,(uint8_t)32);

  for(int j = 0;j<8;j++)
  {
  for(int i=0;i<4;i++)
  {
    buf[i] = Wire.read();
  }
  *(d+j) = *(long*)buf;
   Serial.print( *(d+j));
    Serial.print(" ");
  }
  Serial.println();
  //delayMicroseconds(1500);
}

void getPosition(uint8_t address,long *data)
{
  long raw_value;
  char buf[8];
  Wire.beginTransmission(address);
  Wire.write(_slot);
  Wire.write(CMD_GET_POSITION_DATA);
  Wire.endTransmission(0);
  Wire.requestFrom(address,(uint8_t)4);

  for(int i=0;i<4;i++)
  {
    buf[i] = Wire.read();
  }
  *data = *(long*)buf;

}

/*
void getRawData(uint8_t address,long * d1, long * d2, long * d3 , long *d4, long *d5,long *d6, long *d7, long *d8)
{
  long raw_value;
  char buf[8];
  Wire.beginTransmission(address);
  Wire.write(_slot);
  Wire.write(CMD_GET_RAW_DATA);
  Wire.endTransmission(0);
  Wire.requestFrom(address,(uint8_t)32);
  for(int i=0;i<4;i++)
  {
    buf[i] = Wire.read();
  }
  *d1 = *(long*)buf;
  for(int i=0;i<4;i++)
  {
    buf[i] = Wire.read();
  }
  *d2 = *(long*)buf;
  for(int i=0;i<4;i++)
  {
    buf[i] = Wire.read();
  }
  *d3 = *(long*)buf;
  for(int i=0;i<4;i++)
  {
    buf[i] = Wire.read();
  }
  *d4 = *(long*)buf;
    for(int i=0;i<4;i++)
  {
    buf[i] = Wire.read();
  }
  *d5 = *(long*)buf;
    for(int i=0;i<4;i++)
  {
    buf[i] = Wire.read();
  }
  *d6 = *(long*)buf;
   for(int i=0;i<4;i++)
  {
    buf[i] = Wire.read();
  }
  *d7 = *(long*)buf;
    for(int i=0;i<4;i++)
  {
    buf[i] = Wire.read();
  }
  *d8 = *(long*)buf;

 // return raw_value;
}*/

void getRawData(uint8_t address,uint8_t sensor_id,long * dValue)
{
  long raw_value;
  char buf[8];
  Wire.beginTransmission(address);
  Wire.write(sensor_id);
  Wire.write(CMD_GET_RAW_DATA);
  Wire.endTransmission(0);
  Wire.requestFrom(address,(uint8_t)4);
  for(int i=0;i<4;i++)
  {
    buf[i] = Wire.read();
  }
  *dValue = *(long*)buf;

 // return raw_value;
}

void getFinalData(uint8_t address,uint8_t sensor_id,long * dValue)
{
  long raw_value;
  char buf[8];
  Wire.beginTransmission(address);
  Wire.write(sensor_id);
  Wire.write(CMD_GET_FINAL_DATA);
  Wire.endTransmission(0);
  Wire.requestFrom(address,(uint8_t)4);
  for(int i=0;i<4;i++)
  {
    buf[i] = Wire.read();
  }
  *dValue = *(long*)buf;

 // return raw_value;
}

void calibration()
{
     long sensor_raw_data[8];
     getRawData(0x9,sensor_raw_data);
     for(int i = 0; i<8; i++)
     {
        if(_CAL_MAX_[i]< sensor_raw_data[i]) _CAL_MAX_[i] = sensor_raw_data[i];
        if(_CAL_MIN_[i]> sensor_raw_data[i]) _CAL_MIN_[i] = sensor_raw_data[i];


      }
    //  Serial.println();
}

void turn(char dir)
{
  unsigned short count = 0;
  unsigned short last_status = 0;
  long  sensors[8];
  delay(200);

  switch(dir)
  {
    case 'L':
    case 'B':
      motors.setSpeeds(-TURN_SPEED,TURN_SPEED);
      while(count<2)
      {
        getFinalData(0x9,sensors);
        count += ABOVE_LINE(sensors[2])^last_status;
        last_status = ABOVE_LINE(sensors[2]);

      }
    break;
    case 'R':
      motors.setSpeeds(TURN_SPEED,-TURN_SPEED);
      while(count<2)
      {
        getFinalData(0x9,sensors);
        count += ABOVE_LINE(sensors[6])^last_status;
        last_status = ABOVE_LINE(sensors[6]);
       }
       break;
    case 'S':
      break;
  }
}

char selectTurn(unsigned char found_left,unsigned char found_straight,unsigned char found_right)
{
   if(found_left)
   return 'L';
   else if(found_straight)
   return 'S';
   else if(found_right)
   return 'R';
   else
   return 'B';
 }

 void followSegment()
 {
    unsigned long position;
    long sensors[8];
    int offset_from_center;
    int power_difference;

    while(1)
    {

        getFinalData(0x9,sensors);
        getPosition(0x9,&position);
        offset_from_center = ((int)position) - 3500;
        power_difference = offset_from_center/2;
        if(power_difference > SPEED)
          power_difference = SPEED;
        if(power_difference < -SPEED)
          power_difference = -SPEED;

        if(power_difference < 0)
            motors.setSpeeds(SPEED + power_difference, SPEED);
        else
            motors.setSpeeds(SPEED, SPEED - power_difference);

        if(!ABOVE_LINE(sensors[0]) && !ABOVE_LINE(sensors[1]) && !ABOVE_LINE(sensors[2]) && !ABOVE_LINE(sensors[3]) && !ABOVE_LINE(sensors[4]) && !ABOVE_LINE(sensors[5])&& !ABOVE_LINE(sensors[6])&& !ABOVE_LINE(sensors[7]))
        {
      // intersection.  Must be a dead end.
            return;
        }
         else if(ABOVE_LINE(sensors[0]) || ABOVE_LINE(sensors[7]))
        {
          // Found an intersection.
          return;
        }
     }

 }

void solveMaze()
{
  while(1)
  {
    followSegment();
    unsigned char found_left = 0;
    unsigned char found_straight = 0;
    unsigned char found_right = 0;
    long sensors[8];

    getFinalData(0x9,sensors);

 // if(ABOVE_LINE(sensors[0]) || ABOVE_LINE(sensors[1]) )
  if(ABOVE_LINE(sensors[0]) )
    found_left = 1;
    //if(ABOVE_LINE(sensors[6]) ||ABOVE_LINE(sensors[7]))
     if(ABOVE_LINE(sensors[7]))
    found_right = 1;
    motors.setSpeeds(SPEED,SPEED);
    delay(_OVERSHOOOT_);
    getFinalData(0x9,sensors);
    if(ABOVE_LINE(sensors[0])  )
    found_left = 1;
    if(ABOVE_LINE(sensors[6]) )
    found_right = 1;

   delay(_OVERSHOOOT_);
   getFinalData(0x9,sensors);
     if(ABOVE_LINE(sensors[0]) )
    found_left = 1;
    if(ABOVE_LINE(sensors[6]))
    found_right = 1;


    if(ABOVE_LINE(sensors[1]) ||ABOVE_LINE(sensors[2]) || ABOVE_LINE(sensors[3]) || ABOVE_LINE(sensors[4]) || ABOVE_LINE(sensors[5])|| ABOVE_LINE(sensors[6]))
            found_straight = 1;

    if(ABOVE_LINE(sensors[1]) ||ABOVE_LINE(sensors[2]) && ABOVE_LINE(sensors[3]) && ABOVE_LINE(sensors[4]) && ABOVE_LINE(sensors[5])|| ABOVE_LINE(sensors[6]))
        {
          motors.setSpeeds(0,0);
          break;
        }

        // Intersection identification is complete.
        unsigned char dir = selectTurn(found_left, found_straight, found_right);

        // Make the turn indicated by the path.
    turn(dir);

        // Store the intersection in the path variable.
        path[path_length] = dir;
        //Terminal.print(path_length);Terminal.print(" ");
        //Terminal.println(dir);
        path_length++;

        // You should check to make sure that the path_length does not
        // example.

        // Simplify the learned path.
        simplifyPath();
     }
}

// Now enter an infinite loop - we can re-run the maze as many
// times as we want to.
void goToFinishLine()
{
  long sensors[8];
  int i = 0;

  // Turn around if the Zumo is facing the wrong direction.
  if(path[0] == 'B')
  {
    turn('B');
    i++;
  }

  for(;i<path_length;i++)
  {

    followSegment();

    // Drive through the intersection.
    motors.setSpeeds(SPEED, SPEED);
    delay(_OVERSHOOOT_);

    // Make a turn according to the instruction stored in
    // path[i].
    turn(path[i]);
  }

  // Follow the last segment up to the finish.
  followSegment();

  // The finish line has been reached.
  // Return and wait for another button push to
  // restart the maze.

  getFinalData(0x9,sensors);
  motors.setSpeeds(0,0);

  return;
}

// simplifyPath analyzes the path[] array and reduces all the
// turns. For example: Right turn + Right turn = (1) Back turn.
void simplifyPath()
{

  // only simplify the path if the second-to-last turn was a 'B'
  if(path_length < 3 || path[path_length - 2] != 'B')
  return;

  int total_angle = 0;
  int i;

  for(i = 1; i <= 3; i++)
  {
    switch(path[path_length - i])
    {
      case 'R':
        total_angle += 90;
        break;
      case 'L':
        total_angle += 270;
        break;
      case 'B':
        total_angle += 180;
        break;
    }
  }

  // Get the angle as a number between 0 and 360 degrees.
  total_angle = total_angle % 360;

  // Replace all of those turns with a single one.
  switch(total_angle)
  {
    case 0:
      path[path_length - 3] = 'S';
      break;
    case 90:
      path[path_length - 3] = 'R';
      break;
    case 180:
      path[path_length - 3] = 'B';
      break;
    case 270:
      path[path_length - 3] = 'L';
      break;
  }

  // The path is now two steps shorter.
  path_length -= 2;
}

void toneMelody()
{
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations_[thisNote];
    tone(8, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
}

#include    "ZeroWorkshop_lib.h"

#include    "ZeroWorkshop_Macro_Definitions.h"

int ProgramSelected;

void setup()
{
    toneMelody();
  Wire.begin();
  Serial.begin(115200);
  setMaxVal(0x9,2000);
  motors.flipM2Motor(1);
  button.waitForButton();
  delay(1000);
  if(enable_cal)
  {
     Serial.println("Calibration");
  for(int i = 0; i < 160; i++)
  {
    if ((i > 20 && i <= 60) || (i > 100 && i <= 140))
      motors.setSpeeds(-200, 200);
    else
      motors.setSpeeds(200, -200);
      calibration();
    delay(8);
  }
  motors.setSpeeds(0,0);
  Serial.println("Calibration result:");
  for(int i = 0; i<2; i++)
  {
    for(int j = 0; j<8; j++)
    {
      setCalData(0x9,j+1,_CAL_MAX_[j],_CAL_MIN_[j]);
      if(i == 0)
      {
      Serial.print("j = ");Serial.print(j);Serial.print(" :");Serial.print(_CAL_MAX_[j]);Serial.print("  :");
      Serial.print(_CAL_MIN_[j]);Serial.println();
      }
    }
}
  }
  else
  {
    for(int i = 0; i<8; i++)
    {
      getCalData(0x09,i+1,&_CAL_MAX_[i],&_CAL_MIN_[i]);
    }
  }
 toneMelody();
 button.waitForButton();
 toneMelody();

  StartProgram(&ProgramSelected);

}

void loop()
{
  solveMaze();while (0 == 0) {
    button.waitForButton(); goToFinishLine();  toneMelody();}

}