#pragma once

#include <Arduino.h>
#include <Pushbutton.h>
#include <QTRSensors.h>
#include <ZumoBuzzer.h>
#include <ZumoMotors.h>
#include <ZumoReflectanceSensorArray.h>
#include <PS2.h>
#include <UltrasonicSensor.h>
#include <ZeroRGBLED.h>
//#include <ZeroRGBLED.h>
#include <EEPROM.h>


#define EEPROM_PROG_IDX_ADDRESS 0
#define DSL  										11
#define DSR  										13
#define RGB_NUM									12
#define RGB_PIN									2



//EEPROM data

// Absolute min and max eeprom addresses. Actual values are hardware-dependent.
// These values can be changed e.g. to protect eeprom cells outside this range.
const int EEPROM_MIN_ADDR = 0;
const int EEPROM_MAX_ADDR = 1023;


#define EEPROM_IF_HAVECAL_CHECK1 0xCD
#define EEPROM_IF_HAVECAL_CHECK2 0xAB
#define EEPROM_CAL_START 0xAB
#define EEPROM_CAL_MID 0xCD
#define EEPROM_CAL_END 0xEF

#define EEPROM_START_POS        100
#define STORE_START_ADDR        EEPROM_START_POS + 2      //PID CHECK
#define STORE_REV_ADDR          STORE_START_ADDR + 1      //start data

#define STORE_RGB_PIN_ADDR      STORE_REV_ADDR      +1
#define STORE_DSL_PIN_ADDR      STORE_RGB_PIN_ADDR      +1
#define STORE_DSR_PIN_ADDR      STORE_DSL_PIN_ADDR  +1

#define STORE_DIRLP_PIN_ADDR    STORE_DSR_PIN_ADDR +1
#define STORE_DIRLN_PIN_ADDR    STORE_DIRLP_PIN_ADDR +1
#define STORE_DIRRP_PIN_ADDR    STORE_DIRLN_PIN_ADDR +1
#define STORE_DIRRN_PIN_ADDR    STORE_DIRRP_PIN_ADDR +1



#define STORE_S0_PIN_ADDR       STORE_DIRRN_PIN_ADDR		 + 1
#define STORE_S1_PIN_ADDR       STORE_S1_PIN_ADDR  + 1
#define STORE_S2_PIN_ADDR       STORE_S2_PIN_ADDR  + 1 
#define STORE_S3_PIN_ADDR       STORE_S3_PIN_ADDR  + 1 
#define STORE_S4_PIN_ADDR       STORE_S4_PIN_ADDR  + 1 
#define STORE_S5_PIN_ADDR       STORE_S5_PIN_ADDR  + 1 
#define STORE_S6_PIN_ADDR       STORE_S6_PIN_ADDR  + 1 


#define STORE_MID_ADDR              STORE_S6_PIN_ADDR + 1      // 

#define STORE_S0_MAX_ADDR       STORE_MID_ADDR +1
#define STORE_S1_MAX_ADDR       STORE_S0_MAX_ADDR + 2
#define STORE_S2_MAX_ADDR       STORE_S1_MAX_ADDR + 2
#define STORE_S3_MAX_ADDR       STORE_S2_MAX_ADDR + 2
#define STORE_S4_MAX_ADDR       STORE_S3_MAX_ADDR + 2
#define STORE_S5_MAX_ADDR       STORE_S4_MAX_ADDR + 2
#define STORE_S6_MAX_ADDR       STORE_S5_MAX_ADDR + 2


#define STORE_S0_MIN_ADDR       STORE_S6_MAX_ADDR + 2
#define STORE_S1_MIN_ADDR       STORE_S0_MIN_ADDR + 2
#define STORE_S2_MIN_ADDR       STORE_S1_MIN_ADDR + 2
#define STORE_S3_MIN_ADDR       STORE_S2_MIN_ADDR + 2
#define STORE_S4_MIN_ADDR       STORE_S3_MIN_ADDR + 2
#define STORE_S5_MIN_ADDR       STORE_S4_MIN_ADDR + 2
#define STORE_S6_MIN_ADDR       STORE_S5_MIN_ADDR + 2

