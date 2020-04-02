#ifndef STARTERPRO_I2CSLAVE_H
#define STARTERPRO_I2CSLAVE_H



/****************************************************************/
/******  PIN DEFINITION FOR Starter Pro with I2C CPU BOARD ******/
/****************************************************************/

#define _ZW_A1_ A0
#define _ZW_A2_ A1
#define _ZW_A3_ A4
#define _ZW_A4_ A5

#define _ZW_B1_ A2
#define _ZW_B2_ A3
#define _ZW_B3_ 2
#define _ZW_B4_ 7

#define MOTOR1P 3
#define MOTOR1M 13
#define MOTOR2P 5
#define MOTOR2M 12
#define MOTOR3P 11
#define MOTOR3M 10
#define MOTOR4P 6
#define MOTOR4M 9

#define START_BUTTON 4
#define BEEP 8

// move state and function
#define CMD_RESET         0x00


// config function
#define CMD_SET_DEVID     0x01


#define CMD_SET_PIN_TYPE  0x11
#define CMD_SET_PIN_DIGITAL_VAL   0x12
#define CMD_SET_PIN_ANALOG_VAL   0x13
#define CMD_SET_MOTOR           0x14
#define CMD_SET_STEPPER           0x15
#define CMD_SET_SERVO             0x16
#define CMD_SET_STEPPER_SYNC 			0x17
#define CMD_SET_STEPPER_ZERO_PIN	0x18
#define CMD_RESET_STEPPER         0x19


// get sensor status
#define CMD_GET_PIN_TYPE         0x21
#define CMD_GET_PIN_DIGITAL_VAL  0x22
#define CMD_GET_PIN_ANALOG_VAL   0x23
#define CMD_GET_STEPPER_COUNTER  0x24
#define CMD_GET_STEPPER_ZERO_PIN 0x28
#define CMD_GET_POWER_VOL        0x29




//EEPROM data
#define EEPROM_IF_HAVECAL_CHECK1 0xCD
#define EEPROM_IF_HAVECAL_CHECK2 0xAB
#define EEPROM_CAL_START 0xAB
#define EEPROM_CAL_MID 0xCD
#define EEPROM_CAL_END 0xEF

#define EEPROM_START_POS         0
#define STORE_START_ADDR         EEPROM_START_POS + 2      //PID CHECK
#define STORE_DEVID_ADDR         STORE_START_ADDR + 1      //start data
//#define STORE_TIMEOUT_ADDR        STORE_DEVID_ADDR + 1      //dev id

#define STORE_ZW_A1_PIN_ADDR       STORE_DEVID_ADDR+2
#define STORE_ZW_A2_PIN_ADDR       STORE_ZW_A1_PIN_ADDR + 1
#define STORE_ZW_A3_PIN_ADDR       STORE_ZW_A2_PIN_ADDR + 1 
#define STORE_ZW_A4_PIN_ADDR       STORE_ZW_A3_PIN_ADDR + 1 
#define STORE_ZW_B1_PIN_ADDR       STORE_ZW_A4_PIN_ADDR + 1 
#define STORE_ZW_B2_PIN_ADDR       STORE_ZW_B1_PIN_ADDR + 1 
#define STORE_ZW_B3_PIN_ADDR       STORE_ZW_B2_PIN_ADDR + 1 
#define STORE_ZW_B4_PIN_ADDR       STORE_ZW_B3_PIN_ADDR + 1 

#define STORE_BEEP_PIN_ADDR             STORE_ZW_B4_PIN_ADDR+1
#define STORE_M1P_ADDR       STORE_BEEP_PIN_ADDR+1
#define STORE_M1N_ADDR       STORE_M1P_ADDR+1
#define STORE_M2P_ADDR       STORE_M1N_ADDR+1
#define STORE_M2N_ADDR       STORE_M2P_ADDR+1
#define STORE_M3P_ADDR       STORE_M2N_ADDR+1
#define STORE_M3N_ADDR       STORE_M3P_ADDR+1
#define STORE_M4P_ADDR       STORE_M3N_ADDR+1
#define STORE_M4N_ADDR       STORE_M4P_ADDR+1

#define STORE_MID_ADDR              STORE_M4N_ADDR + 1      // 

#define STORE_ZW_A1_TYPE_ADDR       STORE_MID_ADDR +1
#define STORE_ZW_A2_TYPE_ADDR       STORE_ZW_A1_TYPE_ADDR + 1
#define STORE_ZW_A3_TYPE_ADDR       STORE_ZW_A2_TYPE_ADDR + 1
#define STORE_ZW_A4_TYPE_ADDR       STORE_ZW_A3_TYPE_ADDR + 1
#define STORE_ZW_B1_TYPE_ADDR       STORE_ZW_A4_TYPE_ADDR + 1
#define STORE_ZW_B2_TYPE_ADDR       STORE_ZW_B1_TYPE_ADDR + 1
#define STORE_ZW_B3_TYPE_ADDR       STORE_ZW_B2_TYPE_ADDR + 1
#define STORE_ZW_B4_TYPE_ADDR       STORE_ZW_B3_TYPE_ADDR + 1


#define STORE_END_ADDR              STORE_ZW_B4_TYPE_ADDR + 1      


#define FORWARD   0
#define BACKWARD  1
#define STOP      2

typedef struct
{
  uint8_t pin;
  long value;
  uint8_t type;  // 0  =  input  1 output;
}pin_type;

typedef struct
{
  uint8_t slot;
  pin_type  ZW_A1;
  pin_type  ZW_A2;
  pin_type  ZW_A3;
  pin_type  ZW_A4;

  pin_type  ZW_B1;
  pin_type  ZW_B2;
  pin_type  ZW_B3;
  pin_type  ZW_B4;
  
  long voltage;
}pin_data_type;

typedef struct
{
  uint8_t start_data;
  uint8_t devid;
 // uint16_t timeout;

uint8_t ZW_A1_pin;
uint8_t ZW_A2_pin;
uint8_t ZW_A3_pin;
uint8_t ZW_A4_pin;
uint8_t ZW_B1_pin;
uint8_t ZW_B2_pin;
uint8_t ZW_B3_pin;
uint8_t ZW_B4_pin;

uint8_t  Beep;
uint8_t  M1P;
uint8_t  M1N;
uint8_t  M2P;
uint8_t  M2N;
uint8_t  M3P;
uint8_t  M3N;
uint8_t  M4P;
uint8_t  M4N;

uint8_t mid_data;

uint8_t ZW_A1_type;
uint8_t ZW_A2_type;
uint8_t ZW_A3_type;
uint8_t ZW_A4_type;
uint8_t ZW_B1_type;
uint8_t ZW_B2_type;
uint8_t ZW_B3_type;
uint8_t ZW_B4_type;


uint8_t end_data;
}eeprom_type;


pin_data_type pin_data;
eeprom_type   StarterProEEPROM;

uint8_t dev_id;

long _value;

uint8_t _slot_;
long  _stepper_speed_;
long  _s1_steps_;
long  _s2_steps_;






#endif


