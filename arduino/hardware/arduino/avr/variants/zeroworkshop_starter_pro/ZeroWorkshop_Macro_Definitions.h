#ifndef   _MACRO_DEFINITION_H_   
#define   _MACRO_DEFINITION_H_ 

#define POSITIVE 1
#define NEGATIVE -1
#define DEBUG 0

#define LEFT_IR_SENSOR   ZW_A1
#define RIGHT_IR_SENSOR  ZW_A2
#define Threshold        400

#define COLOR1_START_POS   900  //
#define COLOR_LENGTH       10   //sizeof(RGB_type)

#define  COLOR_TOLERANCE              3
#define  COLOR_TOLERANCE_MAX          30
     //！
#define  COLOR_CALIBRATION_TIMES      10 //！
//bool  CALIBRATION_COLOR =          false ;


//enum color_type
//{
// NOTHING =0,RED=1,ORANGE=2,YELLOW=3,GREEN=4,BLUE=5,PURPLE=6,PINK=7,INVALID=8
//};



//#define LEVEL1       

//#define LEVEL1       
//#define LEVEL1_REVB  
//#define LEVEL4        //use Kim Level4 board with 328p chip
//#define ROBOTCOM_REVA

extern int Rx_Buffer[6];  

/****************************************************************/
/*******  PIN DEFINITION FOR LEVEL1 CPU BOARD *******************/
/****************************************************************/
/*
#ifdef  LEVEL1        //Pins below are for Kim level 1
#define ZW_A1 A1
#define ZW_A2 A2
#define ZW_A3 A6
#define ZW_A4 A7

#define ZW_B1 8
#define ZW_B2 10
#define ZW_B3 11
#define ZW_B4 A3

#define MOTOR1P 4
#define MOTOR1M 5
#define MOTOR2P 7
#define MOTOR2M 6
#define MOTOR3P 0
#define MOTOR3M 0
#define MOTOR4P 0
#define MOTOR4M 0

#define START_BUTTON A0
#define ENA     0
#define ENB     0     //dummy defintions

#define INPUT_VALUE_BT1 !digitalRead(BT1)
#define INPUT_VALUE_BT2 !digitalRead(BT2)
#define INPUT_VALUE_BT3 analogRead(BT3)<10
#define INPUT_VALUE_BT4 analogRead(BT4)<10

#define BuzzerPin  9
#define SpeakerPIN 9

#define IR_IN1   A2
#define IR_IN2   A3
#define IR_IN3   A4
#define IR_IN4   A5

#define LED_A2   6
#define LED_A3   7
#define LED_9    4
#endif
*/
/****************************************************************/
/*******  END OF PIN DEFINITION FOR LEVEL1 CPU BOARD ************/
/****************************************************************/


/****************************************************************/
/******  PIN DEFINITION FOR LEVEL1_REVB with I2C CPU BOARD ******/
/****************************************************************/
/*
#ifdef  LEVEL1_REVB        //Pins below are for Kim level 1
#define ZW_A1 A0
#define ZW_A2 A1
#define ZW_A3 A2
#define ZW_A4 A3

#define ZW_B1 8
#define ZW_B2 10
#define ZW_B3 11
#define ZW_B4 12

#define MOTOR1P 4
#define MOTOR1M 5
#define MOTOR2P 7
#define MOTOR2M 6
#define MOTOR3P 0
#define MOTOR3M 0
#define MOTOR4P 0
#define MOTOR4M 0



#define Left_Fist_SERVO  ZW_B2
#define Right_Fist_SERVO  ZW_B1


#define Carriage_SERVO  ZW_B1

#define START_BUTTON 2
#define ENA     0
#define ENB     0     //dummy defintions

#define INPUT_VALUE_BT1 !digitalRead(BT1)
#define INPUT_VALUE_BT2 !digitalRead(BT2)
#define INPUT_VALUE_BT3 !digitalRead(BT3)
#define INPUT_VALUE_BT4 !digitalRead(BT4)

#define BuzzerPin  9
#define SpeakerPIN 9

#define IR_IN1   A0
#define IR_IN2   A1
#define IR_IN3   A2
#define IR_IN4   A3

#define LED_A2   6
#define LED_A3   7
#define LED_9    4
#endif
*/
/****************************************************************/
/*******  END OF PIN DEFINITION FOR LEVEL1 CPU BOARD ************/
/****************************************************************/

