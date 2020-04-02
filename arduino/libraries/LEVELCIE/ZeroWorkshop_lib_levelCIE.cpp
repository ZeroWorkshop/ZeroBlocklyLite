#include "ZeroWorkshop_lib_levelCIE.h"

#include "ZeroWorkshop_Macro_Definitions.h"

#include <Arduino.h>
#include <Servo.h>
#include <EEPROM.h>
#include <Adafruit_NeoPixel.h>
#include <string.h>

#define IR_REMOTE_ENABLE 1


Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

Adafruit_NeoPixel radarStrip = Adafruit_NeoPixel(16, ZW_B4, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel singleLED = Adafruit_NeoPixel(2, ZW_B4, NEO_GRB + NEO_KHZ800);


Adafruit_NeoPixel lampLED = Adafruit_NeoPixel(2, ZW_B3, NEO_GRB + NEO_KHZ800);

static void (*reset_this_CPU)(void) = 0x0000; // ***婵瀀垼倀涚瀀宕倀礊退涙怀瀚倀柣倀堢怀U退佸怀鍨倀慨退夊怀閻怀厧瀀伴怀銉墯退氾怀

struct ProgNumInEPROM {
  int lastProgSelected;
};
int followFlag = 1;
int buffer_index = 0;
int a = 999;
bool GrabActionCompleted = false;
bool PutActionCompleted = false;

long startTimeLeft = 0;
long startTimeRight = 0;
bool leftLEDLastState = LOW;
bool rightLEDLastState = LOW;

int isFollowFlag = 0;
long scoreTime = 0;

long mouthTime = 0;

int fanHeadMove_direction = 1;

int radar_dir = 1;

long startTimeKnock = 0;
bool hammerState = LOW;

long startTimeAttacked = 0;

int lastAttackedSensorState = HIGH;
int AttackedSensorState = HIGH;

int flash_times = 0;
bool LEDFlashState = false;

#define NumberOfProgram 11   //define the number of programs that stored in the CPU

int NOTE[] = {
  c5, c4, d4, e4, f4, g4, a4, b4, c5, d5, e5, f5
};


int TuningStatus = 0;
float LoaderPosition[] = {0, 53, 72, 97, 121, 146, 168};

struct ServoAngles {
  float positionValue[7];
};



#define buttonL1 (0x4 & ControlButton_Read[3])
#define buttonL2 (0x1 & ControlButton_Read[3])
#define buttonR1 (0x8 & ControlButton_Read[3])
#define buttonR2 (0x2 & ControlButton_Read[3])
#define Select (0x1 & ControlButton_Read[2])


// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {8, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4};

int ButtonState;                    // variable to store button state

int lastButtonState;                // variable to store last button state

//int ProgramSelector;

bool KeepOnReadButton;

bool ReadButtonState;

long ButtonInterval = 2000;

long startTime ;                    // start time for stop watch

long elapsedTime ;                  // elapsed time for stop watch
void StartProgram(int *ProgramSelector)
{
  ProgNumInEPROM ProgToBeSelected;
  ProgNumInEPROM lastRunProg;

  int eepromAddr = eeAddr_LEVEL1_DEFAULT_PROG;

  EEPROM.get(eepromAddr, lastRunProg);
  if (lastRunProg.lastProgSelected == 0) {
    ProgToBeSelected.lastProgSelected = 1;
    EEPROM.put(eepromAddr, ProgToBeSelected);
  }


  Serial.begin(115200);

  pinMode(BuzzerPin, OUTPUT);
  pinMode(START_BUTTON, INPUT);
  digitalWrite(START_BUTTON, HIGH);


  int bullet_left = bulletNumber;
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
      ButtonState = digitalRead(START_BUTTON);

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
			Serial.println(a);
      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      noteDuration = 1000 / noteDurations[(*ProgramSelector)];
      #if IR_REMOTE_ENABLE
       int xx;
      #else
			#endif
      // the note's duration + 30% seems to work well:
      pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      #if IR_REMOTE_ENABLE
      #else
  		#endif
      //      int eepromAddr = eeAddr_LEVEL1_DEFAULT_PROG;
      //      EEPROM.get(eepromAddr, lastRunProg);
      //      if (lastRunProg.lastProgSelected == 0) {
      //        ProgToBeSelected.lastProgSelected = 1;
      //        EEPROM.put(eepromAddr, ProgToBeSelected);
      //      }

      //      ProgToBeSelected.lastProgSelected = (*ProgramSelector);
      //      Serial.print("###########Program To be saved in EEPROM = ");
      //      Serial.println((*ProgramSelector));
      //      if (ProgToBeSelected.lastProgSelected != 0) {
      //
      //        Serial.print("Program To be saved in EEPROM = ");
      //        Serial.println(ProgToBeSelected.lastProgSelected);
      //
      //        EEPROM.put(eepromAddr, ProgToBeSelected);
      //      }
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

  playNoteShort(e7, sixteenthNote * 0.25, meters_x1);
  playNoteShort(g7, sixteenthNote * 0.25, meters_x1);
  playNoteShort(f7, sixteenthNote * 0.25, meters_x1);
  playNoteShort(g7, sixteenthNote * 0.25, meters_x1);
  delay(100);

  playNoteShort(e7, sixteenthNote * 0.25, meters_x1);
  playNoteShort(g7, sixteenthNote * 0.25, meters_x1);
  playNoteShort(f7, sixteenthNote * 0.25, meters_x1);
  playNoteShort(g7, sixteenthNote * 0.25, meters_x1);
//  delay(100);
//
//  playNoteShort(e7, sixteenthNote * 0.25, meters_x1);
//  playNoteShort(g7, sixteenthNote * 0.25, meters_x1);
//  playNoteShort(f7, sixteenthNote * 0.25, meters_x1);
//  playNoteShort(g7, sixteenthNote * 0.25, meters_x1);
}
  


void MotorControl(int MotorNumber, int RunningStatus) {
  switch (MotorNumber) {
  case 1:
    if (RunningStatus == FORWARD) {
      digitalWrite(MOTOR1P, HIGH);
      digitalWrite(MOTOR1M, LOW);
    }
    else if (RunningStatus == BACKWARD) {
      digitalWrite(MOTOR1P, LOW);
      digitalWrite(MOTOR1M, HIGH);
    }
    else if (RunningStatus == STOP) {
      digitalWrite(MOTOR1P, LOW);
      digitalWrite(MOTOR1M, LOW);
    }
    break;
  case 2:
    if (RunningStatus == FORWARD) {
      digitalWrite(MOTOR2P, HIGH);
      digitalWrite(MOTOR2M, LOW);
    }
    else if (RunningStatus == BACKWARD) {
      digitalWrite(MOTOR2P, LOW);
      digitalWrite(MOTOR2M, HIGH);
    }
    else if (RunningStatus == STOP) {
      digitalWrite(MOTOR2P, LOW);
      digitalWrite(MOTOR2M, LOW);
    }
    break;
  case 3:
    if (RunningStatus == FORWARD) {
      digitalWrite(MOTOR3P, HIGH);
      digitalWrite(MOTOR3M, LOW);
    }
    else if (RunningStatus == BACKWARD) {
      digitalWrite(MOTOR3P, LOW);
      digitalWrite(MOTOR3M, HIGH);
    }
    else if (RunningStatus == STOP) {
      digitalWrite(MOTOR3P, LOW);
      digitalWrite(MOTOR3M, LOW);
    }
    break;
  case 4:
    if (RunningStatus == FORWARD) {
      digitalWrite(MOTOR4P, HIGH);
      digitalWrite(MOTOR4M, LOW);
    }
    else if (RunningStatus == BACKWARD) {
      digitalWrite(MOTOR4P, LOW);
      digitalWrite(MOTOR4M, HIGH);
    }
    else if (RunningStatus == STOP) {
      digitalWrite(MOTOR4P, LOW);
      digitalWrite(MOTOR4M, LOW);
    }
    break;
  default:
    break;
  }
}

void servopulse(int servopin, int angle)//闂䀀法退愰倀濠怀箯退戣倀鏅怀柡退樺栫氳绋倀敓怀嬫瀀閻怀憡退怀椋倀厴退佹怀寮妶退楊䀀闂䀀法退曞΀鍕礄倀犲鏅怀柡退樺栫氾怀
{

  int pulsewidth = (angle * 11) + 500; //闂䀀法退愰倀濠怀箯退戣倀鏅怀悷倀愬瀀椤怀劙退忛怀顖怀ギ退佽怀鍠怀弸怀氬瀀閾怀倽瀀�500-2480退佽怀鍠怀弸怀氬瀀閻怀姤退搁怀鍌怀�怀�怀綊退ㄩ怀鍛倀伄退瑰倀鍢怀敓退ゆ倀

  digitalWrite(servopin, HIGH);   //闂䀀法退愰倀濠怀箯退戣倀鏅怀柡退樺栫氬瀀鏌　悢退婄䀀闁倀兘退辩瀀鍓р嫚怀楋怀閺䀀捇退倀鍐 伄退归鍏怀弫退诲怀閵倀棗退堕怀璺　櫐退凤怀

  delayMicroseconds(pulsewidth);  //闂䀀法退愰倀濠怀箯退垮顦р梺瀀ㄥ怀閺倀退忛怀鑺　櫢退哄倀鍊怀�怀綊倀愭瀀鍛倀櫢退哄倀鍊怀�怀懓退ラ锟䀀弫退诲怀閵倀棗退堕怀璺　枑退嬪骞倀敓退�

  digitalWrite(servopin, LOW);    //退佽怀鍠怀弸怀氬瀀閻怀姤退搁怀鍌怀�怀�怀綊退ㄩ怀鍛倀伄退圭倀鏀耀粔退ф倀濮怀拷退佹怀鎮埄退╃䀀闁倀退橀倀鎾耀棘退堝怀顏倀梺瀀ㄥ怀閹倀拷

  delayMicroseconds(20000 - pulsewidth);

}

void pull() {
  digitalWrite(MOTOR1P, HIGH);
  digitalWrite(MOTOR1M, LOW);
  delay(10);
  digitalWrite(MOTOR1P, LOW);

}

void pull2() {
  digitalWrite(MOTOR1P, LOW);
  digitalWrite(MOTOR1M, HIGH);
  delay(10);
  digitalWrite(MOTOR1M, LOW);
}

void pull_another() {
  digitalWrite(MOTOR2P, HIGH);
  digitalWrite(MOTOR2M, LOW);
  delay(10);
  digitalWrite(MOTOR2P, LOW);
}

void pull_another2() {
  digitalWrite(MOTOR2P, LOW);
  digitalWrite(MOTOR2M, HIGH);
  delay(10);
  digitalWrite(MOTOR2M, LOW);
}

void Left_Motor(long direction) {

  if (direction == FORWARD) {

    digitalWrite(MOTOR1P, HIGH);

    digitalWrite(MOTOR1M, LOW);

  } else if (direction == BACKWARD) {

    digitalWrite(MOTOR1P, LOW);

    digitalWrite(MOTOR1M, HIGH);

  } else {

    digitalWrite(MOTOR1P, LOW);

    digitalWrite(MOTOR1M, LOW);

  }

}



void Right_Motor(long direction) {

  if (direction == FORWARD) {

    digitalWrite(MOTOR2P, HIGH);

    digitalWrite(MOTOR2M, LOW);

  } else if (direction == BACKWARD) {

    digitalWrite(MOTOR2P, LOW);

    digitalWrite(MOTOR2M, HIGH);

  } else {

    digitalWrite(MOTOR2P, LOW);

    digitalWrite(MOTOR2M, LOW);



  }

}

#if 1
void goForward() {

  Left_Motor(FORWARD);

  Right_Motor(FORWARD);

}



void goReverse() {

  Left_Motor(BACKWARD);

  Right_Motor(BACKWARD);

}


void goLeftTurn() {

  Left_Motor(BACKWARD);

  Right_Motor(FORWARD);

}

void goRightTurn() {

  Left_Motor(FORWARD);

  Right_Motor(BACKWARD);

}

void goBrake() {
	
	if(followFlag == 2 || isFollowFlag == 1){
		
	}else{
		Left_Motor(STOP);
 	 Right_Motor(STOP);
	}
  

}
#endif

#if 0
void setRightSpeed(int speed)
{
  boolean reverse = 0;
  if (speed < 0)
  {
    speed = -speed; // make speed a positive quantity
    reverse = 1;    // preserve the direction
  }
  if (speed > 255)  // Max
  {
    speed = 255;
  }

  //analogWrite(ENA, speed); // default to using analogWrite, mapping 400 to 255.
  //digitalWrite(ENA,HIGH);
  if (reverse)
  {
    Palatis::SoftPWM.set(MOTOR1P, speed);
    digitalWrite(MOTOR1M, LOW);
  }
  else
  {
    digitalWrite(MOTOR1P, LOW);
    Palatis::SoftPWM.set(MOTOR1M, speed);
  }

}



void setLeftSpeed(int speed)
{
  boolean reverse = 0;
  if (speed < 0)
  {
    speed = -speed; // make speed a positive quantity
    reverse = 1;    // preserve the direction
  }
  if (speed > 255)  // Max
  {
    speed = 255;
  }
  //analogWrite(ENB, speed * 51 / 80); // default to using analogWrite, mapping 400 to 255.
  //digitalWrite(ENB,HIGH);
  if (reverse)
  {
    //digitalWrite(MOTOR2P, HIGH);
    Palatis::SoftPWM.set(MOTOR2P, speed);
    digitalWrite(MOTOR2M, LOW);
  }
  else
  {
    digitalWrite(MOTOR2P, LOW);
    Palatis::SoftPWM.set(MOTOR2M, speed);
    //digitalWrite(MOTOR2M, HIGH);
  }

}

void goForward () {
  setLeftSpeed(350);
  setRightSpeed(350);
}

void goReverse() {
  setLeftSpeed(-350);
  setRightSpeed(-350);
}

void goLeftTurn() {
  setLeftSpeed(-350);
  setRightSpeed(350);
}

void goRightTurn() {
  setLeftSpeed(350);
  setRightSpeed(-350);
}

void goBrake() {
  setLeftSpeed(0);
  setRightSpeed(0);
}
#endif
/*
  void leftLightFlash() {
  digitalWrite(LED_left, HIGH);
  delay(50);
  digitalWrite(LED_left, LOW);
  }
*/
void leftLightFlash() {
  if ( (millis() - startTimeLeft) > 50 ) {

    if (leftLEDLastState == LOW)	{
      digitalWrite(LED_left, HIGH);
      leftLEDLastState = HIGH;
    }
    else if (leftLEDLastState == HIGH)	{
      digitalWrite(LED_left, LOW);
      leftLEDLastState = LOW;
    }
    startTimeLeft = millis();
  }
}

void leftLightOn() {
  digitalWrite(LED_left, HIGH);
}

void leftLightOff() {
  digitalWrite(LED_left, LOW);
}
/*
  void rightLightFlash() {
  digitalWrite(LED_right, HIGH);
  delay(50);
  digitalWrite(LED_right, LOW);
  }
*/
void rightLightFlash() {
  if ( (millis() - startTimeRight) > 50 ) {

    if (rightLEDLastState == LOW)	{
      digitalWrite(LED_right, HIGH);
      rightLEDLastState = HIGH;
    }
    else if (rightLEDLastState == HIGH)	{
      digitalWrite(LED_right, LOW);
      rightLEDLastState = LOW;
    }
    startTimeRight = millis();
  }
}

void rightLightOn() {
  digitalWrite(LED_right, HIGH);
}

void rightLightOff() {
  digitalWrite(LED_right, LOW);
}

void rearLightFlash() {
  digitalWrite(LED_A3, HIGH);
  digitalWrite(LED_A2, HIGH);
  delay(50);
  digitalWrite(LED_A3, LOW);
  digitalWrite(LED_A2, LOW);
}

void rearLightOn() {
  digitalWrite(LED_left, HIGH);
  digitalWrite(LED_right, HIGH);
}

void rearLightOff() {
  digitalWrite(LED_left, LOW);
  digitalWrite(LED_right, LOW);
}

//void onRedLED() {
//  digitalWrite(LED_9, HIGH);

//}

bool PS2_RF_Button(uint16_t ButtonPressed)
{
  byte PS2_RF_buffer[6];
  bool PAD_LeftKey;

  uint8_t UpperByte = ButtonPressed >> 8;
  uint8_t LowerByte = ButtonPressed & 0xff;

  if (Serial.available() > 0) {
    Serial.readBytes(PS2_RF_buffer, 6);  //the decoded data is a 6 byte data


    Serial.print("Expected 16bit value is: 0x");
    Serial.println(ButtonPressed, HEX);

    Serial.print("Left Pad Recieved is:");
    Serial.println(PS2_RF_buffer[2], HEX);
    Serial.print("Right Pad Recieved is:");
    Serial.println(PS2_RF_buffer[3], HEX);

    Serial.print("Left Pad Expected is:");
    Serial.println(UpperByte, HEX);
    Serial.print("Right Pad Expected is:");
    Serial.println(LowerByte, HEX);
    if (PS2_RF_buffer[0] != 0xAA || PS2_RF_buffer[1] != 0x55) {
      return false;
    }




    if ((PS2_RF_buffer[2] & UpperByte) != 0) {
      Serial.println("Pad left button matched!");
      return true;
    }
    else {
      Serial.println("No Pad left button matched!");
      return false;
    }


    if ((PS2_RF_buffer[3] & LowerByte)) {
      Serial.println("Pad right button matched!");
      return true;
    }
    else {
      Serial.println("No Pad right button matched!");
      return false;
    }



  }
  else return false;
}

bool PS2_RF_ReadButton(int *Button_Buffer)
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
      Serial.print("Byte ");
      Serial.print(j);
      Serial.print(":   ");
      Serial.println(temp, HEX);
      if (temp == 0xAA) buffer_index = 0;

      Button_Buffer[buffer_index] = temp;
      //#if DEBUG
      Serial.print("Byte[");
      Serial.print(buffer_index);
      Serial.print("]: 0x");
      Serial.println(Button_Buffer[buffer_index], HEX);
      //#endif
      buffer_index++;


    }
  }
}