#define STORE_END_ADDR          STORE_S6_MIN_ADDR + 2      

//For Sumo
const char charge_sound_effect[] PROGMEM = "O4 T100 V15 L4 MS g12>c12>e12>G6>E12 ML>G2"; // "charge" melody - use V0 to suppress sound effect; v15 for max volume
//const char bump_sound_effect[] PROGMEM = "O4 T100 V15 L4 g16<g2"; // "bump" sound
const char edge_sound_effect[] PROGMEM = "O4 T100 V15 L4 g12>c12"; // "edge" sound
const char hunt_sound_effect[] PROGMEM = "O4 T100 V15 L4 g12"; // "hunt" sound
const char target_sound_effect[] PROGMEM = "O4 T100 V15 L4 >E12"; // "target" sound
const char attack_sound_effect[] PROGMEM = "O4 T100 V15 L4 ML>G2"; // "attack" sound


	
	
// Command Queue
#define MAX_COMMANDS 10
	
// Finite State Machine Setup
//  States
enum State {
  SURVIVE, HUNT, TARGET, ATTACK//, EVADE
};


enum Move {
	FORWARD,FORWARD_LEFT,LEFT,FORWARD_RIGHT,RIGHT,LEFT_BACK,BACKWARD,RIGHT_BACK,STOP	
};


typedef struct
{
  int pin;
  long max_value;
  long min_value;  
}LINESENSOR_TYPE;



typedef struct
{
  uint8_t start_data;
  uint8_t rev;
 
  uint8_t RGB_pin;
  uint8_t DSL_pin;
  uint8_t DSR_pin;
  
  uint8_t DIR_LP_pin;
  uint8_t DIR_LN_pin;
  uint8_t DIR_RP_pin;
  uint8_t DIR_RN_pin;
	
	uint8_t S0_pin;
	uint8_t S1_pin;
	uint8_t S2_pin;
	uint8_t S3_pin;
	uint8_t S4_pin;
	uint8_t S5_pin;
	uint8_t S6_pin;

	uint8_t mid_data;


	uint16_t S0_minval;
	uint16_t S1_minval;
	uint16_t S2_minval;
	uint16_t S3_minval;
	uint16_t S4_minval;
	uint16_t S5_minval;
	uint16_t S6_minval;

	uint16_t S0_maxval;
	uint16_t S1_maxval;
	uint16_t S2_maxval;
	uint16_t S3_maxval;
	uint16_t S4_maxval;
	uint16_t S5_maxval;
	uint16_t S6_maxval;

	uint8_t end_data;
}EEPROM_TYPE;

class Beatle
{
public:

  Beatle();
  // path[] keeps a log of all the turns made
	// since starting the maze
	char maze_path[100] ;//= "";
	unsigned char maze_path_length = 0; // the length of the path

  int DEBUG;

  int ProgramSelector;
  
  void StartProgram();
  
 
 
	ZumoBuzzer buzzer;
	ZumoReflectanceSensorArray LineSensors;
	ZumoMotors motors;
	Pushbutton button= Pushbutton(ZUMO_BUTTON);	
	ZeroRGBLED led;
	
  
  void SetupAll(int idx= 0);
  void LoopAll(int idx= 0);  
  void Setup_FollowLine();
	void Loop_FollowLine();
	void Setup_MazeSolver();
	void Loop_MazeSolver();
	void Setup_BorderDetect();
	void Loop_BorderDetect();
	void Setup_AvoidObstacle();
	void Loop_AvoidObstacle();
	void Setup_RemoteControl();
	void Loop_RemoteControl();
	void Setup_Sumo();
	void Loop_Sumo();
	void Setup_Wandering();
	void Loop_Wandering();
	
	void QTRC_ReadRawValue();
	
	void SetMaxSpeed(int speed);
	void SetTurnSpeed(int speed);
	void SetSpeed(int speed);
	void SetForwardSpeed(int speed);
	void SetReverseSpeed(int speed);
	void SetAttackSpeed(int speed);
	