/****************************************************************/
/******  PIN DEFINITION FOR ROBOTCOM_REVA with I2C CPU BOARD ******/
/****************************************************************/
/*
#ifdef  ROBOTCOM_REVA       //Pins below are for Kim level 1
#define ZW_A1 A0
#define ZW_A2 A1
#define ZW_A3 A4
#define ZW_A4 A5

#define Main_SERVO 	ZW_B1
#define Throw_SERVO ZW_B2

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
*/
/****************************************************************/
/*****  END OF PIN DEFINITION FOR ROBOTCOM_REVA CPU BOARD *******/
/****************************************************************/



/****************************************************************/
/*******  PIN DEFINITION FOR LEVEL4 CPU BOARD *******************/
/****************************************************************/
/*
#ifdef LEVEL4         //Pins below are for Kim level 4
#define START_BUTTON A0
#define ENA     0
#define ENB     0     //dummy defintions

#define ZW_A1 A2
#define ZW_A2 A3
#define ZW_A3 A4
#define ZW_A4 A5

#define ZW_B1 4
#define ZW_B2 5
#define ZW_B3 6
#define ZW_B4 7

#define MOTOR1P 3
#define MOTOR1M A1
#define MOTOR2P 13
#define MOTOR2M 12
#define MOTOR3P 8
#define MOTOR3M 2
#define MOTOR4P 11
#define MOTOR4M 10

#define SP 9    //speaker
#define BuzzerPin 9
#define SpeakerPIN 9

#define IR_IN1   A2
#define IR_IN2   A3
#define IR_IN3   A4
#define IR_IN4   A5

#define LED_A2   6
#define LED_A3   7
#define LED_9    4

#define LED_left    A3
#define LED_right   A0
#endif
*/
/****************************************************************/
/*******  END OF PIN DEFINITION FOR LEVEL1 CPU BOARD ************/
/****************************************************************/


#define portOfPin(P)\
  (((P)>=0&&(P)<8)?&PORTD:(((P)>7&&(P)<14)?&PORTB:&PORTC))
#define ddrOfPin(P)\
  (((P)>=0&&(P)<8)?&DDRD:(((P)>7&&(P)<14)?&DDRB:&DDRC))
#define pinOfPin(P)\
  (((P)>=0&&(P)<8)?&PIND:(((P)>7&&(P)<14)?&PINB:&PINC))
#define pinIndex(P)((uint8_t)(P>13?P-14:P&7))
#define pinMask(P)((uint8_t)(1<<pinIndex(P)))

#define pinAsInput(P) *(ddrOfPin(P))&=~pinMask(P)
#define pinAsInputPullUp(P) *(ddrOfPin(P))&=~pinMask(P);digitalHigh(P)
#define pinAsOutput(P) *(ddrOfPin(P))|=pinMask(P)
#define digitalLow(P) *(portOfPin(P))&=~pinMask(P)
#define digitalHigh(P) *(portOfPin(P))|=pinMask(P)
#define isHigh(P)((*(pinOfPin(P))& pinMask(P))>0)
#define isLow(P)((*(pinOfPin(P))& pinMask(P))==0)
#define digitalState(P)((uint8_t)isHigh(P))



#define L1 2
#define L2 3
#define L3 A0
#define L4 13
#define R1 A4
#define R2 A3
#define R3 A2
#define R4 A1

#define FORWARD    		0
#define BACKWARD    	1
#define STOP    			2