int Rx_Buffer[6];
int temp[6];

/*
 For some unknown reason, the controller data into the serial port sometimes give the wrong sequence. 
 The right sequence is AA 55 RR SS TT UU. A right data is a 6-byte with AA 55 as the first two bytes. 
 However sometimes the byte sequence is less than 6 byte which is a wrong number. It maybe caused by some missing capture. 
 This function is to pick up the right 6-byte sequence as the correct controller data.
 SerialEvent occurs whenever a new data comes in the hardware serial RX. 
 Normally several consective 6-byte data are recieved. But sometimes there are some missing bytes. 
 In this case, we collect the latest valid 6-byte data as the valid controller data.
 */
void serialEvent() {
  if (Serial.available() < 6) return;  //If the total bytes in buffer is less than 6, the data is invalid. Stop the routine without get the data.
  #if	DEBUG
  Serial.print("Bytes in buffer is : ");
  Serial.println(Serial.available());
  #endif
  if (Serial.available() % 6) Serial.println("ERROR!!Bytes in UART buffer is not an valid PS2 control data. Data will be discarsed");



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


void playNote(int Note, int Meter, int Length) {
#if IR_REMOTE_ENABLE
#else
#endif
  //  delay(Meter * 1.3 * Length);
  long duration_time = millis();
  for (int i = 0; i < Meter * 1.3 * Length * 200; i++) {
    //    Serial.println(i);
    if (millis() - duration_time > Meter * 1.3 * Length) break;
    //digitalRead(ZW_A1);
  }
}

void playNoteShort(int Note, int Meter, int Length) {
#if IR_REMOTE_ENABLE
#else
//delay(Meter * 1.3 * Length);
#endif
long duration_time = millis();
for (int i = 0; i < Meter * 1.3 * Length * 200; i++) {
    //    Serial.println(i);
    if (millis() - duration_time > Meter * 1.0 * Length) break;
    //digitalRead(ZW_A1);
}
}

void playSong(int songSelected) {
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
void PanMoveClockwise(Servo myservo, double *Pos)
{
  double temp_pos = *Pos;
  temp_pos += 2;     //1 step is 2 degrees
  if (temp_pos >= 180) temp_pos = 180;

  *Pos = temp_pos;

  myservo.write(temp_pos);
  //    delay(10);
}


void PanMoveCounterclockwise(Servo myservo, double *Pos)
{
  double temp_pos = *Pos;
  temp_pos -= 2;     //1 step is -2 degrees
  if (temp_pos <= 0) temp_pos = 0;

  *Pos = temp_pos;

  myservo.write(temp_pos);
  //    delay(10);
}

void TiltMoveDown(Servo myservo, double *Pos)
{
  double temp_pos = *Pos;
  temp_pos -= 2;     //1 step is -2 degrees
  if (temp_pos <= 0) temp_pos = 0;

  *Pos = temp_pos;

  myservo.write(temp_pos);
  //    delay(10);
}

void TiltMoveUp(Servo myservo, double *Pos)
{
  double temp_pos = *Pos;
  temp_pos += 2;     //1 step is 2 degrees
  if (temp_pos >= 180) temp_pos = 180;

  *Pos = temp_pos;

  myservo.write(temp_pos);
  //    delay(10);
}

void ServoSteeringRight(Servo steer_servo1, Servo steer_servo2, double *Pos)
{
  double temp_pos = *Pos;
  temp_pos += 10;     //1 step is 10 degrees
  if (temp_pos >= 160) temp_pos = 160;

  *Pos = temp_pos;

  steer_servo1.write(temp_pos);
  steer_servo2.write(temp_pos);
  //    delay(10);
}


void ServoSteeringLeft(Servo steer_servo1, Servo steer_servo2, double *Pos)
{
  double temp_pos = *Pos;
  temp_pos -= 10;     //1 step is -10 degrees
  if (temp_pos <= 20) temp_pos = 20;

  *Pos = temp_pos;


  steer_servo1.write(temp_pos);
  steer_servo2.write(temp_pos);
  //    delay(10);
}

void ServoSteeringCenter(Servo steer_servo1, Servo steer_servo2, double *Pos) {
  *Pos = initPos;
  steer_servo1.write(initPos);
  steer_servo2.write(initPos);
}

void ActionGrab(Servo arm_servo, Servo hand_servo) {
  double arm_pos;
  double hand_pos;



  arm_pos = ARM_STOP_UP;
  hand_pos = HAND_FULL_OPEN;

  if (GrabActionCompleted == false) {
    for (int arm_i = 0; arm_i < 60; arm_i++) {
      ArmControlDown(arm_servo, &arm_pos);
    }
    for (int hand_step = 0; hand_step < 50; hand_step++) {
      HandControlClose(hand_servo, &hand_pos);
    }
    for (int arm_j = 0; arm_j < 60; arm_j++)
    {
      ArmControlUp(arm_servo, &arm_pos);
    }

    GrabActionCompleted = true;
    PutActionCompleted = false;
  }
}

void ActionGrab_Liang(Servo arm_servo, Servo hand_servo) {
  double arm_pos;
  double hand_pos;



  arm_pos = 170;
  hand_pos = HAND_FULL_OPEN;

  if (GrabActionCompleted == false) {
    for (int arm_i = 0; arm_i < 60; arm_i++) {
      ArmControlDown_Liang(arm_servo, &arm_pos);
    }
    for (int hand_step = 0; hand_step < 50; hand_step++) {
      HandControlClose(hand_servo, &hand_pos);
    }
    for (int arm_j = 0; arm_j < 60; arm_j++)
    {
      ArmControlUp_Liang(arm_servo, &arm_pos);
    }

    GrabActionCompleted = true;
    PutActionCompleted = false;
  }
}
void ActionPut(Servo arm_servo, Servo hand_servo) {
  double arm_pos;
  double hand_pos;

  arm_pos = ARM_STOP_UP;
  hand_pos = HAND_FULL_CLOSE;

  if (PutActionCompleted == false) {
    for (int arm_i = 0; arm_i < 60; arm_i++) {
      ArmControlDown(arm_servo, &arm_pos);
    }
    for (int hand_step = 0; hand_step < 50; hand_step++) {
      HandControlOpen(hand_servo, &hand_pos);
    }
    for (int arm_j = 0; arm_j < 60; arm_j++) {
      ArmControlUp(arm_servo, &arm_pos);
    }

    PutActionCompleted = true;
    GrabActionCompleted = false;
  }
}

void ActionPut_Liang(Servo arm_servo, Servo hand_servo) {
  double arm_pos;
  double hand_pos;

  arm_pos = 170;
  hand_pos = HAND_FULL_CLOSE;

  if (PutActionCompleted == false) {
    for (int arm_i = 0; arm_i < 60; arm_i++) {
      ArmControlDown_Liang(arm_servo, &arm_pos);
    }
    for (int hand_step = 0; hand_step < 50; hand_step++) {
      HandControlOpen(hand_servo, &hand_pos);
    }
    for (int arm_j = 0; arm_j < 60; arm_j++) {
      ArmControlUp_Liang(arm_servo, &arm_pos);
    }

    PutActionCompleted = true;
    GrabActionCompleted = false;
  }
}
//TAIL_STOP_UP 90
//TAIL_STOP_DOWN 0
void TailControlUp(Servo tail_servo, double *tail_position) {//0
	
	//90

  if ((*tail_position) >  TAIL_STOP_DOWN) *tail_position =  TAIL_STOP_DOWN;
  tail_servo.write(*tail_position);
  delay(10);
}
int FFlag  =  0;
long isF = 0;
void HammerKnock( Servo hammer_servo ) {//15
  if(millis() - isF >500) {
    if(FFlag == 0) {
      hammer_servo.write(175);
      FFlag = 1 ;
    } else {
      hammer_servo.write(0);
      FFlag = 0 ;
    }
    isF = millis();
  }



}
void TailControlDown(Servo tail_servo, double *tail_position) {
	if (*tail_position < TAIL_STOP_UP) *tail_position = TAIL_STOP_UP;

  tail_servo.write(*tail_position);

  delay(10);
}

void ArmControlUp(Servo arm_servo, double *arm_position) {

  *arm_position -= 2;

  if (*arm_position < ARM_STOP_UP) *arm_position = ARM_STOP_UP;
  arm_servo.write(*arm_position);
  delay(10);
}

void ArmControlUp_Liang(Servo arm_servo, double *arm_position) {

  *arm_position += 2;

  if (*arm_position > 170) *arm_position = 170;
  arm_servo.write(*arm_position);
  delay(10);
}

void ArmControlDown(Servo arm_servo, double *arm_position) {
  *arm_position += 2;

  if ((*arm_position) > ARM_STOP_DOWN) *arm_position = ARM_STOP_DOWN;
  arm_servo.write(*arm_position);
  delay(10);

}

void ArmControlDown_Liang(Servo arm_servo, double *arm_position) {
  *arm_position -= 2;

  if ((*arm_position) < 110) *arm_position = 110;
  arm_servo.write(*arm_position);
  delay(10);

}
void HandControlClose(Servo hand_servo, double *hand_angle) {

  *hand_angle += 2;

  if (*hand_angle > HAND_FULL_CLOSE) *hand_angle = HAND_FULL_CLOSE;


  hand_servo.write(*hand_angle);
  delay(10);
}

void HandControlOpen(Servo hand_servo, double *hand_angle) {

  *hand_angle -= 2;

  if (*hand_angle < HAND_FULL_OPEN) *hand_angle = HAND_FULL_OPEN;

  hand_servo.write(*hand_angle);
  delay(10);
}

void LeftWheelForward() {
  digitalWrite(MOTOR1P, HIGH);
  digitalWrite(MOTOR1M, LOW);
}

void LeftWheelBackward() {
  digitalWrite(MOTOR1P, LOW);
  digitalWrite(MOTOR1M, HIGH);
}

void RightWheelForward() {
  digitalWrite(MOTOR2P, HIGH);
  digitalWrite(MOTOR2M, LOW);
}

void RightWheelBackward() {
  digitalWrite(MOTOR2P, LOW);
  digitalWrite(MOTOR2M, HIGH);
}

#ifdef LEVEL1
void LeftWheelForward_SpeedControl(int SpeedSet) {
  digitalWrite(MOTOR1P, HIGH);
  //digitalWrite(MOTOR1M, LOW);
  int PWMvalue = 255 - SpeedSet;
  analogWrite(MOTOR1M, PWMvalue);   //Since the PWM is on negative pin, so the opposite value should be calculated
}

void LeftWheelBackward_SpeedControl(int SpeedSet) {
  digitalWrite(MOTOR1P, LOW);
  //digitalWrite(MOTOR1M, HIGH);
  analogWrite(MOTOR1M, SpeedSet);
}

void RightWheelForward_SpeedControl(int SpeedSet) {
  digitalWrite(MOTOR2P, HIGH);
  //digitalWrite(MOTOR2M, LOW);
  int PWMvalue = 255 - SpeedSet;
  analogWrite(MOTOR2M, PWMvalue);   //Since the PWM is on negative pin, so the opposite value should be calculated
}

void RightWheelBackward_SpeedControl(int SpeedSet) {
  digitalWrite(MOTOR2P, LOW);
  //digitalWrite(MOTOR2M, HIGH);
  analogWrite(MOTOR2M, SpeedSet);
}
#endif

#ifdef LEVEL1_REVB
void LeftWheelForward_SpeedControl(int SpeedSet) {
  analogWrite(MOTOR1P, HIGH);
  digitalWrite(MOTOR1M, LOW);
  //int PWMvalue = 255 - SpeedSet;
  //analogWrite(MOTOR1M, PWMvalue);   //Since the PWM is on negative pin, so the opposite value should be calculated
}

void LeftWheelBackward_SpeedControl(int SpeedSet) {
  int PWMvalue = 255 - SpeedSet;
  analogWrite(MOTOR1P, PWMvalue);
  digitalWrite(MOTOR1M, HIGH);
  //analogWrite(MOTOR1M, SpeedSet);
}

void RightWheelForward_SpeedControl(int SpeedSet) {
  analogWrite(MOTOR2P, HIGH);
  digitalWrite(MOTOR2M, LOW);
  //int PWMvalue = 255 - SpeedSet;
  //analogWrite(MOTOR2M, PWMvalue);   //Since the PWM is on negative pin, so the opposite value should be calculated
}

void RightWheelBackward_SpeedControl(int SpeedSet) {
  int PWMvalue = 255 - SpeedSet;
  analogWrite(MOTOR2P, PWMvalue);
  digitalWrite(MOTOR2M, HIGH);
  //analogWrite(MOTOR2M, SpeedSet);
}
#endif

void LeftWheelClockwise() {         //left wheel runs clockwise means left wheel run backward
  digitalWrite(MOTOR1P, LOW);
  digitalWrite(MOTOR1M, HIGH);
}

void LeftWheelCounterClockwise() {  //left wheel runs counterclockwise means left wheel run forward
  digitalWrite(MOTOR1P, HIGH);
  digitalWrite(MOTOR1M, LOW);
}

void RightWheelClockwise() {        //right wheel runs clockwise means right wheel run forward
  digitalWrite(MOTOR2P, HIGH);
  digitalWrite(MOTOR2M, LOW);
}

void RightWheelCounterClockwise() {  //right wheel runs counterclockwise means right wheel run backward
  digitalWrite(MOTOR2P, LOW);
  digitalWrite(MOTOR2M, HIGH);
}

void LeftWheelStop() {
  digitalWrite(MOTOR1P, LOW);
  digitalWrite(MOTOR1M, LOW);
}

void RightWheelStop() {
  digitalWrite(MOTOR2P, LOW);
  digitalWrite(MOTOR2M, LOW);
}


//get servo angle data from eeprom which is stored previously
void getServoAngleEEPROM(int *standbyPos) {
  ServoAngles RubberbandLoaderAngle;

  int eepromAddr = eeAddr_RUBERBAND_LOADER;

  EEPROM.get(eepromAddr, RubberbandLoaderAngle);

  for (int i = 0; i < 7; i++) {
    LoaderPosition[i] = RubberbandLoaderAngle.positionValue[i];
    Serial.print("Angle[");
    Serial.print(i);
    Serial.print("]=");
    Serial.println(LoaderPosition[i]);
  }

  (*standbyPos) = LoaderPosition[bulletNumber];
}


void reloadAllBullets(Servo bulletLoader_servo) {
  int servo_pos;

  servo_pos = LoaderPosition[6];

  bulletLoader_servo.write(servo_pos);

}

void loadBullet(Servo bulletLoader_servo, int *bullet_left) {
  float servo_pos;
  float servo_angle;


  servo_pos = LoaderPosition[*bullet_left];

  Serial.print("Loader angle is : ");
  Serial.println(servo_pos);

  bulletLoader_servo.write(servo_pos);
  delay(500);
}

void fireBullet(Servo bulletTrigger_servo, Servo bulletLoader_servo, int *bullet_left) {
  bulletTrigger_servo.write(0);
  delay(800);
  bulletTrigger_servo.write(140);


  (*bullet_left)--;                           //Bullets left is decreased after one is shot.


  if (*bullet_left == 0) {                   //After all bullets are fired(no bullet left), restore the loading servo to initial position.
    reloadAllBullets(bulletLoader_servo);
    *bullet_left = 6;
  }
  while (Serial.available() > 0) {
    int getData = Serial.read();
    //Serial.println("i am here !!!!!!!!!!!!!!!");
  }
  delay(500);
}

void RubberbandFireSingle(Servo bulletLoader_servo, Servo bulletTrigger_servo, int *bullet_left) {


  loadBullet(bulletLoader_servo, bullet_left);

  fireBullet(bulletTrigger_servo, bulletLoader_servo, bullet_left);     //Bullet left number will be decreased after one bullet is fired. The number is changed in fireBullet() function



}

void RubberbandFireAll(Servo bulletLoader_servo, Servo bulletTrigger_servo, int *bullet_left) {
  //Serial.flush();
  int loop_times = *bullet_left;
  Serial.println("Firing!!!!");
  for (loop_times; loop_times > 0; loop_times--) {
    loadBullet(bulletLoader_servo, bullet_left);

    fireBullet(bulletTrigger_servo, bulletLoader_servo, bullet_left);    //Bullet left number will be decreased after one bullet is fired. The number is changed in fireBullet() function
    //delay(500);
  }
  //Serial.begin(115200);
  while (Serial.available() > 0) {
    int getData = Serial.read();
    Serial.println("i am here !!!!!!!!!!!!!!!");
  }
}


void TuningLoader(Servo Loader_servo, Servo Trigger_servo, int *bullet_left) {

  double loaderPos = 90;
  int noteDuration = 1000 / noteDurations[0];
  int pauseBetweenNotes = noteDuration * 1.30;

  int      ControlButton_Read[6];

  ServoAngles RubberbandLoaderAngles;

  PS2_RF_ReadButton(ControlButton_Read);


  //if (buttonL1 && buttonL2 && buttonR1 && buttonR2 && TuningStatus == 0) {
  TuningStatus = 1;


  while (TuningStatus == 1 && *bullet_left > 0) {
    Serial.print(*bullet_left);
    Serial.println(" is left.");
    PS2_RF_ReadButton(ControlButton_Read);

    if (buttonL1) {
      loaderPos -= 0.5;
      if (loaderPos < 0) loaderPos = 0;
      Loader_servo.write(loaderPos);
      Serial.println("Tuning loader positively!");
    }
    else if (buttonR1) {
      loaderPos += 0.5;
      if (loaderPos > 180) loaderPos = 180;
      Loader_servo.write(loaderPos);
      Serial.println("Tuning loader negatively!");
    }

    if (Select) {
      Serial.print("Bullet No.:");
      Serial.print(*bullet_left);
      Serial.println(" is tuned.");
      LoaderPosition[*bullet_left] = loaderPos;
      RubberbandLoaderAngles.positionValue[*bullet_left]  = loaderPos;

      for (int i = 0; i < *bullet_left; i++) {
        noteDuration = 1000 / noteDurations[*bullet_left];
        #if IR_REMOTE_ENABLE
        #else
        #endif
        pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
        #if IR_REMOTE_ENABLE
        #else
        #endif
      }

      (*bullet_left)--;
      Serial.print("Bullet No.At this moment is :");
      Serial.println(*bullet_left);
    }
  }

  int eepromAddr = eeAddr_RUBERBAND_LOADER;
  EEPROM.put(eepromAddr, RubberbandLoaderAngles);


  TuningStatus = 0;
  *bullet_left = 6;
  //Loader_servo.write(*bullet_left);
  //}

  playNote(e5, sixteenthNote, meters_x1);
  playNote(e5, sixteenthNote, meters_x1);
  playNote(e5, sixteenthNote, meters_x1);
}


void FanRunning(int SelectSpeed, bool fanIsRunning) {

  if (fanIsRunning) {
    if (SelectSpeed == spinFAST) {
      digitalWrite(MOTOR1P, HIGH);
      digitalWrite(MOTOR1M, LOW);
    }
    else if (SelectSpeed == spinMEDIUM) {
      digitalWrite(MOTOR1P, HIGH);
      analogWrite(MOTOR1M, 64);
    }
    else if (SelectSpeed == spinSLOW) {
      digitalWrite(MOTOR1P, HIGH);
      analogWrite(MOTOR1M, 128);
    }
  }
  else {
    digitalWrite(MOTOR1P, LOW);
    digitalWrite(MOTOR1M, LOW);
  }

}


void FanHeadMove(Servo fanHeadServo, bool allowFanHeadMoving, double *fanHeadPos) {


  if (allowFanHeadMoving) {
    if (fanHeadMove_direction == 1) {
      (*fanHeadPos) += 0.6;

      if ((*fanHeadPos) > 180) {
        (*fanHeadPos) = 180;
        fanHeadMove_direction = -1;
      }
      fanHeadServo.write((*fanHeadPos));
    }
    else if (fanHeadMove_direction == -1) {
      (*fanHeadPos) -= 0.6;

      if ((*fanHeadPos) < 0) {
        (*fanHeadPos) = 0;
        fanHeadMove_direction = 1;
      }
      fanHeadServo.write((*fanHeadPos));
    }
  }
}

void fanHeadPosition(Servo fanHeadZ_servo, int headPosition) {
  if (headPosition == UP) {
    fanHeadZ_servo.write(30);

  }
  else if (headPosition == CENTER) {
    fanHeadZ_servo.write(120);
  }
  else if (headPosition == DOWN) {
    fanHeadZ_servo.write(170);
  }
}


void loadBatteryBullet(Servo batterybulletLoader_servo, int *battery_left) {
  float servo_pos;
  float servo_angle;


  batterybulletLoader_servo.write(LOADING_POS);
  delay(500);
  batterybulletLoader_servo.write(STANDBY_POS);
}


void fireBatteryBullet(Servo batterybulletTrigger_servo, int *battery_left) {
  batterybulletTrigger_servo.write(FIRING_POS);
  delay(800);
  batterybulletTrigger_servo.write(WAITING_POS);


  (*battery_left)--;                           //Bullets left is decreased after one is shot.


  if (*battery_left == 0) {                   //After all bullets are fired(no bullet left), restore the loading servo to initial position.
    //reloadAllBullets(bulletLoader_servo);
    *battery_left = batteryNumber;
  }
  while (Serial.available() > 0) {
    int getData = Serial.read();
    //Serial.println("i am here !!!!!!!!!!!!!!!");
  }
  delay(500);
}

void BatteryFireAll(Servo batterybulletLoader_servo, Servo batterybulletTrigger_servo, int *battery_left) {
  //Serial.flush();
  int loop_times = *battery_left;
  Serial.println("Firing Battery!!!!");
  for (loop_times; loop_times > 0; loop_times--) {
    loadBatteryBullet(batterybulletLoader_servo, battery_left);

    fireBatteryBullet(batterybulletTrigger_servo, battery_left);    //Bullet left number will be decreased after one bullet is fired. The number is changed in fireBullet() function
    //delay(500);
  }
  //Serial.begin(115200);
  while (Serial.available() > 0) {
    int getData = Serial.read();
    Serial.println("i am here !!!!!!!!!!!!!!!");
  }
}

void BatteryFireSingle(Servo batterybulletLoader_servo, Servo batterybulletTrigger_servo, int *battery_left) {


  loadBatteryBullet(batterybulletLoader_servo, battery_left);

  fireBatteryBullet(batterybulletTrigger_servo, battery_left);    //Bullet left number will be decreased after one bullet is fired. The number is changed in fireBullet() function
}

void resetScoreboard() {
  digitalWrite(MOTOR1P, HIGH);
  analogWrite(MOTOR1M, 190);
  delay(1000);
  digitalWrite(MOTOR1P, LOW);
  digitalWrite(MOTOR1M, LOW);
}
void scoreboardChange(int speedSel) {
  int SpeedSet;
  double delay_T;

  if (speedSel == 1) {
    SpeedSet = 100;
    delay_T = 15;
  }
  else if (speedSel == 2) {
    SpeedSet = 200;
    delay_T = 9.5;
  }

  analogWrite(MOTOR1M, SpeedSet);
  digitalWrite(MOTOR1P, LOW);

  delay(delay_T);

  digitalWrite(MOTOR1M, LOW);
}

void checkBall(int selection, int SensorPin, int *Points) {


  if (isLow( SensorPin )) {
    if ( (millis() - scoreTime) > 500 ) {
      Serial.println("SCORED!!!!!");
      if (selection == 1) {
        (*Points) += 1;

        scoreboardChange(selection);
      }
      else if (selection == 2) {
        (*Points) += 2;

        scoreboardChange(selection);
      }
      scoreTime = millis();
    }

  }
}

void  backboard_noMove(double *backboard_pos, Servo backboard_servo) {
  (*backboard_pos) = backboard_initPos;

  backboard_servo.write((*backboard_pos));
}

int move_direction = 1;
long boardMoveTime = 0;

void  backboard_slowMove(double *backboard_pos, Servo backboard_servo) {
  double step_angle = 0.5;
  if ( (millis() - boardMoveTime) > 40 ) {
    if ((*backboard_pos) > backboard_stopPos) {
      (*backboard_pos) = backboard_stopPos;
      move_direction = -1;
    }
    else  if ((*backboard_pos) < backboard_startPos) {
      (*backboard_pos) = backboard_startPos;
      move_direction = 1;
    }

    (*backboard_pos) += move_direction * step_angle;

    backboard_servo.write((*backboard_pos));

    boardMoveTime = millis();
  }
}

void  backboard_fastMove(double *backboard_pos, Servo backboard_servo) {
  double step_angle = 1;
  if ( (millis() - boardMoveTime) > 20 ) {
    if ((*backboard_pos) > backboard_stopPos) {
      (*backboard_pos) = backboard_stopPos;
      move_direction = -1;
    }
    else  if ((*backboard_pos) < backboard_startPos) {
      (*backboard_pos) = backboard_startPos;
      move_direction = 1;
    }

    (*backboard_pos) += move_direction * step_angle;

    backboard_servo.write((*backboard_pos));

    boardMoveTime = millis();
  }
}
void backboardMove(int *points, Servo backboard_servo, double *backboard_pos, int backboard_nomove_sel, int backboard_slowmove_sel, int backboard_fastmove_sel) {
  int stage_still_limit;
  int stage_slow_limit;
  int stage_fast_limit;

  stage_still_limit = backboard_nomove_sel;
  stage_slow_limit  = backboard_slowmove_sel;
  stage_fast_limit  = backboard_fastmove_sel;

  if (backboard_nomove_sel < backboard_slowmove_sel && backboard_slowmove_sel < backboard_fastmove_sel) {
    stage_still_limit = backboard_nomove_sel;
    stage_slow_limit  = backboard_slowmove_sel;
    stage_fast_limit  = backboard_fastmove_sel;
  }
  else if (backboard_nomove_sel >= backboard_slowmove_sel) {
    stage_still_limit = backboard_nomove_sel;
    stage_slow_limit  = backboard_nomove_sel;
  }
  else if (backboard_slowmove_sel >= backboard_fastmove_sel) {
    stage_slow_limit = backboard_slowmove_sel;
    stage_fast_limit = backboard_slowmove_sel;
  }

  if ((*points) <= stage_still_limit) {
    backboard_noMove(backboard_pos, backboard_servo);
  }
  else if ((*points) > stage_still_limit && (*points) <= stage_slow_limit) {
    backboard_slowMove(backboard_pos, backboard_servo);
  }
  else if ((*points) > stage_slow_limit && (*points) <= stage_fast_limit) {
    backboard_fastMove(backboard_pos, backboard_servo);
  }

}
int agFlag = 0;
void fire (Servo fire_servo ,double *ang) {
  fire_servo.write(55);

  agFlag = 0;
}
int ag = 55;

void acc(Servo fire_servo ,double *ang) {
  if(agFlag == 0) {
    if(ag<140) {
      ag = ag+1;
      fire_servo.write(ag);
      
    } else{
    	agFlag = 1;
    }
  } else {

  }
}
void fired (Servo fire_servo ,double *ang) {
  if(agFlag == 1) {
      fire_servo.write(0);
      ag = 55;
      agFlag = 1;
  } else {

  }
}

void lampMoveL (Servo lamp_servo ,double *angL) {
  if(*angL<180) {
    *angL+=0.1;
    lamp_servo.write(*angL);
    Serial.print("angL = ");	
		Serial.println(*angL);
  }
}

void lampMoveR (Servo lamp_servo ,double *angL) {
  if(*angL>0) {
    *angL-=0.1;
    lamp_servo.write(*angL);
    Serial.print("angL = ");	
		Serial.println(*angL);
  }
}

void chassisMoveL (Servo chassis_servo ,double *ang) {
  if(*ang<180) {
    *ang+=0.1;
    chassis_servo.write(*ang);
    Serial.print("ang = ");	
		Serial.println(*ang);
  }
}

void chassisMoveR (Servo chassis_servo ,double *ang) {
  if(*ang>0) {
    *ang-=0.1;
    chassis_servo.write(*ang);
    Serial.print("ang = ");	
		Serial.println(*ang);
  }
}


double beginTime;
double endTime;
double holdTime;
boolean firstRun = true;
void radarStart(Servo radar_servo ,bool moveFlag ,double *ang) {
  if (firstRun) {
    beginTime = millis();
    firstRun = false;
  }
  else
    beginTime = endTime;

  endTime = millis();
  holdTime = endTime - beginTime;

//Serial.print("HoldTime = ");
//Serial.println(holdTime);

  if(moveFlag) {
    if(radar_dir == 1) {
      //delay(10);
      //(*ang) +=0.5;
      (*ang) += holdTime * 0.05;
      radar_servo.write((*ang));

      if((*ang) > 179) {
        radar_dir = -1;
      }
    }
    if(radar_dir == -1 ) {
      (*ang) += -holdTime * 0.05;
      radar_servo.write((*ang));
      if((*ang) < 1) {
        radar_dir = 1;
      }
    }
  }

}

long pixFlag = 0;
long timeLight = 0;
int fashFlag = 1;

long offPassFlag = 0;
void indicatorLightOff() {

  if(millis()-offPassFlag>200) {
    for(int i=0; i<16; i++) {
      radarStrip.setPixelColor(i,0);
    }
    radarStrip.show();
    offPassFlag = millis();
  }
}



#include <NewPing.h>

#define SONAR_NUM 4      // Number of sensors. 
#define MAX_DISTANCE 500 // Maximum distance (in cm) to ping.

NewPing sonar[SONAR_NUM] = {   // Sensor object array.  
  NewPing(ZW_A1, ZW_A1, MAX_DISTANCE), // Each sensor's trigger pin, echo pin, and max distance to ping.
  NewPing(ZW_A2, ZW_A2, MAX_DISTANCE),
  NewPing(ZW_A3, ZW_A3, MAX_DISTANCE),
  NewPing(ZW_A4, ZW_A4, MAX_DISTANCE)
};

long passFlag = 0;
int LEDBright[16] = {0};
uint32_t greenLEDstatus[16];
uint32_t redLEDstatus[16];

void indicatorLightRun(bool runFlag ,int pin, double *ang) { //b4
	
	if(runFlag == true){
  double radar0_sight;
  double radar1_sight;

  if(millis()-passFlag>200) {
    radar0_sight = sonar[0].ping_cm();
    radar1_sight = sonar[1].ping_cm();
		
    for(int i=0; i<16; i++) {
      LEDBright[i] /= 2;
      
      greenLEDstatus[i] = strip.Color(LEDBright[i],0 , 0);
      radarStrip.setPixelColor(i,greenLEDstatus[i]);
    }

    for (int j = 0; j < 8; j++) {
      if ((*ang) >= (22.5 * j) && (*ang) < (22.5 * (j + 1))) {
        if (radar0_sight < RADAR_SENSOR_RANGE && radar0_sight > 0) {
          LEDBright[j + 1] = LED_MAX_BRIGHT;
          radarStrip.setPixelColor(j + 1,ON_RED_MAX);
        }
        
        if (radar1_sight < RADAR_SENSOR_RANGE && radar1_sight > 0) {
          if (j == 7) {
          	LEDBright[0] = LED_MAX_BRIGHT;
            radarStrip.setPixelColor(0,ON_RED_MAX);
          }
          else {
          	LEDBright[j + 1 + 8] = LED_MAX_BRIGHT;
            radarStrip.setPixelColor(j + 1 + 8,ON_RED_MAX);
          }
        }
        radarStrip.show();
      }
    }
    
    passFlag = millis();
  }
  
 }
}

int getSensorDistance(int pinOut) {
		int distance;
		if(pinOut == 1){
				distance = sonar[0].ping_cm();
		}else if(pinOut == 2){
		  	distance = sonar[1].ping_cm();
		}else if(pinOut == 3){
		  	distance = sonar[2].ping_cm();
		}else if(pinOut == 4){
		  	distance = sonar[3].ping_cm();
		}else {
				distance = 999;
		}
		
	
		return distance;
		
		
}

void checkMouthTouch(int MouthSensorPin, Servo cathand_servo) {
  if (isLow( MouthSensorPin )) {
    //    if ( (millis() - mouthTime) > 500 ) {
    Serial.println("Mouth is Touched!!!!!");
    for (int repeat_i = 0; repeat_i < 3; repeat_i++) {
      cathand_servo.write(0);
      delay(200);
      cathand_servo.write(60);
      delay(200);
    }


    //      mouthTime = millis();
    //    }

  }
}

void checkHeadTouch(int HeadSensorPin) {
  if (isLow( HeadSensorPin )) {
    //    if ( (millis() - mouthTime) > 500 ) {
    Serial.println("Head is Touched!!!!!");
    for (int repeat_i = 0; repeat_i < 3; repeat_i++) {
      playNote(f6, eighthNote, meters_x2);
      playNote(d6, eighthNote, meters_x2);
      delay(200);
    }


    //      mouthTime = millis();
    //    }

  }
}

void RaptorCruise(Servo head_servo, double *head_pos, int *moving_direction) {

  //  LeftWheelForward_SpeedControl(127);
  //  RightWheelForward_SpeedControl(127);

  if ((*moving_direction) == POSITIVE) {
    (*head_pos) += 0.5;
    if ((*head_pos) > 180) {
      (*head_pos) = 180;
      (*moving_direction) = NEGATIVE;
    }
  }
  else if ((*moving_direction) == NEGATIVE) {
    (*head_pos) -= 0.5;
    if ((*head_pos) < 0) {
      (*head_pos) = 0;
      (*moving_direction) = POSITIVE;
    }
  }


  head_servo.write((*head_pos));
  Serial.print("Head position is :");
  Serial.println((*head_pos));
  //  delay(1);
}


void avoidObstacle(int RaptorSensorPin, int *head_moving_direction, double *raptorHead_pos, Servo head_servo) {
  int IRSensorValue = analogRead(RaptorSensorPin);

  double head_pos = *raptorHead_pos;
  //  if (isLow(RaptorSensorPin)) {
  if (IRSensorValue < 700) {

    if ((*head_moving_direction == POSITIVE)) {
      if (head_pos > 90) {
        LeftWheelBackward_SpeedControl(255);
        RightWheelForward_SpeedControl(127);
        delay(200);        //It means the obstacle is mainly in the right front of the raptor but the mainly body is not in front of the raptor. So the raptor turns left a short time(80ms) to avoid it.
        LeftWheelForward_SpeedControl(150);
        RightWheelForward_SpeedControl(150);
        //        head_pos = 0;
        head_pos = 88;
        (*raptorHead_pos) = head_pos;
        head_servo.write(head_pos);
        delay(1000);
        LeftWheelForward_SpeedControl(127);
        RightWheelBackward_SpeedControl(255);    //Make the raptor to face front again.
        delay(200);
      }
      //    else if ((*head_moving_direction == NEGATIVE)) {
      else if (head_pos < 90) {
        RightWheelBackward_SpeedControl(255);
        LeftWheelForward_SpeedControl(127);
        delay(300);       //It means the obstacle is in left of the raptor. But the main body maybe still in front of it. So the raptor turns to right for a longer time(100ms).
        LeftWheelForward_SpeedControl(150);
        RightWheelForward_SpeedControl(150);
        //        head_pos = 180;
        head_pos = 88;
        (*raptorHead_pos) = head_pos;
        head_servo.write(head_pos);
        delay(1000);
        LeftWheelBackward_SpeedControl(255);
        RightWheelForward_SpeedControl(127);
        delay(300);
      }
    }
    else if ((*head_moving_direction == NEGATIVE)) {
      if (head_pos > 90) {
        LeftWheelBackward_SpeedControl(255);
        RightWheelForward_SpeedControl(127);
        delay(300);      //It means the obstacle is in right of the raptor. But the main body maybe still in front of it. So the raptor turns to left for a longer time(100ms).
        LeftWheelForward_SpeedControl(150);
        RightWheelForward_SpeedControl(150);
        //        head_pos = 0;
        head_pos = 88;
        (*raptorHead_pos) = head_pos;
        head_servo.write(head_pos);
        delay(1000);
        RightWheelBackward_SpeedControl(255);    //Make the raptor to face front again.
        LeftWheelForward_SpeedControl(127);
        delay(300);
      }
      //    else if ((*head_moving_direction == NEGATIVE)) {
      else if (head_pos < 90) {
        RightWheelBackward_SpeedControl(255);
        LeftWheelForward_SpeedControl(127);
        delay(200);     //It means the obstacle is mainly in the left front of the raptor but the mainly body is not in front of the raptor. So the raptor turns right a short time(80ms) to avoid it.
        LeftWheelForward_SpeedControl(150);
        RightWheelForward_SpeedControl(150);
        //        head_pos = 180;
        head_pos = 88;
        (*raptorHead_pos) = head_pos;
        head_servo.write(head_pos);
        delay(1000);
        LeftWheelBackward_SpeedControl(255);
        RightWheelForward_SpeedControl(127);
        delay(200);
      }
    }
  }
  else {
    LeftWheelForward_SpeedControl(127);
    RightWheelForward_SpeedControl(127);
  }

}

void ControlLeftWheel(int LeftWheelButton, int BackwardButton) {
  if (isLow(LeftWheelButton)) {
    LeftWheelForward_SpeedControl(255);
  }
  else if (isHigh(LeftWheelButton) && isHigh(BackwardButton))
    LeftWheelForward_SpeedControl(0);
}

void ControlRightWheel(int RightWheelButton, int BackwardButton) {
  if (isLow(RightWheelButton)) {
    RightWheelForward_SpeedControl(255);
  }
  else if (isHigh(RightWheelButton)  && isHigh(BackwardButton))
    RightWheelForward_SpeedControl(0);
}

void ControlTwoWheelBackward(int BackwardButton, int LeftWheelButton, int RightWheelButton) {
  if (isLow(BackwardButton)) {
    LeftWheelBackward();
    RightWheelBackward();
  }
  else if (isHigh(BackwardButton) && isHigh(RightWheelButton) && isHigh(LeftWheelButton)) {
    LeftWheelBackward_SpeedControl(0);
    RightWheelBackward_SpeedControl(0);
  }
}

//void HammerKnock(int targetSensorPin, Servo hammer_servo) {
////int IRSensorValue = analogRead(targetSensorPin);
//
//if ( (millis() - startTimeKnock) > 200 ) {         //This is to set the interval time between a hammer knock position and its initial position. The interval time should be longer than 200ms.
//  if (IRSensorValue < 700) {                       //When a target is seen, the hammer begins to knock. The hammer's knocking and retoring interval time is no shorter than 200ms.
//    if (hammerState == LOW) {
//      hammer_servo.write(60);
//      hammerState = HIGH;
//    }
//    else if (hammerState == HIGH) {
//      hammer_servo.write(hammer_initPos);
//      hammerState = LOW;
//    }
//    startTimeKnock = millis();
//  }
//  else {                                      //When no target is seen, the hammer restore to its initial position.
//    hammer_servo.write(hammer_initPos);
//    hammerState = LOW;
//  }
//}
//}
long trumpetGo = 0;
void Trumpet () { //喇倀滴怀叫
  playNote(d6, eighthNote, meters_x2);
}
void LEDFlash() {

  if ( (millis() - startTimeLeft) > 50 ) {
    if (flash_times < 3) {                //The LED flashes for 10 times.
      if (leftLEDLastState == LOW)  {
        digitalWrite(LED_b1, HIGH);
        digitalWrite(LED_b2, HIGH);
        leftLEDLastState = HIGH;
      }
      else if (leftLEDLastState == HIGH)  {
        digitalWrite(LED_b1, LOW);
        digitalWrite(LED_b2, LOW);
        leftLEDLastState = LOW;
      }
      flash_times += 1;
      startTimeLeft = millis();
    }
    else {                            //When the LED finishes flashing 10 times, it reset the LEDFlashState to false meaning no LED is flashing.
      LEDFlashState = false;          //After flashing 10(user can set this value, the LED stops flashing.
      digitalWrite(LED_b1, LOW);
      digitalWrite(LED_b2, LOW);
      leftLEDLastState = LOW;
    }
  }
}


void checkIfAttacked(int *number_of_attacked, int AttackedSensor, int max_attacked_times) {//瀀 b3 b4
  lastAttackedSensorState = AttackedSensorState;
  AttackedSensorState = digitalState(AttackedSensor);
  Serial.print("AttackedSensorState:");//000000000000000000000000000000
  Serial.println(AttackedSensorState == LOW);
  Serial.print("lastAttackedSensorState1:");//111111111111111111111
  Serial.println(lastAttackedSensorState == HIGH);
  if (AttackedSensorState == LOW && lastAttackedSensorState == HIGH) {     //Only that the button is pushed(a high to low transition is found) means a valid attack
    if ( (millis() - startTimeAttacked) > 500 ) {                         //Set the interval time of two successive attack to be more than 500ms
      flash_times = 0;                                                    //When a button is pushed(high-->low transition found), the LED begin to flash 10 times which is defined in LEDFlash() function.
      LEDFlashState = true;                                               //The flash_times is refreshed when a new high-->low transition is found. The flag is set to true;
      (*number_of_attacked) += 1;
    }
    startTimeAttacked = millis();
  }


  if (LEDFlashState) {
    LEDFlash();
    Trumpet();
  }



//
//Serial.print("Attacked numver : ");
//Serial.println((*number_of_attacked));
  if ((*number_of_attacked) >= max_attacked_times) {
    digitalWrite(LED_b1, LOW);
    digitalWrite(LED_b2, LOW);
    reset_this_CPU(); //***退荤倀鎼崯退楀怀閿瀀拷0x0000退侀怀闄倀倀侯瀀閸怀喖瀀伴怀銉墯退氭瀀鏌　☉倀侯怀缂䀀�倀暟倀滃怀娼倀妸耀锕顭耀捄退剐紓倀忔
  }
}


long FlashStartTime = 0;
long policeLightStart = 0;
bool oldState = HIGH;
int showType = 0;

//bool firstRun = true;
long WipeStartTime = 0;
void GreenOnAll() {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(0, 255 / 16, 0));
    strip.show();
    delay(50);
  }
}

