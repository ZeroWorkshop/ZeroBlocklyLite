#include "ZeroWorkshop_lib_levelS.h"
#include "ZeroWorkshop_Macro_Definitions.h"

#include <Arduino.h>
//#include <Servo.h>
#include <EEPROM.h>


static void (*reset_this_CPU)(void) = 0x0000; // ***婵犮垼娉涚粔宕囩礊閸涙潙瀚夐柣婵堢潓U闂佸憡鍨兼慨銈夊汲閻旂厧绠伴柛銉墯鐎氾拷

struct ProgNumInEPROM {
  int lastProgSelected;
};

int buffer_index = 0;

bool GrabActionCompleted = false;
bool PutActionCompleted = false;

long startTimeLeft = 0;
long startTimeRight = 0;
bool leftLEDLastState = LOW;
bool rightLEDLastState = LOW;

long scoreTime = 0;

long mouthTime = 0;

int fanHeadMove_direction = 1;

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

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      noteDuration = 1000 / noteDurations[(*ProgramSelector)];
      tone(SpeakerPIN, NOTE[(*ProgramSelector)], noteDuration);

      // the note's duration + 30% seems to work well:
      pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      noTone(SpeakerPIN);


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

void servopulse(int servopin, int angle)//闂佽法鍠愰弸濠氬箯閻戣姤鏅搁柡鍌樺�栫�氳绋夐敓浠嬫煥閻斿憡鐏柟椋庡厴閺佹捇寮妶鍡楊伓闂佽法鍠曞Λ鍕礄娴犲鏅搁柡鍌樺�栫�氾拷
{

  int pulsewidth = (angle * 11) + 500; //闂佽法鍠愰弸濠氬箯閻戣姤鏅搁悷娆愬笩椤旀劙骞忛悿顖涚ギ闂佽法鍠愰弸濠氬箯閾氬倽绀�500-2480闂佽法鍠愰弸濠氬箯閻戣姤鏅搁柡鍌樺�栫�氬綊鏌ㄩ悢鍛婄伄闁瑰嘲鍢查敓鏂ゆ嫹

  digitalWrite(servopin, HIGH);   //闂佽法鍠愰弸濠氬箯閻戣姤鏅搁柡鍌樺�栫�氬綊鏌ㄩ悢鍛婄伄闁圭兘鏀辩粔鍓ф嫚濮楋拷閺佹捇鎮埄鍐╃伄闁归鍏橀弫鎾诲棘閵堝棗顏堕梺璺ㄥ櫐閹凤拷

  delayMicroseconds(pulsewidth);  //闂佽法鍠愰弸濠氬箯闁垮顦ч梺璺ㄥ枑閺嬪骞忛悜鑺ユ櫢闁哄倶鍊栫�氬綊宕愭總鍛婃櫢闁哄倶鍊栫�氱懓顕ラ锟介弫鎾诲棘閵堝棗顏堕梺璺ㄥ枑閺嬪骞忛敓锟�

  digitalWrite(servopin, LOW);    //闂佽法鍠愰弸濠氬箯閻戣姤鏅搁柡鍌樺�栫�氬綊鏌ㄩ悢鍛婄伄闁圭兘鏀辩粔鍓ф嫚濮楋拷閺佹捇鎮埄鍐╃伄闁归鍏橀弫鎾诲棘閵堝棗顏堕梺璺ㄥ櫐閹凤拷

  delayMicroseconds(20000 - pulsewidth);

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
  Left_Motor(STOP);

  Right_Motor(STOP);

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

void onRedLED() {
  digitalWrite(LED_9, HIGH);

}

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

void playNote(int Note, int Meter, int Length) {
  tone(BuzzerPin, Note, Meter * Length);
  //  delay(Meter * 1.3 * Length);
  long duration_time = millis();
  for (int i = 0; i < Meter * 1.3 * Length * 200; i++) {
//    Serial.println(i);
    if (millis() - duration_time > Meter * 1.3 * Length) break;
    //digitalRead(ZW_A1);
  }
  //  noTone(BuzzerPin);
}

void playNoteShort(int Note, int Meter, int Length) {
  tone(BuzzerPin, Note, Meter * Length);
  //  delay(Meter * 1.3 * Length);
  long duration_time = millis();
  for (int i = 0; i < Meter * 1.3 * Length * 200; i++) {
//    Serial.println(i);
    if (millis() - duration_time > Meter * 1.0 * Length) break;
    //digitalRead(ZW_A1);
  }
  //  noTone(BuzzerPin);
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
      playNote(e7, sixteenthNote,  meters_x1);  playNote(e7, sixteenthNote,  meters_x1);  playNote(0, sixteenthNote,  meters_x1);  playNote(e7, sixteenthNote,  meters_x1);
      playNote(0, sixteenthNote,  meters_x1);  playNote(c7, sixteenthNote,  meters_x1);  playNote(e7, sixteenthNote,  meters_x1);  playNote(0, sixteenthNote,  meters_x1);
      playNote(g7, sixteenthNote,  meters_x1);  playNote(0, sixteenthNote,  meters_x1);  playNote(0, sixteenthNote,  meters_x1);   playNote(0, sixteenthNote,  meters_x1);
      playNote(g6, sixteenthNote,  meters_x1);  playNote(0, sixteenthNote,  meters_x1);  playNote(0, sixteenthNote,  meters_x1);  playNote(0, sixteenthNote,  meters_x1);

      playNote(c7, sixteenthNote,  meters_x1);  playNote(0, sixteenthNote,  meters_x1);  playNote(0, sixteenthNote,  meters_x1);  playNote(g6, sixteenthNote,  meters_x1);
      playNote(0, sixteenthNote,  meters_x1);  playNote(0, sixteenthNote,  meters_x1);  playNote(e6, sixteenthNote,  meters_x1);  playNote(0, sixteenthNote,  meters_x1);
      playNote(0, sixteenthNote,  meters_x1);  playNote(a6, sixteenthNote,  meters_x1);  playNote(0, sixteenthNote,  meters_x1);  playNote(b6, sixteenthNote,  meters_x1);
      playNote(0, sixteenthNote,  meters_x1);  playNote(as6, sixteenthNote,  meters_x1);  playNote(a6, sixteenthNote,  meters_x1);  playNote(0, sixteenthNote,  meters_x1);

      playNote(g6, eighthNote,  meters_x1);  playNote(e7, eighthNote,  meters_x1);  playNote(g7, eighthNote,  meters_x1);
      playNote(a7, sixteenthNote,  meters_x1);  playNote(0, sixteenthNote,  meters_x1);  playNote(f7, sixteenthNote,  meters_x1);  playNote(g7, sixteenthNote,  meters_x1);
      playNote(0, sixteenthNote,  meters_x1);  playNote(e7, sixteenthNote,  meters_x1);  playNote(0, sixteenthNote,  meters_x1); playNote(c7, sixteenthNote,  meters_x1);
      playNote(d7, sixteenthNote,  meters_x1);  playNote(b6, sixteenthNote,  meters_x1);  playNote(0, sixteenthNote,  meters_x1);  playNote(0, sixteenthNote,  meters_x1);

      playNote(c7, sixteenthNote,  meters_x1);  playNote(0, sixteenthNote,  meters_x1);  playNote(0, sixteenthNote,  meters_x1);  playNote(g6, sixteenthNote,  meters_x1);
      playNote(0, sixteenthNote,  meters_x1);  playNote(0, sixteenthNote,  meters_x1);  playNote(e6, sixteenthNote,  meters_x1);  playNote(0, sixteenthNote,  meters_x1);
      playNote(0, sixteenthNote,  meters_x1);  playNote(a6, sixteenthNote,  meters_x1);  playNote(0, sixteenthNote,  meters_x1);  playNote(b6, sixteenthNote,  meters_x1);
      playNote(0, sixteenthNote,  meters_x1);  playNote(as6, sixteenthNote,  meters_x1);  playNote(a6, sixteenthNote,  meters_x1);  playNote(0, sixteenthNote,  meters_x1);

      playNote(g6, eighthNote,  meters_x1);  playNote(e7, eighthNote,  meters_x1);  playNote(g7, eighthNote,  meters_x1);
      playNote(a7, sixteenthNote,  meters_x1);  playNote(0, sixteenthNote,  meters_x1);  playNote(f7, sixteenthNote,  meters_x1);  playNote(g7, sixteenthNote,  meters_x1);
      playNote(0, sixteenthNote,  meters_x1);  playNote(e7, sixteenthNote,  meters_x1);  playNote(0, sixteenthNote,  meters_x1); playNote(c7, sixteenthNote,  meters_x1);
      playNote(d7, sixteenthNote,  meters_x1);  playNote(b6,sixteenthNote,  meters_x1);  playNote(0, sixteenthNote,  meters_x1);  playNote(0, sixteenthNote,  meters_x1);
      break;
    case 4:
      break;

    case 5:
      break;

    default:
      break;
  }

}
/*void PanMoveClockwise(Servo myservo, double *Pos)
  {
  double temp_pos = *Pos;
  temp_pos += 2;     //1 step is 2 degrees
  if (temp_pos >= 180) temp_pos = 180;

   Pos = temp_pos;

  myservo.write(temp_pos);
  //    delay(10);
  }


  void PanMoveCounterclockwise(Servo myservo, double *Pos)
  {
  double temp_pos = *Pos;
  temp_pos -= 2;     //1 step is -2 degrees
  if (temp_pos <= 0) temp_pos = 0;

   Pos = temp_pos;

  myservo.write(temp_pos);
  //    delay(10);
  }

  void TiltMoveDown(Servo myservo, double *Pos)
  {
  double temp_pos = *Pos;
  temp_pos -= 2;     //1 step is -2 degrees
  if (temp_pos <= 0) temp_pos = 0;

   Pos = temp_pos;

  myservo.write(temp_pos);
  //    delay(10);
  }

  void TiltMoveUp(Servo myservo, double *Pos)
  {
  double temp_pos = *Pos;
  temp_pos += 2;     //1 step is 2 degrees
  if (temp_pos >= 180) temp_pos = 180;

   Pos = temp_pos;

  myservo.write(temp_pos);
  //    delay(10);
  }

  void ServoSteeringRight(Servo steer_servo1, Servo steer_servo2, double *Pos)
  {
  double temp_pos = *Pos;
  temp_pos += 10;     //1 step is 10 degrees
  if (temp_pos >= 160) temp_pos = 160;

   Pos = temp_pos;

  steer_servo1.write(temp_pos);
  steer_servo2.write(temp_pos);
  //    delay(10);
  }


  void ServoSteeringLeft(Servo steer_servo1, Servo steer_servo2, double *Pos)
  {
  double temp_pos = *Pos;
  temp_pos -= 10;     //1 step is -10 degrees
  if (temp_pos <= 20) temp_pos = 20;

   Pos = temp_pos;


  steer_servo1.write(temp_pos);
  steer_servo2.write(temp_pos);
  //    delay(10);
  }

  void ServoSteeringCenter(Servo steer_servo1, Servo steer_servo2, double *Pos) {
   Pos = initPos;
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

  void ArmControlUp(Servo arm_servo, double *arm_position) {

   arm_position -= 2;

  if (*arm_position < ARM_STOP_UP) *arm_position = ARM_STOP_UP;
  arm_servo.write(*arm_position);
  delay(10);
  }

  void ArmControlUp_Liang(Servo arm_servo, double *arm_position) {

   arm_position += 2;

  if (*arm_position > 170) *arm_position = 170;
  arm_servo.write(*arm_position);
  delay(10);
  }

  void ArmControlDown(Servo arm_servo, double *arm_position) {
   arm_position += 2;

  if ((*arm_position) > ARM_STOP_DOWN) *arm_position = ARM_STOP_DOWN;
  arm_servo.write(*arm_position);
  delay(10);

  }

  void ArmControlDown_Liang(Servo arm_servo, double *arm_position) {
   arm_position -= 2;

  if ((*arm_position) < 110) *arm_position = 110;
  arm_servo.write(*arm_position);
  delay(10);

  }
  void HandControlClose(Servo hand_servo, double *hand_angle) {

   hand_angle += 2;

  if (*hand_angle > HAND_FULL_CLOSE) *hand_angle = HAND_FULL_CLOSE;


  hand_servo.write(*hand_angle);
  delay(10);
  }

  void HandControlOpen(Servo hand_servo, double *hand_angle) {

   hand_angle -= 2;

  if (*hand_angle < HAND_FULL_OPEN) *hand_angle = HAND_FULL_OPEN;

  hand_servo.write(*hand_angle);
  delay(10);
  }

  void LeftWheelForward() {
  digitalWrite(MOTOR1P, HIGH);
  digitalWrite(MOTOR1M, LOW);
  }
*/
void LeftWheelForward_SpeedControl(int SpeedSet) {
  digitalWrite(MOTOR1P, HIGH);
  //digitalWrite(MOTOR1M, LOW);
  int PWMvalue = 255 - SpeedSet;
  analogWrite(MOTOR1M, PWMvalue);   //Since the PWM is on negative pin, so the opposite value should be calculated
}