#define BT1 										ZW_A1
#define BT2 										ZW_A2
#define BT3 										ZW_A3
#define BT4 										ZW_A4 

#define LED_left    						ZW_B3
#define LED_right   						ZW_B4

#define LED_b1 									ZW_B4
#define LED_b2 									ZW_B3

#define FTAIL_SERVO 						ZW_B1

#define ARM_SERVO  							ZW_B2
#define HAND_SERVO 							ZW_B1

#define FRADAR_SERVO 						ZW_B1

#define LAMP_SERVO 							ZW_B1
#define CHASSIS_SERVO 					ZW_B2

#define FIRE_SERVO 							ZW_B1


#define CAT_HAND_SERVO 					ZW_B1

#define bulletTRIGGER_SERVO 		ZW_B1
#define bulletLOADER_SERVO  		ZW_B2

#define batteryTRIGGER_SERVO 		ZW_B1
#define batteryLOADER_SERVO  		ZW_B2

#define fanHeadHORIZONTAL_SERVO ZW_B1
#define fanHeadVERTICAL_SERVO   ZW_B2

#define paw_B1_SERVO     ZW_B1
#define paw_B2_SERVO     ZW_B2

#define handlebar_B1_SERVO     ZW_B1

#define shovel_B2_SERVO     ZW_B2
#define arm_B1_SERVO     ZW_B1

#define BASKET_SERVO      			ZW_B1
#define BALL_SENSOR       			ZW_A2

#define CAT_MOUTH_SENSORPIN 		ZW_A1
#define CAT_HEAD_SENSORPIN  		ZW_A2



#define RADAR1_SENSORPIN 				ZW_A1
#define RADAR2_SENSORPIN 				ZW_A2

#define RAPTORHEAD_SERVO       	ZW_B1
#define RAPTORHEAD_SENSORPIN   	ZW_A1

#define TARGET_SENSORPIN       	ZW_A4
#define HAMMER_SERVO           	ZW_B1
#define ATTACKED_SENSORPIN     	ZW_A1
#define LEFT_WHEEL_BUTTON      	ZW_A2
#define RIGHT_WHEEL_BUTTON     	ZW_A1
#define BACKWARD_BUTTON        	ZW_B4


#define B1_SERVO           			ZW_B1
#define B2_SERVO           			ZW_B2
#define B3_SERVO           			ZW_B3
#define B4_SERVO           			ZW_B4



#define LEFT_SENSOR   					ZW_A1
#define RIGHT_SENSOR  					ZW_A2
#define NOSE_BUTTON   					ZW_A3
#define TAIL_SERVO    					ZW_B3
#define LEFT_LED      					ZW_B1
#define RIGHT_LED     					ZW_B2


/****************************************************************/
/****************  PS2 REMOTE CONTROL DATA **********************/
/****************************************************************/
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


/****************************************************************/
/****************  PS2 REMOTE CONTROL DATA **********************/
/****************  USING SERIAL EVENT ***************************/
/****************************************************************/
#define _ButtonUp        (0x10 & Rx_Buffer[2])
#define _ButtonRight     (0x20 & Rx_Buffer[2])
#define _ButtonDown      (0x40 & Rx_Buffer[2])
#define _ButtonLeft      (0x80 & Rx_Buffer[2])
#define _ButtonTriangle  (0x10 & Rx_Buffer[3])
#define _ButtonCircle    (0x20 & Rx_Buffer[3])
#define _ButtonCross     (0x40 & Rx_Buffer[3])
#define _ButtonSquare    (0x80 & Rx_Buffer[3])
#define _ButtonL1        (0x4 & Rx_Buffer[3])
#define _ButtonL2        (0x1 & Rx_Buffer[3])
#define _ButtonR1        (0x8 & Rx_Buffer[3])
#define _ButtonR2        (0x2 & Rx_Buffer[3])
#define _ButtonSelect    (0x1 & Rx_Buffer[2])
#define _ButtonStart     (0x8 & Rx_Buffer[2])