void OneLED_RGB(uint8_t pixel, uint32_t c) {

  strip.setPixelColor(pixel, c);
  strip.show();
  //    delay(50);

}

void FlashOneLED_RGB(int flash_speed, uint8_t pixel, uint32_t c) {
  long flash_time;

  switch (flash_speed) {
  case FAST:
    flash_time = FLASH_DURATION * 0.2;
    break;
  case MIDDLE:
    flash_time = FLASH_DURATION * 0.6;
    break;
  case SLOW:
    flash_time = FLASH_DURATION * 1.0;
    break;
  }
  if (millis() - FlashStartTime < flash_time / 2 ) {
    strip.setPixelColor(pixel, c);
    strip.show();
  }
  else if (millis() - FlashStartTime < flash_time ) {
    strip.setPixelColor(pixel, OFF_RGB);
    strip.show();
  }
  else {
    FlashStartTime = millis();
  }

}

void FlashOneLED_RGB(int flash_speed, uint8_t pixel, uint32_t c, int swap) {
  long flash_time;

  switch (flash_speed) {
  case FAST:
    flash_time = FLASH_DURATION * 0.2;
    break;
  case MIDDLE:
    flash_time = FLASH_DURATION * 0.6;
    break;
  case SLOW:
    flash_time = FLASH_DURATION * 1.0;
    break;
  }
  if (swap) {
    if (millis() - FlashStartTime < flash_time / 2 ) {
      strip.setPixelColor(pixel, OFF_RGB);
      strip.show();
    }
    else if (millis() - FlashStartTime < flash_time ) {
      strip.setPixelColor(pixel, c);
      strip.show();
    }
    else {
      FlashStartTime = millis();
    }
  }
  else {
    if (millis() - FlashStartTime < flash_time / 2 ) {
      strip.setPixelColor(pixel, c);
      strip.show();
    }
    else if (millis() - FlashStartTime < flash_time ) {
      strip.setPixelColor(pixel, OFF_RGB);
      strip.show();
    }
    else {
      FlashStartTime = millis();
    }
  }
}