void LeftWheelBackward() {
  digitalWrite(MOTOR1P, LOW);
  digitalWrite(MOTOR1M, HIGH);
}

void LeftWheelBackward_SpeedControl(int SpeedSet) {
  digitalWrite(MOTOR1P, LOW);
  //digitalWrite(MOTOR1M, HIGH);
  analogWrite(MOTOR1M, SpeedSet);
}

void RightWheelForward() {
  digitalWrite(MOTOR2P, HIGH);
  digitalWrite(MOTOR2M, LOW);
}

void RightWheelForward_SpeedControl(int SpeedSet) {
  digitalWrite(MOTOR2P, HIGH);
  //digitalWrite(MOTOR2M, LOW);
  int PWMvalue = 255 - SpeedSet;
  analogWrite(MOTOR2M, PWMvalue);   //Since the PWM is on negative pin, so the opposite value should be calculated
}

void RightWheelBackward() {
  digitalWrite(MOTOR2P, LOW);
  digitalWrite(MOTOR2M, HIGH);
}

void RightWheelBackward_SpeedControl(int SpeedSet) {
  digitalWrite(MOTOR2P, LOW);
  //digitalWrite(MOTOR2M, HIGH);
  analogWrite(MOTOR2M, SpeedSet);
}

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

/*
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
     bullet_left = 6;
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
        tone(SpeakerPIN, NOTE[*bullet_left], noteDuration);
        pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
        noTone(SpeakerPIN);
      }

      (*bullet_left)--;
      Serial.print("Bullet No.At this moment is :");
      Serial.println(*bullet_left);
    }
  }

  int eepromAddr = eeAddr_RUBERBAND_LOADER;
  EEPROM.put(eepromAddr, RubberbandLoaderAngles);


  TuningStatus = 0;
   bullet_left = 6;
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
     battery_left = batteryNumber;
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
  if (IRSensorValue < 900) {

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

  void HammerKnock(int targetSensorPin, Servo hammer_servo) {
  int IRSensorValue = analogRead(targetSensorPin);

  if ( (millis() - startTimeKnock) > 200 ) {         //This is to set the interval time between a hammer knock position and its initial position. The interval time should be longer than 200ms.
    if (IRSensorValue < 700) {                       //When a target is seen, the hammer begins to knock. The hammer's knocking and retoring interval time is no shorter than 200ms.
      if (hammerState == LOW) {
        hammer_servo.write(60);
        hammerState = HIGH;
      }
      else if (hammerState == HIGH) {
        hammer_servo.write(hammer_initPos);
        hammerState = LOW;
      }
      startTimeKnock = millis();
    }
    else {                                      //When no target is seen, the hammer restore to its initial position.
      hammer_servo.write(hammer_initPos);
      hammerState = LOW;
    }
  }
  }

  void LEDFlash() {
  if ( (millis() - startTimeLeft) > 50 ) {
    if (flash_times < 10) {                //The LED flashes for 10 times.
      if (leftLEDLastState == LOW)  {
        digitalWrite(LED_left, HIGH);
        leftLEDLastState = HIGH;
      }
      else if (leftLEDLastState == HIGH)  {
        digitalWrite(LED_left, LOW);
        leftLEDLastState = LOW;
      }
      flash_times += 1;
      startTimeLeft = millis();
    }
    else {                            //When the LED finishes flashing 10 times, it reset the LEDFlashState to false meaning no LED is flashing.
      LEDFlashState = false;          //After flashing 10(user can set this value, the LED stops flashing.
      digitalWrite(LED_left, LOW);
      leftLEDLastState = LOW;
    }
  }
  }


  void checkIfAttacked(int *number_of_attacked, int AttackedSensor, int max_attacked_times) {
  lastAttackedSensorState = AttackedSensorState;
  AttackedSensorState = digitalState(AttackedSensor);

  if (AttackedSensorState == LOW && lastAttackedSensorState == HIGH) {     //Only that the button is pushed(a high to low transition is found) means a valid attack
    if ( (millis() - startTimeAttacked) > 500 ) {                         //Set the interval time of two successive attack to be more than 500ms
      flash_times = 0;                                                    //When a button is pushed(high-->low transition found), the LED begin to flash 10 times which is defined in LEDFlash() function.
      LEDFlashState = true;                                               //The flash_times is refreshed when a new high-->low transition is found. The flag is set to true;
      (*number_of_attacked) += 1;
    }
    startTimeAttacked = millis();
  }
  if (LEDFlashState)
    LEDFlash();


  Serial.print("Attacked numver : ");
  Serial.println((*number_of_attacked));
  if ((*number_of_attacked) >= max_attacked_times) {
    leftLightOff();
    reset_this_CPU(); //***闁荤姴鎼崯鍧楀春閿燂拷0x0000闂侀潻闄勫妯侯焽閸愵喖绠伴柛銉墯鐎氭盯鏌ㄥ☉妯侯殭缂佲�冲暟娴滃憡娼忛妸蟺锕�顭跨捄铏剐＄紓宥忔嫹
  }
  }

*/