/****************************************************************/
/****************  PS2 KEY VALUE **********************/
/****************************************************************/
#define PS2_UP        0x10 
#define PS2_RIGHT     0x20 
#define PS2_DOWN      0x40 
#define PS2_LEFT      0x80 
#define PS2_TRIANGLE  0x10 
#define PS2_CIRCLE    0x20 
#define PS2_CROSS     0x40 
#define PS2_SQUARE    0x80 
#define PS2_L1        0x4 
#define PS2_L2        0x1 
#define PS2_R1        0x8 
#define PS2_R2        0x2 
#define PS2_SELECT    0x1 
#define PS2_START     0x8 

/****************************************************************/
/**********************  DEFINITIONS FOR SOUND*******************/
/****************************************************************/

#define a0   28
#define as0  29
#define b0   31
#define c1   33
#define cs1  35
#define d1   37
#define ds1  39
#define e1   41
#define f1   44
#define fs1  46
#define g1   49
#define gs1  52
#define a1   55
#define as1  58
#define b1   62
#define c2   65
#define cs2  69
#define d2   73
#define ds2  78
#define e2   82
#define f2   87
#define fs2  93
#define g2   98
#define gs2  104
#define a2   110
#define as2  117
#define b2   123
#define c3   131
#define cs3  139
#define d3   147
#define ds3  156
#define e3   165
#define f3   175
#define fs3  185
#define g3   196
#define gs3  208
#define a3   220
#define as3  233
#define b3   247
#define c4   262
#define cs4  277
#define d4   294
#define ds4  311
#define e4   330
#define f4   349
#define fs4  370
#define g4   392
#define gs4  415
#define a4   440
#define as4  466
#define b4   494
#define c5   523
#define cs5  554
#define d5   587
#define ds5  622
#define e5   659
#define f5   698
#define fs5  740
#define g5   784
#define gs5  831
#define a5   880
#define as5  932
#define b5   988
#define c6   1047
#define cs6  1109
#define d6   1175
#define ds6  1245
#define e6   1319
#define f6   1397
#define fs6  1480
#define g6   1568
#define gs6  1661
#define a6   1760
#define as6  1865
#define b6   1976
#define c7   2093
#define cs7  2217
#define d7   2349
#define ds7  2489
#define e7   2637
#define f7   2794
#define fs7  2960
#define g7   3136
#define gs7  3322
#define a7   3520
#define as7  3729
#define b7   3951
#define c8   4186
#define cs8  4435
#define d8   4699
#define ds8  4978