void policeLightWipe(int pix_num, int *pixel) {
  if (firstRun) {
    WipeStartTime = millis();
    firstRun = false;
  }

  if ((*pixel) < pix_num) {
    if (millis() - WipeStartTime < 100) {
      strip.setPixelColor((*pixel), ON_BLUE);
      strip.setPixelColor(pix_num - 1 - (*pixel), ON_RED);
      strip.show();
    }
    else {
      (*pixel)++;
      WipeStartTime = millis();
    }
  }
  else {
    if (millis() - WipeStartTime < 100) {
      OneLED_RGB(0, OFF_RGB);
      OneLED_RGB(1, OFF_RGB);
      OneLED_RGB(2, OFF_RGB);
      OneLED_RGB(3, OFF_RGB);
      OneLED_RGB(4, OFF_RGB);
      OneLED_RGB(5, OFF_RGB);
      OneLED_RGB(6, OFF_RGB);
      OneLED_RGB(7, OFF_RGB);
      OneLED_RGB(8, OFF_RGB);
      OneLED_RGB(9, OFF_RGB);
    }
    else {
      WipeStartTime = millis();
      (*pixel = pix_num / 2);
    }
  }
}

void Wipe() {
  for (uint16_t i = 5; i < 10; i++) {
    strip.setPixelColor(i, ON_BLUE);
    strip.setPixelColor(9 - i, ON_RED);
    strip.show();
    delay(100);
  }
  OneLED_RGB(0, OFF_RGB);
  OneLED_RGB(1, OFF_RGB);
  OneLED_RGB(2, OFF_RGB);
  OneLED_RGB(3, OFF_RGB);
  OneLED_RGB(4, OFF_RGB);
  OneLED_RGB(5, OFF_RGB);
  OneLED_RGB(6, OFF_RGB);
  OneLED_RGB(7, OFF_RGB);
  OneLED_RGB(8, OFF_RGB);
  OneLED_RGB(9, OFF_RGB);
  delay(100);
}