	void SetReverseDuration(int duration);
	void SetTurnDuration(int duration);
	void SetHuntDuration(int duration);
	
	void SetSensorThreshold(int threshold);
	
	void SetPID(double kp,double ki,double kd);
	
	void waitForButtonAndCountDown(); //Used in Border detect
	
	void setDefaultvalue(void);
	
	void FloatToEEPROM(int address,int num,float *f);
	void IntToEEPROM(int address,int num, uint16_t *data);
	void ByteToEEPROM(int address,int num, uint8_t *data);
	boolean eeprom_is_addr_ok(int addr); 
	boolean eeprom_write_bytes(int startAddr, const byte* array, int numBytes) ;
	boolean eeprom_write_string(int addr, const char* string) ;
	boolean eeprom_read_string(int addr, char* buffer, int bufSize) ;
	void clearEEPROM(void);
	void writetoEEPROM(void);
	boolean readEEPROM(void);
	void updatefromBackuparea(void);
	
	
	void LineSenorCalibation();
	void readCalibrationData();
	void writeCalibrationData();  
	void writeCalibrationData(unsigned int Max[],unsigned int Min[]) ;     
	void LineSensorCalibration(boolean status = true,int  speed = 128,int delay = 20);

	
	void turn(char dir);
	char selectTurn(unsigned char found_left, unsigned char found_straight,
  unsigned char found_right);
  void followSegment();
  void followSegmentStopIntersection();
  void solveMaze();
  void goToFinishLine();
  void goToTarget();
  void simplifymaze_path();
  
  boolean IsSensorCalibrated();
  void SetCalibrationFlag(int flag);
	void setDebugLevel(int idx);
	
  State state;
  
  Move  move_state;

private:
	
	
	boolean CalibrationFlag = true;
	
	unsigned long time_start;
	unsigned long time_start_maze;
	unsigned long time_start_led = millis();

	unsigned long startTime = millis();   // the time in milliseconds that the command queue started executingCommands
	unsigned long nextCommand = millis(); // the time that the queue should execute the next command
	unsigned int commandIndex;
	unsigned int numberOfCommands;
	int leftSpeed[MAX_COMMANDS];
	int rightSpeed[MAX_COMMANDS];
	unsigned int commandDuration[MAX_COMMANDS];
	unsigned int turnDirection = 1;
	//  Events
  bool opponentDetected;
  bool edgeDetected;
  //bool inContact;
  bool executingCommands;
  
  EEPROM_TYPE encoder_eeprom;
  LINESENSOR_TYPE  qtrc_data[7];

	
	int 	REVERSE_SPEED   =  128;// 0 is stopped, 400 is full speed
	int 	TURN_SPEED      =  128;
	int 	FORWARD_SPEED   =  128;
	int 	SPEED           =  128;
	int 	MAX_SPEED       =  128;
	int 	ATTACK_SPEED 		=  255;
	
	int 	REVERSE_DURATION=  200; // ms  //for border detect
	int 	TURN_DURATION   =  300; // ms  /for border detect
	
	double _Kp = 1.0/8.0;
	double _Kd = 6.0;
	double _Ki = 0;

	
//	int   REVERSE_DURATION= 250;
//	int   TURN_DURATION		= 500;
	int   HUNT_DURATION   = 1000;
	



	// SENSOR_THRESHOLD is a value to compare reflectance sensor
	// readings to to decide if the sensor is over a black line
	int  SENSOR_THRESHOLD =   300;


	// ABOVE_LINE is a helper macro that takes returns
	// 1 if the sensor is over the line and 0 if otherwise	
	int ABOVE_LINE(int value);
	
	
	
	int lastError = 0;
	
	
	int AT_END_POINT = 0;
	

	unsigned int sensor_values[7];
	void updateFromSensors();
	void checkStateTransition();
	void survive();
 	void hunt();
 	void target();
 	void attack();
 	void clearCommands();
 	void startExecutingCommands();
 	void addCommand(int left, int right, int duration);
 	void executeCommands();
 	
 	
};