#define NOTE_A0  a0   
#define NOTE_AS0 as0  
#define NOTE_B0  b0   
#define NOTE_C1  c1   
#define NOTE_CS1 cs1  
#define NOTE_D1  d1   
#define NOTE_DS1 ds1  
#define NOTE_E1  e1   
#define NOTE_F1  f1   
#define NOTE_FS1 fs1  
#define NOTE_G1  g1   
#define NOTE_GS1 gs1  
#define NOTE_A1  a1   
#define NOTE_AS1 as1  
#define NOTE_B1  b1   
#define NOTE_C2  c2   
#define NOTE_CS2 cs2  
#define NOTE_D2  d2   
#define NOTE_DS2 ds2  
#define NOTE_E2  e2   
#define NOTE_F2  f2   
#define NOTE_FS2 fs2  
#define NOTE_G2  g2   
#define NOTE_GS2 gs2  
#define NOTE_A2  a2   
#define NOTE_AS2 as2  
#define NOTE_B2  b2   
#define NOTE_C3  c3   
#define NOTE_CS3 cs3  
#define NOTE_D3  d3   
#define NOTE_DS3 ds3  
#define NOTE_E3  e3   
#define NOTE_F3  f3   
#define NOTE_FS3 fs3  
#define NOTE_G3  g3   
#define NOTE_GS3 gs3  
#define NOTE_A3  a3   
#define NOTE_AS3 as3  
#define NOTE_B3  b3   
#define NOTE_C4  c4   
#define NOTE_CS4 cs4  
#define NOTE_D4  d4   
#define NOTE_DS4 ds4  
#define NOTE_E4  e4   
#define NOTE_F4  f4   
#define NOTE_FS4 fs4  
#define NOTE_G4  g4   
#define NOTE_GS4 gs4  
#define NOTE_A4  a4   
#define NOTE_AS4 as4  
#define NOTE_B4  b4   
#define NOTE_C5  c5   
#define NOTE_CS5 cs5  
#define NOTE_D5  d5   
#define NOTE_DS5 ds5  
#define NOTE_E5  e5   
#define NOTE_F5  f5   
#define NOTE_FS5 fs5  
#define NOTE_G5  g5   
#define NOTE_GS5 gs5  
#define NOTE_A5  a5   
#define NOTE_AS5 as5  
#define NOTE_B5  b5   
#define NOTE_C6  c6   
#define NOTE_CS6 cs6  
#define NOTE_D6  d6   
#define NOTE_DS6 ds6  
#define NOTE_E6  e6   
#define NOTE_F6  f6   
#define NOTE_FS6 fs6  
#define NOTE_G6  g6   
#define NOTE_GS6 gs6  
#define NOTE_A6  a6   
#define NOTE_AS6 as6  
#define NOTE_B6  b6   
#define NOTE_C7  c7   
#define NOTE_CS7 cs7  
#define NOTE_D7  d7   
#define NOTE_DS7 ds7  
#define NOTE_E7  e7   
#define NOTE_F7  f7   
#define NOTE_FS7 fs7  
#define NOTE_G7  g7   
#define NOTE_GS7 gs7  
#define NOTE_A7  a7   
#define NOTE_AS7 as7  
#define NOTE_B7  b7   
#define NOTE_C8  c8   
#define NOTE_CS8 cs8  
#define NOTE_D8  d8   
#define NOTE_DS8 ds8  


#define wholeNote       4000*0.5
#define halfNote        2000*0.5
#define quaterNote      1000*0.5
#define eighthNote      500*0.5
#define sixteenthNote   250*0.5

#define meters_x1       1
#define meters_x2       2
#define meters_x3       3
#define meters_x4       4
#define meters_x5       5
#define meters_x6       6
#define meters_x7       7
#define meters_x8       8

#define SONG_1          1
#define SONG_2          2
#define SONG_3          3
#define SONG_4          4
#define SONG_5          5
/****************************************************************/
/***************** ** END OF  NOTE PERIOD ***********************/
/****************************************************************/


#define initPos         90    //to define a initial degree of servo

#define TAIL_STOP_UP     110
#define TAIL_STOP_DOWN   45


#define RADAR_INIT   0

#define radar_initPos  RADAR_INIT


#define LAMP_INIT   1

#define lamp_initPos  LAMP_INIT

#define lamp_initPos_new  90


#define FIRE_INIT   90

#define fire_initPos  FIRE_INIT

#define Main_initPos  90
#define initTailPos  90

#define Left_initPos  0
#define Right_initPos  180


#define Carriage_initPos  25

#define Throw_initPos  90


#define tail_initPos  TAIL_STOP_DOWN

#define ARM_STOP_UP     180
#define ARM_STOP_DOWN   0
#define HAND_FULL_CLOSE 75
#define HAND_FULL_OPEN  10

#define arm_initPos  			ARM_STOP_UP
#define hand_initPos 			HAND_FULL_OPEN
#define loader_initPos   	70
#define trigger_initPos  	170
#define bulletNumber     	6

#define eeAddr_RUBERBAND_LOADER 				0           //define the EEPROM start address from where the servo position is saved