void policeLightFlash(int pix_num, int flashSpeed, int swap) {
  for (int i = 0; i < pix_num / 2; i++) {
    FlashOneLED_RGB(flashSpeed, i, ON_RED);
    FlashOneLED_RGB(flashSpeed, i + pix_num / 2, ON_BLUE, swap);
  }
}

void policeLightRun(int TotalPix, int *pixels) {

  if (millis() - policeLightStart < 4000) {
    policeLightFlash(TotalPix, MIDDLE, UNSWAP);
  }
  else if (millis() - policeLightStart < 10000) {
    policeLightFlash(TotalPix, SLOW, SWAP);
  }
  else if (millis() - policeLightStart < 15000) {
    policeLightWipe(TotalPix, pixels);
  }
  else if (millis() - policeLightStart < 20000) {
    policeLightFlash(TotalPix, FAST, UNSWAP);
  }
  else
    policeLightStart = millis();


}

int brightness = 0;


void turnonlight() {
	if(brightness <255){
		brightness++;
	}
  delay(10);
  lampLED.setPixelColor(0, strip.Color(brightness, brightness, brightness));
  lampLED.setPixelColor(1, strip.Color(brightness, brightness, brightness));
  lampLED.show();
}

void turnofflight() {
	if(brightness>0){
			brightness--;
	}
  delay(10);
	lampLED.setPixelColor(0, strip.Color(brightness, brightness, brightness));
  lampLED.setPixelColor(1, strip.Color(brightness, brightness, brightness));
  lampLED.show();
}