#define eeAddr_LEVEL1_DEFAULT_PROG     100      //define the EEPROM start address from where the default prog(last time selected) number is saved

#define fanHeadHori_initPos  90
#define fanHeadVerti_initPos 90



#define spinFAST   1
#define spinMEDIUM 2
#define spinSLOW   3


#define UP       1
#define CENTER   2
#define DOWN     3

#define LOADING_POS   30
#define STANDBY_POS   75

#define FIRING_POS   	160
#define WAITING_POS  	40

#define Batt_trigger_initPos WAITING_POS
#define Batt_loader_initPos  STANDBY_POS
#define batteryNumber     7


#define backboard_initPos 95
#define backboard_stopPos 125
#define backboard_startPos 65

#define raptorHead_initPos 90

#define hammer_initPos     0
#define TailServo_Init_Pos 90

/****************************************************************/
/******************* DEFINITIONS FOR LED ************************/
/****************************************************************/
#define PIXEL_PIN    			ZW_B2    // Digital IO pin connected to the NeoPixels.
#define PIXEL_COUNT  			12
#define FLASH_DURATION 		200
#define SLOW   						2
#define MIDDLE 						1
#define FAST   						0

#define OFF        				0
#define ON         				1
#define SCALE      				8
#define ON_WHITE_MAX   		strip.Color(255, 255, 255)
#define ON_WHITE   				strip.Color(255 / SCALE, 255 / SCALE, 255 / SCALE)

#define ON_RED_MAX     		       strip.Color( 0, 255, 0)
#define ON_GREEN_MAX 				strip.Color(255, 0 , 0)
#define ON_BLUE_MAX   				strip.Color(0, 0, 255)
#define ON_YELLOW_MAX				strip.Color(255, 255, 0)

//#define ON_RED    		        strip.Color( 0, 255 / SCALE, 0)
//#define ON_GREEN				strip.Color(255 / SCALE, 0 , 0)
//#define ON_BLUE  				strip.Color(0, 0, 255 / SCALE)
//#define ON_YELLOW				strip.Color(255 / SCALE, 255 / SCALE, 0)

//不匹配的颜色RGB值
#define ON_RED     				strip.Color(255 / SCALE, 0, 0)
#define ON_GREEN   				strip.Color(0, 255 / SCALE, 0)
#define ON_BLUE    				strip.Color(0, 0, 255 / SCALE)
#define ON_YELLOW  				strip.Color(255 / SCALE, 255 / SCALE, 0)

#define ON_CYAN    				strip.Color(0, 255 / SCALE, 255 / SCALE)
#define ON_MAGENTA 				strip.Color(255 / SCALE, 0, 255 / SCALE)
#define ON_PURPLE  				strip.Color(128 / SCALE, 0, 128 / SCALE)
#define OFF_RGB    				strip.Color(0, 0, 0)
#define STRIP1_ON_YELLOW  LED_strip1.Color(255 / SCALE, 255 / SCALE, 0)
#define STRIP1_OFF_RGB    LED_strip1.Color(0, 0, 0)
#define STRIP2_ON_GREEN   LED_strip2.Color(0, 255 / SCALE, 0)
#define STRIP2_OFF_RGB    LED_strip2.Color(0, 0, 0)
#define SWAP       1
#define UNSWAP     0

#define LED_MAX_BRIGHT   255 / SCALE

/****************************************************************/
/******************* ULTRA SONIC RELATED ************************/
/****************************************************************/
#define RADAR_SENSOR_RANGE			15


#endif

#define Main_SERVO 	ZW_B1
#define Throw_SERVO ZW_B2


#define B1_SERVO ZW_B1

#define OpenCloseinitPos  90
#define UpDowninitPos 90

#define barinitPos 90

#define shovelinitPos 90

#define arminitPos 90