void onGreenLED() {
  singleLED.setPixelColor(0, ON_GREEN);
  singleLED.setPixelColor(1, ON_GREEN);
  singleLED.show();
}

void onRedLED() {
  singleLED.setPixelColor(0, ON_RED);
  singleLED.setPixelColor(1, ON_RED);
  singleLED.show();
}

void onBlueLED() {
  singleLED.setPixelColor(0, ON_BLUE);
  singleLED.setPixelColor(1, ON_BLUE);
  singleLED.show();
}

void onYellowLED() {
  singleLED.setPixelColor(0, ON_YELLOW);
  singleLED.setPixelColor(1, ON_YELLOW);
  singleLED.show();
}

void offLED() {
  singleLED.setPixelColor(0, OFF_RGB);
  singleLED.setPixelColor(1, OFF_RGB);
  singleLED.show();
}

int direction = 1;
int SwingTimes = 0;
bool TailSwingCompleted = true;
void TailSwing(Servo TServo, double *servo_pos) {
  if ((*servo_pos) >= 180) {
    (*servo_pos) = 180;
    direction = -1;
  }
  if ((*servo_pos) <= 0)  {
    (*servo_pos) = 0;
    direction = 1;
    SwingTimes++;
  }


  (*servo_pos) = (*servo_pos) + 1 * direction;	  //Increase/decrease 10 degrees every run

  if (SwingTimes == 3 && (*servo_pos) >= TailServo_Init_Pos) {
    TailSwingCompleted = true;  //The tail swing 3 times
    (*servo_pos) = TailServo_Init_Pos;  //Restore the servo pos to its initial position
    SwingTimes = 0;
  }
  else TailSwingCompleted = false;

  Serial.print("Swing Times = ");
  Serial.println(SwingTimes);


  TServo.write((*servo_pos));


}

void BirdTailSwing(int SensorButton, Servo TailServo, double *TailServoPos) {
  if (isLow(SensorButton) || !TailSwingCompleted) {
    TailSwing(TailServo, TailServoPos);
  }
}

void BirdFollowTarget(int LeftSensor, int RightSensor) {
//if (analogRead(LeftSensor) < 400 && analogRead(RightSensor) < 400) {  //if the object is too close, the bird back off
//  LeftWheelBackward_SpeedControl(255);
//  RightWheelBackward_SpeedControl(255);
//}
//else if (analogRead(LeftSensor) < 600 && analogRead(RightSensor) < 600) { //the object is getting close, the bird stops
//  LeftWheelForward_SpeedControl(0);
//  RightWheelForward_SpeedControl(0);
//}
//else if (analogRead(LeftSensor) < 800 && analogRead(RightSensor) < 800) {  //both sensor see an object
//  LeftWheelForward_SpeedControl(255);
//  RightWheelForward_SpeedControl(255);
//}
//
//else if  (analogRead(LeftSensor) > 800 && analogRead(RightSensor) > 800) { //if no object is seen, the bird keep still
//  LeftWheelForward_SpeedControl(0);
//  RightWheelForward_SpeedControl(0);
//}
//else if  (analogRead(LeftSensor) < 800 && analogRead(RightSensor) > 800) {  //if left sensor see object, turn left
//  LeftWheelForward_SpeedControl(0);
//  RightWheelForward_SpeedControl(255);
//}
//else if  (analogRead(LeftSensor) > 800 && analogRead(RightSensor) < 800) {  //if right sensor see object, turn right
//  LeftWheelForward_SpeedControl(255);
//  RightWheelForward_SpeedControl(0);
//}

  if(analogRead(LeftSensor) < 800 ){
  	 digitalWrite(ZW_B1, HIGH);
  digitalWrite(MOTOR2P, HIGH);
  digitalWrite(MOTOR2M, LOW);
  }else{
  	 digitalWrite(ZW_B1, LOW);
  digitalWrite(MOTOR2P, LOW);
  digitalWrite(MOTOR2M, LOW);
  }
   if(analogRead(RightSensor) < 800 ){
  	 digitalWrite(ZW_B2, HIGH);
  	digitalWrite(MOTOR1P, HIGH);
    digitalWrite(MOTOR1M, LOW);
  }else{
  	 digitalWrite(ZW_B2, LOW);
  	digitalWrite(MOTOR1P, LOW);
    digitalWrite(MOTOR1M, LOW);
  }
  
}


void MotorControlSpeed(int MotorNumber, int Speed) {

	switch(MotorNumber) {
		case 1:
			if(Speed > 0) {
				digitalWrite(MOTOR1P, HIGH);
				Speed = constrain(Speed, 0, 254);
				int PWMvalue = 255 - Speed;
				analogWrite(MOTOR1M, PWMvalue); //Since the PWM is on negative pin, so the opposite value should be calculated

			} else if(Speed < 0) {
				digitalWrite(MOTOR1P, LOW);
				int PWMvalue = abs(Speed);
				PWMvalue = constrain(PWMvalue, 0, 255);
				analogWrite(MOTOR1M, PWMvalue);
			} else {
				digitalWrite(MOTOR1P, LOW);
				digitalWrite(MOTOR1M, LOW);
			}
			break;
		case 2:
			if(Speed > 0) {
				digitalWrite(MOTOR2P, HIGH);
				Speed = constrain(Speed, 0, 254);
				int PWMvalue = 255 - Speed;
				analogWrite(MOTOR2M, PWMvalue); //Since the PWM is on negative pin, so the opposite value should be calculated

			} else if(Speed < 0) {
				digitalWrite(MOTOR2P, LOW);
				int PWMvalue = abs(Speed);
				PWMvalue = constrain(PWMvalue, 0, 255);
				analogWrite(MOTOR2M, PWMvalue);
			} else {
				digitalWrite(MOTOR2P, LOW);
				digitalWrite(MOTOR2M, LOW);
			}
			break;
		case 3:
			if(Speed > 0) {
				digitalWrite(MOTOR3P, HIGH);
				Speed = constrain(Speed, 0, 254);
				int PWMvalue = 255 - Speed;
				analogWrite(MOTOR3M, PWMvalue); //Since the PWM is on negative pin, so the opposite value should be calculated

			} else if(Speed < 0) {
				digitalWrite(MOTOR3P, LOW);
				int PWMvalue = abs(Speed);
				PWMvalue = constrain(PWMvalue, 0, 255);
				analogWrite(MOTOR3M, PWMvalue);
			} else {
				digitalWrite(MOTOR3P, LOW);
				digitalWrite(MOTOR3M, LOW);
			}
			break;
		case 4:
			if(Speed > 0) {
				digitalWrite(MOTOR4P, HIGH);
				Speed = constrain(Speed, 0, 254);
				int PWMvalue = 255 - Speed;
				analogWrite(MOTOR4M, PWMvalue); //Since the PWM is on negative pin, so the opposite value should be calculated

			} else if(Speed < 0) {
				digitalWrite(MOTOR4P, LOW);
				int PWMvalue = abs(Speed);
				PWMvalue = constrain(PWMvalue, 0, 255);
				analogWrite(MOTOR4M, PWMvalue);
			} else {
				digitalWrite(MOTOR4P, LOW);
				digitalWrite(MOTOR4M, LOW);
			}
			break;
		default:
			break;
	}
}



void changeFollowFlagTrue () {
	Serial.println(9);
	isFollowFlag =1;
}
void changeFollowFlagFalse () {
	isFollowFlag =0;
}

boolean isAuto() {
	if(isFollowFlag == 1){
		return true;
	}
	else{
		return false;
	}	
}

boolean howFollow(int LEFT_IR_SENSOR,int RIGHT_IR_SENSOR,int leftOne,int rightOne) {
	 
	int Left_IR_Value;
	int Right_IR_Value;
	Left_IR_Value = analogRead(LEFT_IR_SENSOR);
	Right_IR_Value = analogRead(RIGHT_IR_SENSOR);
	
	boolean Left_IR,Right_IR;
	if(Left_IR_Value > Threshold ) Left_IR = 1;else Left_IR = 0;
	if(Right_IR_Value > Threshold ) Right_IR = 1;else Right_IR = 0;
	
//	Serial.println(isFollowFlag);
	if(Left_IR == leftOne && Right_IR == rightOne&&isFollowFlag == 1)
	return true;
	else
	return false;
	
}

void left_turn_speed(int speed){
		MotorControlSpeed(1, 0);
		MotorControlSpeed(2, speed*-1);
	
}
void right_turn_speed(int speed){
		MotorControlSpeed(1, speed);
		MotorControlSpeed(2, 0);
	
}
void go_forward_speed(int speed){
		MotorControlSpeed(1, speed);
		MotorControlSpeed(2, speed*-1);
	
}
void go_reverse_speed(int speed){
		MotorControlSpeed(1, speed*-1);
		MotorControlSpeed(2, speed);
	
}
//=======================================================================================================================

//
//String StrColor[9]={"NOTHING","RED","ORANGE","YELLOW","GREEN","BLUE","PURPLE","PINK","INVALID"};
//int PS2_Button_Read[6];
//int ProgramSelected;
//
//typedef struct{
//uint8_t red;
//uint8_t green;
//uint8_t blue;
//uint8_t red_max;
//uint8_t red_min;
//uint8_t green_max;
//uint8_t green_min;
//uint8_t blue_max;
//uint8_t blue_min;
//} RGB_type;
//
//RGB_type rgb;
//
//RGB_type RGB_STORE_DATA[COLOR_NUM_MAX];
//Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);  
// 
//const int buttonPin = ZW_A1;  
//const int buttonPinConfirm = ZW_A2;  
//
//int num = 0;
//int ColorNum = 0;
//
//void sensorMode();
//
// EasyButton button(buttonPin,sensorMode,CALL_IN_PUSHED);
// EasyButton buttonConfirm(buttonPinConfirm);
//
//void sensorMode(){  
//uint16_t clearcol, red, green, blue;
//tcs.getRawData(&red,&green,&blue,&clearcol);
//uint32_t sum = clearcol;
//float r, g, b;
//r = red; r /= sum;
//g = green; g /= sum;
//b = blue; b /= sum;
//r *= 256; g *= 256; b *= 256;   
// 
//rgb.red = (int)r;
//rgb.green = (int)g;
//rgb.blue = (int)b;
// 
//if(rgb.red_max < rgb.red)
//rgb.red_max = rgb.red;
// if(rgb.red_min > rgb.red)
//rgb.red_min = rgb.red;
//
//  if(rgb.green_max < rgb.green)
//rgb.green_max = rgb.green;
// if(rgb.green_min > rgb.green)
//rgb.green_min = rgb.green;
//
//  if(rgb.blue_max < rgb.blue)
//rgb.blue_max = rgb.blue;
// if(rgb.blue_min > rgb.blue)
//rgb.blue_min = rgb.blue;
//
//num++;
//
//Serial.print((int)num, DEC);
//Serial.print(":\t");
//
//if( CALIBRATION_COLOR == true)
//{
//  Serial.print(rgb.red, DEC); Serial.print("\t");Serial.print(rgb.green, DEC); Serial.print("\t");Serial.print(rgb.blue, DEC);
//  Serial.print(" R:"); Serial.print(rgb.red_max, DEC); Serial.print(":");Serial.print(rgb.red_min, DEC);
//  Serial.print(" G:");Serial.print(rgb.green_max, DEC); Serial.print(":");Serial.print(rgb.green_min, DEC);
//  Serial.print(" B:"); Serial.print(rgb.blue_max, DEC); Serial.print(":");Serial.print(rgb.blue_min, DEC);
//}
//else
//{
// Serial.print(rgb.red, HEX);Serial.print(rgb.green, HEX);Serial.print(rgb.blue, HEX); 
//}
//Serial.println();
//
// }
//
// 
// 
//
//
//color_type CheckColor(RGB_type rgb_data)
//{
// color_type color = INVALID;
//    for(int i = 0; i< COLOR_NUM_MAX; i++)
//    {
//        boolean red_in_limit = false;
//        boolean green_in_limit = false;
//        boolean blue_in_limit = false;
//        if((rgb_data.red <   RGB_STORE_DATA[i].red_max) &&  (rgb_data.red >   RGB_STORE_DATA[i].red_min)) 
//        {
//           red_in_limit = true;  
//        }  
//        if((rgb_data.green <   RGB_STORE_DATA[i].green_max) &&  (rgb_data.green >   RGB_STORE_DATA[i].green_min)) 
//        {
//           green_in_limit = true;  
//        }  
//        if((rgb_data.blue <   RGB_STORE_DATA[i].blue_max) &&  (rgb_data.blue >   RGB_STORE_DATA[i].blue_min)) 
//        {
//           blue_in_limit = true;  
//        }  
//
//        if(red_in_limit && green_in_limit && blue_in_limit)
//        {
//          color = i;
//        }
//      
//    }
//  return color;
//}
//
//
//void setup()
//{
//  Serial.begin(115200);       
//  pinMode(ZW_A1,INPUT);
//  pinMode(ZW_B1,OUTPUT);
//  
//     rgb.red = 0;
//     rgb.red_min = 255;
//     rgb.red_max = 0;
//     rgb.green = 0;
//     rgb.green_min = 255;
//     rgb.green_max = 0;
//     rgb.blue = 0;
//     rgb.blue_min = 255;
//     rgb.blue_max = 0;
//  if (tcs.begin()) {
//    Serial.println("Sensor founded!");
//  } else {
//    Serial.println("TCS34725 is not available, please try check it !");
//    while (1); 
//  } 
//
//  tcs.setInterrupt(false);
//  digitalWrite(ZW_B1,HIGH);
//
//if(CALIBRATION_COLOR)
//{
//   Serial.println("=======================================================================");
//   Serial.println("Please follow bellow steps to calibration those colors.");  
//   Serial.println("Step 1: Read the color of surronding.");
//   Serial.println("\t  Please keep nothing and try to adjust the position of the sensor, then press button A1.");
//   Serial.print  ("\t  Please do the same steps and try "); Serial.print(COLOR_CALIBRATION_TIMES); Serial.println(" times at least.");
//   Serial.println("\t  Please press button A2 when finished. it will save the surrounding color data to EEPROM.");   
//}
//else
//{
//    for(int i = 0; i< COLOR_NUM_MAX; i++)
//    {
//    int COLOR_START_POS;
//    COLOR_START_POS  =COLOR1_START_POS +  i * COLOR_LENGTH;
//    EEPROM.get(COLOR_START_POS,RGB_STORE_DATA[i]);
//    Serial.print("Read Color "); Serial.print(i);Serial.print(" data from EEPROM ");Serial.print(COLOR_START_POS); Serial.print(":\t");    
//    Serial.print(" red:"); Serial.print(RGB_STORE_DATA[i].red, DEC); Serial.print(":");Serial.print(RGB_STORE_DATA[i].red_max, DEC); Serial.print(":");Serial.print(RGB_STORE_DATA[i].red_min, DEC);
//    Serial.print(" green:");Serial.print(RGB_STORE_DATA[i].green, DEC);Serial.print(":"); Serial.print(RGB_STORE_DATA[i].green_max, DEC); Serial.print(":");Serial.print(RGB_STORE_DATA[i].green_min, DEC);
//    Serial.print(" blue:"); Serial.print(RGB_STORE_DATA[i].blue, DEC);Serial.print(":");Serial.print(RGB_STORE_DATA[i].blue_max, DEC); Serial.print(":");Serial.print(RGB_STORE_DATA[i].blue_min, DEC);
//    Serial.println("");
//}
//}
// 
//}
//
//boolean checkBolls(char bollChoosed)
//{  	
//
//if( CALIBRATION_COLOR == true)
//{
//  button.update();
//  buttonConfirm.update();
//  if(buttonConfirm.IsPushed() &&( num >=COLOR_CALIBRATION_TIMES)  )
//  {       
//    if((rgb.red_max  - rgb.red_min) >COLOR_TOLERANCE_MAX  ||
//        (rgb.green_max  - rgb.green_min) >COLOR_TOLERANCE_MAX  ||
//        (rgb.blue_max  - rgb.blue_min) >COLOR_TOLERANCE_MAX )
//    {
//      Serial.println("ERROR, please re-calibration this object");
//      num = 0;
//      rgb.red = 0;
//      rgb.red_min = 255;
//      rgb.red_max = 0;
//      rgb.green = 0;
//      rgb.green_min = 255;
//      rgb.green_max = 0;
//      rgb.blue = 0;
//      rgb.blue_min = 255;
//      rgb.blue_max = 0;
//    }
//    else
//    {        
//       int COLOR_START_POS;
//      COLOR_START_POS  =COLOR1_START_POS +  ColorNum * COLOR_LENGTH;
//  
//      RGB_STORE_DATA[ColorNum].red =(int) (rgb.red_max + rgb.red_min)/2;
//      RGB_STORE_DATA[ColorNum].green =(int) (rgb.green_max + rgb.green_min)/2;
//      RGB_STORE_DATA[ColorNum].blue =(int) (rgb.blue_max + rgb.blue_min)/2;
//  
//      rgb.red_max     += COLOR_TOLERANCE;
//      rgb.red_min     -=  COLOR_TOLERANCE;
//      rgb.green_max   += COLOR_TOLERANCE;
//      rgb.green_min   -= COLOR_TOLERANCE;
//      rgb.blue_max    += COLOR_TOLERANCE;
//      rgb.blue_min    -= COLOR_TOLERANCE;
//
//      RGB_STORE_DATA[ColorNum].red_max = constrain(rgb.red_max,0,255);
//      RGB_STORE_DATA[ColorNum].red_min = constrain(rgb.red_min,0,255);
//      RGB_STORE_DATA[ColorNum].green_max = constrain(rgb.green_max,0,255);
//      RGB_STORE_DATA[ColorNum].green_min = constrain(rgb.green_min,0,255);
//      RGB_STORE_DATA[ColorNum].blue_max = constrain(rgb.blue_max,0,255);
//      RGB_STORE_DATA[ColorNum].blue_min = constrain(rgb.blue_min,0,255);
//  
//      EEPROM.put(COLOR_START_POS, RGB_STORE_DATA[ColorNum]); 
//      Serial.print("Write Color "); Serial.print(ColorNum);Serial.print(" data to EEPROM ");Serial.print(COLOR_START_POS); Serial.println(":\t");    
//      Serial.print(" red:"); Serial.print(rgb.red, DEC); Serial.print(":");Serial.print(rgb.red_max, DEC); Serial.print(":");Serial.print(rgb.red_min, DEC);
//      Serial.print(" green:");Serial.print(rgb.green, DEC);Serial.print(":"); Serial.print(rgb.green_max, DEC); Serial.print(":");Serial.print(rgb.green_min, DEC);
//      Serial.print(" blue:"); Serial.print(rgb.blue, DEC);Serial.print(":");Serial.print(rgb.blue_max, DEC); Serial.print(":");Serial.print(rgb.blue_min, DEC);
//      Serial.println("");
//    num = 0;
//    rgb.red = 0;
//    rgb.red_min = 255;
//    rgb.red_max = 0;
//    rgb.green = 0;
//    rgb.green_min = 255;
//    rgb.green_max = 0;
//    rgb.blue = 0;
//    rgb.blue_min = 255;
//    rgb.blue_max = 0;
//    ColorNum++;
//
//    if((ColorNum > 0) && (ColorNum <COLOR_NUM_MAX)  ) 
//    {
//        Serial.print("Step "); Serial.print(ColorNum+1); Serial.print(": Read the color of No.");Serial.print(ColorNum); Serial.println(" object");
//        Serial.print("\t  Please put No.");Serial.print(ColorNum); Serial.println(" object and try to adjust the position of the sensor, then press button A1.");
//        Serial.print("\t  Please do the same steps and try "); Serial.print(COLOR_CALIBRATION_TIMES); Serial.println(" times at least.");
//        Serial.print("\t  Please press button A2 when finished. it will save the color data of No.");Serial.print(ColorNum);Serial.println(" object to EEPROM.");
//    } 
//    if( ColorNum >= COLOR_NUM_MAX) {
//      CALIBRATION_COLOR = false;
//      Serial.println("Calibrantion finished.!!!");
//      };
//    }
//  }
//
//}
//else
//{
//  color_type color;
//  sensorMode();
//
//  color = CheckColor(rgb);
//  Serial.print(" The color of this object is "); Serial.println(StrColor[color]);
//  delay(3000);
//  
//}
// if(color == bollChoosed){
// 	return true;
// }else{
//		return false;
// }
//
//}


void throwTheBall(Servo B1_mian_servo, Servo B2_throw_servo)
{
  B1_mian_servo.write(0);
  delay(500);
  B2_throw_servo.write(0);
  delay(500);
  B1_mian_servo.write(90);
  B2_throw_servo.write(90);
  
}

void filterTheBall(Servo B1_mian_servo, Servo B2_throw_servo)
{
  B1_mian_servo.write(180);
  delay(500);
  B1_mian_servo.write(90);
  B2_throw_servo.write(90);
  
}

void leftPunches(Servo left_fist_servo){
	left_fist_servo.write(90);
}
void leftTakeAFist(Servo left_fist_servo){
	left_fist_servo.write(0);
}

void rightPunches(Servo right_fist_servo){
	right_fist_servo.write(90);
}

void rightTakeAFist(Servo right_fist_servo){
	right_fist_servo.write(180);
}

void loadingCarriage(Servo carrriage_servo){
	carrriage_servo.write(5);
}

void unloadingCarriage(Servo carrriage_servo){
	carrriage_servo.write(25);
}

void yellowLEDOn(int whichLamp){
	
	if(whichLamp == 1){
 		 digitalWrite(ZW_B1, HIGH);
	}else if(whichLamp == 2){
 		 digitalWrite(ZW_B2, HIGH);
	}else if(whichLamp == 3){
 		 digitalWrite(ZW_B3, HIGH);
	}else if(whichLamp = 4){
 		 digitalWrite(ZW_B4, HIGH);
	} 
}


void offLED(int whichLampOff) {
 	if(whichLampOff == 1){
 		 digitalWrite(ZW_B1, LOW);
	}else if(whichLampOff == 2){
 		 digitalWrite(ZW_B2, LOW);
	}else if(whichLampOff == 3){
 		 digitalWrite(ZW_B3, LOW);
	}else if(whichLampOff = 4){
 		 digitalWrite(ZW_B4, LOW);
	} 
}