// followLine
//#define PWM_L  6
//#define PWM_R  5
//#define DIR_L  12
//#define DIR_R  13
//
//#define SENSOR_THRESHOLD  200
//
//#define ABOVE_LINE(sensor)   ((sensor) >SENSOR_THRESHOLD)
//
//#define TURN_SPEED  200
//#define SPEED       200
//#define _OVERSHOOOT_     (28000/SPEED) 
//
//#define CMD_RESET         0x00
//
//#define CMD_SET_CAL_DATA  0x14
//#define CMD_SET_EMITTER   0x15
//#define CMD_SET_MAX_VAL   0x16
//#define CMD_SET_DEVID     0x17
//
//#define CMD_GET_CAL_DATA        0x24
//#define CMD_GET_POSITION_DATA        0x26
//#define CMD_GET_FINAL_DATA      0x27
//#define CMD_GET_RAW_DATA        0x28
//#define I2C_DEFAULT_ADDR        0x9
//#define _slot                   0x0
//
//#define NOTE_B0  31
//#define NOTE_C1  33
//#define NOTE_CS1 35
//#define NOTE_D1  37
//#define NOTE_DS1 39
//#define NOTE_E1  41
//#define NOTE_F1  44
//#define NOTE_FS1 46
//#define NOTE_G1  49
//#define NOTE_GS1 52
//#define NOTE_A1  55
//#define NOTE_AS1 58
//#define NOTE_B1  62
//#define NOTE_C2  65
//#define NOTE_CS2 69
//#define NOTE_D2  73
//#define NOTE_DS2 78
//#define NOTE_E2  82
//#define NOTE_F2  87
//#define NOTE_FS2 93
//#define NOTE_G2  98
//#define NOTE_GS2 104
//#define NOTE_A2  110
//#define NOTE_AS2 117
//#define NOTE_B2  123
//#define NOTE_C3  131
//#define NOTE_CS3 139
//#define NOTE_D3  147
//#define NOTE_DS3 156
//#define NOTE_E3  165
//#define NOTE_F3  175
//#define NOTE_FS3 185
//#define NOTE_G3  196
//#define NOTE_GS3 208
//#define NOTE_A3  220
//#define NOTE_AS3 233
//#define NOTE_B3  247
//#define NOTE_C4  262
//#define NOTE_CS4 277
//#define NOTE_D4  294
//#define NOTE_DS4 311
//#define NOTE_E4  330
//#define NOTE_F4  349
//#define NOTE_FS4 370
//#define NOTE_G4  392
//#define NOTE_GS4 415
//#define NOTE_A4  440
//#define NOTE_AS4 466
//#define NOTE_B4  494
//#define NOTE_C5  523
//#define NOTE_CS5 554
//#define NOTE_D5  587
//#define NOTE_DS5 622
//#define NOTE_E5  659
//#define NOTE_F5  698
//#define NOTE_FS5 740
//#define NOTE_G5  784
//#define NOTE_GS5 831
//#define NOTE_A5  880
//#define NOTE_AS5 932
//#define NOTE_B5  988
//#define NOTE_C6  1047
//#define NOTE_CS6 1109
//#define NOTE_D6  1175
//#define NOTE_DS6 1245
//#define NOTE_E6  1319
//#define NOTE_F6  1397
//#define NOTE_FS6 1480
//#define NOTE_G6  1568
//#define NOTE_GS6 1661
//#define NOTE_A6  1760
//#define NOTE_AS6 1865
//#define NOTE_B6  1976
//#define NOTE_C7  2093
//#define NOTE_CS7 2217
//#define NOTE_D7  2349
//#define NOTE_DS7 2489
//#define NOTE_E7  2637
//#define NOTE_F7  2794
//#define NOTE_FS7 2960
//#define NOTE_G7  3136
//#define NOTE_GS7 3322
//#define NOTE_A7  3520
//#define NOTE_AS7 3729
//#define NOTE_B7  3951
//#define NOTE_C8  4186
//#define NOTE_CS8 4435
//#define NOTE_D8  4699
//#define NOTE_DS8 4978