void MotorControl(int MotorNumber, int RunningStatus,int speedValue) {
	Serial.println(speedValue);
  switch (MotorNumber) {
  case 1:
    if (RunningStatus == FORWARD) {
			#ifdef ROBOTCOM_REVA
			analogWrite(MOTOR1P, speedValue);
      digitalWrite(MOTOR1M, HIGH);
			#else
			
      digitalWrite(MOTOR1P, HIGH);
      digitalWrite(MOTOR1M, LOW);
      #endif
    }
    else if (RunningStatus == BACKWARD) {
    	#ifdef ROBOTCOM_REVA
    	analogWrite(MOTOR1P, speedValue);
      digitalWrite(MOTOR1M, LOW);
			
			#else
      digitalWrite(MOTOR1P, LOW);
      digitalWrite(MOTOR1M, HIGH);
      #endif
    }
    else if (RunningStatus == STOP) {
      digitalWrite(MOTOR1P, LOW);
      digitalWrite(MOTOR1M, LOW);
    }
    break;
  case 2:
    if (RunningStatus == FORWARD) {
    	#ifdef ROBOTCOM_REVA
      analogWrite(MOTOR2P, speedValue);
      digitalWrite(MOTOR2M, HIGH);
			
			#else
      digitalWrite(MOTOR2P, HIGH);
      digitalWrite(MOTOR2M, LOW);
      #endif
    }
    else if (RunningStatus == BACKWARD) {
    	#ifdef ROBOTCOM_REVA
			analogWrite(MOTOR2P, speedValue);
      digitalWrite(MOTOR2M, LOW);
			#else
      digitalWrite(MOTOR2P, LOW);
      digitalWrite(MOTOR2M, HIGH);
      #endif
    }
    else if (RunningStatus == STOP) {
      digitalWrite(MOTOR2P, LOW);
      digitalWrite(MOTOR2M, LOW);
    }
    break;
  case 3:
    if (RunningStatus == FORWARD) {
    	#ifdef ROBOTCOM_REVA
			analogWrite(MOTOR3P, speedValue);
      digitalWrite(MOTOR3M, HIGH);
			#else
      digitalWrite(MOTOR3P, HIGH);
      digitalWrite(MOTOR3M, LOW);
      #endif
    }
    else if (RunningStatus == BACKWARD) {
    	#ifdef ROBOTCOM_REVA
			analogWrite(MOTOR3P, speedValue);
      digitalWrite(MOTOR3M, LOW);
			#else
      digitalWrite(MOTOR3P, LOW);
      digitalWrite(MOTOR3M, HIGH);
      #endif
    }
    else if (RunningStatus == STOP) {
      digitalWrite(MOTOR3P, LOW);
      digitalWrite(MOTOR3M, LOW);
      
    }
    break;
  case 4:
    if (RunningStatus == FORWARD) {
    	#ifdef ROBOTCOM_REVA
			analogWrite(MOTOR4P, speedValue);
      digitalWrite(MOTOR4M, HIGH);
			#else
      digitalWrite(MOTOR4P, HIGH);
      digitalWrite(MOTOR4M, LOW);
      #endif
    }
    else if (RunningStatus == BACKWARD) {
    	#ifdef ROBOTCOM_REVA
			analogWrite(MOTOR4P, speedValue);
      digitalWrite(MOTOR4M, LOW);
			
			#else
      digitalWrite(MOTOR4P, LOW);
      digitalWrite(MOTOR4M, HIGH);
      #endif
    }
    else if (RunningStatus == STOP) {
      digitalWrite(MOTOR4P, LOW);
      digitalWrite(MOTOR4M, LOW);
    }
    break;
  default:
    break;
  }
}

void optionalServeAng(Servo oServo, double ang) {
  oServo.write(ang);
}
double servoChange_mi = 0;
void servoChange(Servo Self_servo,  double *ang , double angleValue, double maxValue){
	if(angleValue < 0 ){
		if((*ang)>maxValue){
			if(millis() - servoChange_mi > 10){
		Serial.println((*ang));
		(*ang) +=angleValue;
		if((*ang)>180){
			(*ang)  = 180;
		}
		if((*ang)<0){
			(*ang)  = 0;
		}
		Self_servo.write(*ang);
			servoChange_mi = millis();
		
	}
		}
	}else{
		if((*ang)<maxValue){
			if(millis() - servoChange_mi > 10){
		Serial.println((*ang));
		(*ang) +=angleValue;
		if((*ang)>180){
			(*ang)  = 180;
		}
		if((*ang)<0){
			(*ang)  = 0;
		}
		Self_servo.write(*ang);
			servoChange_mi = millis();
		
	}
		}
	}

	
		
}

void servoTurnto( Servo Self_servo, double Servoangle){
	Self_servo.write(Servoangle);
}
int num = 0;
void VoiceNum(int num, int arg1, int arg2) {
	
	 int tmp, val;
    int hundred = 0;
    val = num;

    tmp = val / 100;
    if (tmp > 0)
    {
        VoiceWord(tmp,  arg1,  arg2);
        delay(400);
        VoiceWord(12,  arg1,  arg2);
        delay(400);
        hundred = 1;
    }
    val = val % 100;
    tmp = val / 10;
    if (tmp > 0)
    {
        VoiceWord(tmp,  arg1,  arg2);
        delay(400);
        VoiceWord(11,  arg1,  arg2);
        delay(400);
        hundred = 1;
    }
    else if (hundred == 1)
    {
        VoiceWord(10,  arg1,  arg2);
        delay(400);
    }
    val = val % 10;

    if (val > 0)
    {
        VoiceWord(val,  arg1,  arg2);
        delay(400);
    }
}
	void VoiceWord(int idx , int arg1 , int arg2)
{ 
	if( arg1 == 1 ) {
		arg1 = A0;
	}else if( arg1 == 2 ){
		arg1 = A1;
	}else if( arg1 == 3 ){
		arg1 = A2;
	}else if( arg1 == 4 ){
		arg1 = A3;
	}
	
	if( arg2 == 1 ) {
		arg2 = A0;
	}else if( arg2 == 2 ){
		arg2 = A1;
	}else if( arg2 == 3 ){
		arg2 = A2;
	}else if( arg2 == 4 ){
		arg2 = A3;
	}
  digitalWrite(arg1,HIGH);
  delayMicroseconds(200);
  digitalWrite(arg1,LOW);
  delayMicroseconds(200);
  digitalWrite(arg1,HIGH);
  delayMicroseconds(200);
  digitalWrite(arg1,LOW);
  delayMicroseconds(200);
  for(int i=0;i<idx;i++)
  {
      digitalWrite(arg2,HIGH);
      delayMicroseconds(200);
      digitalWrite(arg2,LOW);
      delayMicroseconds(200);
  }
  delay(1000);
}




void motor_changeSpeed(int MotorNumber, int RunningStatus,double speedValue ,double *current) {
	
	 *current =  *current + speedValue;
	 if((*current)>255){
	 	*current = 255;
	 }
	 if((*current)<0){
	 	*current = 0;
	 }
	 
	 Serial.println(*current);
  switch (MotorNumber) {
  case 1:
    if (RunningStatus == FORWARD) {
			#ifdef ROBOTCOM_REVA
			analogWrite(MOTOR1P, *current);
      digitalWrite(MOTOR1M, HIGH);
			#else
 			digitalWrite(MOTOR1P, HIGH);
  		//digitalWrite(MOTOR1M, LOW);
 			int PWMvalue = 255 - *current;
  		analogWrite(MOTOR1M, PWMvalue);   //Since the PWM is on negative pin, so the opposite value should be calculated
      #endif
    }
    else if (RunningStatus == BACKWARD) {
    	#ifdef ROBOTCOM_REVA
    	analogWrite(MOTOR1P, *current);
      digitalWrite(MOTOR1M, LOW);
			
			#else
      digitalWrite(MOTOR1P, LOW);
  		analogWrite(MOTOR1M, *current);
      #endif
    }
    else if (RunningStatus == STOP) {
      digitalWrite(MOTOR1P, LOW);
      digitalWrite(MOTOR1M, LOW);
    }
    break;
  case 2:
    if (RunningStatus == FORWARD) {
    	#ifdef ROBOTCOM_REVA
      analogWrite(MOTOR2P, *current);
      digitalWrite(MOTOR2M, HIGH);
			
			#else
      digitalWrite(MOTOR2P, HIGH);
 			int PWMvalue = 255 - *current;
  		analogWrite(MOTOR2M, PWMvalue); 
      #endif
    }
    else if (RunningStatus == BACKWARD) {
    	#ifdef ROBOTCOM_REVA
			analogWrite(MOTOR2P, *current);
      digitalWrite(MOTOR2M, LOW);
			#else
      digitalWrite(MOTOR2P, LOW);
  		analogWrite(MOTOR2M, *current);
      #endif
    }
    else if (RunningStatus == STOP) {
      digitalWrite(MOTOR2P, LOW);
      digitalWrite(MOTOR2M, LOW);
    }
    break;
  case 3:
    if (RunningStatus == FORWARD) {
    	#ifdef ROBOTCOM_REVA
			analogWrite(MOTOR3P, *current);
      digitalWrite(MOTOR3M, HIGH);
			#else
      digitalWrite(MOTOR3P, HIGH);
      digitalWrite(MOTOR3M, LOW);
      #endif
    }
    else if (RunningStatus == BACKWARD) {
    	#ifdef ROBOTCOM_REVA
			analogWrite(MOTOR3P, *current);
      digitalWrite(MOTOR3M, LOW);
			#else
      digitalWrite(MOTOR3P, LOW);
      digitalWrite(MOTOR3M, HIGH);
      #endif
    }
    else if (RunningStatus == STOP) {
      digitalWrite(MOTOR3P, LOW);
      digitalWrite(MOTOR3M, LOW);
      
    }
    break;
  case 4:
    if (RunningStatus == FORWARD) {
    	#ifdef ROBOTCOM_REVA
			analogWrite(MOTOR4P, *current);
      digitalWrite(MOTOR4M, HIGH);
			#else
      digitalWrite(MOTOR4P, HIGH);
      digitalWrite(MOTOR4M, LOW);
      #endif
    }
    else if (RunningStatus == BACKWARD) {
    	#ifdef ROBOTCOM_REVA
			analogWrite(MOTOR4P, *current);
      digitalWrite(MOTOR4M, LOW);
			
			#else
      digitalWrite(MOTOR4P, LOW);
      digitalWrite(MOTOR4M, HIGH);
      #endif
    }
    else if (RunningStatus == STOP) {
      digitalWrite(MOTOR4P, LOW);
      digitalWrite(MOTOR4M, LOW);
    }
    break;
  default:
    break;
  }

	
}


void motor_speed_fillings(int MotorNumber, int RunningStatus,double speedValue ) {
	if(speedValue <0){
		speedValue = 0;
	}
	if(speedValue >255){
		speedValue =255;
	}
	Serial.println(speedValue);
  switch (MotorNumber) {
  case 1:
    if (RunningStatus == FORWARD) {
			#ifdef ROBOTCOM_REVA
			analogWrite(MOTOR1P, speedValue);
      digitalWrite(MOTOR1M, HIGH);
			#else
 			digitalWrite(MOTOR1P, HIGH);
  		//digitalWrite(MOTOR1M, LOW);
 			int PWMvalue = 255 - speedValue;
  		analogWrite(MOTOR1M, PWMvalue);   //Since the PWM is on negative pin, so the opposite value should be calculated
      #endif
    }
    else if (RunningStatus == BACKWARD) {
    	#ifdef ROBOTCOM_REVA
    	analogWrite(MOTOR1P, speedValue);
      digitalWrite(MOTOR1M, LOW);
			
			#else
      digitalWrite(MOTOR1P, LOW);
  		analogWrite(MOTOR1M, speedValue);
      #endif
    }
    else if (RunningStatus == STOP) {
      digitalWrite(MOTOR1P, LOW);
      digitalWrite(MOTOR1M, LOW);
    }
    break;
  case 2:
    if (RunningStatus == FORWARD) {
    	#ifdef ROBOTCOM_REVA
      analogWrite(MOTOR2P, speedValue);
      digitalWrite(MOTOR2M, HIGH);
			
			#else
      digitalWrite(MOTOR2P, HIGH);
 			int PWMvalue = 255 - speedValue;
  		analogWrite(MOTOR2M, PWMvalue); 
      #endif
    }
    else if (RunningStatus == BACKWARD) {
    	#ifdef ROBOTCOM_REVA
			analogWrite(MOTOR2P, speedValue);
      digitalWrite(MOTOR2M, LOW);
			#else
      digitalWrite(MOTOR2P, LOW);
  		analogWrite(MOTOR2M, speedValue);
      #endif
    }
    else if (RunningStatus == STOP) {
      digitalWrite(MOTOR2P, LOW);
      digitalWrite(MOTOR2M, LOW);
    }
    break;
  case 3:
    if (RunningStatus == FORWARD) {
    	#ifdef ROBOTCOM_REVA
			analogWrite(MOTOR3P, speedValue);
      digitalWrite(MOTOR3M, HIGH);
			#else
      digitalWrite(MOTOR3P, HIGH);
      digitalWrite(MOTOR3M, LOW);
      #endif
    }
    else if (RunningStatus == BACKWARD) {
    	#ifdef ROBOTCOM_REVA
			analogWrite(MOTOR3P, speedValue);
      digitalWrite(MOTOR3M, LOW);
			#else
      digitalWrite(MOTOR3P, LOW);
      digitalWrite(MOTOR3M, HIGH);
      #endif
    }
    else if (RunningStatus == STOP) {
      digitalWrite(MOTOR3P, LOW);
      digitalWrite(MOTOR3M, LOW);
      
    }
    break;
  case 4:
    if (RunningStatus == FORWARD) {
    	#ifdef ROBOTCOM_REVA
			analogWrite(MOTOR4P, speedValue);
      digitalWrite(MOTOR4M, HIGH);
			#else
      digitalWrite(MOTOR4P, HIGH);
      digitalWrite(MOTOR4M, LOW);
      #endif
    }
    else if (RunningStatus == BACKWARD) {
    	#ifdef ROBOTCOM_REVA
			analogWrite(MOTOR4P, speedValue);
      digitalWrite(MOTOR4M, LOW);
			
			#else
      digitalWrite(MOTOR4P, LOW);
      digitalWrite(MOTOR4M, HIGH);
      #endif
    }
    else if (RunningStatus == STOP) {
      digitalWrite(MOTOR4P, LOW);
      digitalWrite(MOTOR4M, LOW);
    }
    break;
  default:
    break;
  }

	
}





