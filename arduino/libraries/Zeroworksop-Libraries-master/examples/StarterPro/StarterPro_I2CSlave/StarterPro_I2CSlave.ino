#include <Arduino.h>
#include <avr/io.h>
#include <util/twi.h>
#include <avr/interrupt.h>
#include <EEPROM.h>
#include <Servo.h>
#include "Buzzer.h"
#include "StarterPro_I2CSlave.h"

//Print message priority
//#define DEBUG_INFO_ERROR
//#define DEBUG_INFO_HIGH  
//#define DEBUG_INFO_MID
//#define DEBUG_INFO_LOW
#define DEBUG_INFO

//Common parameter configuration
#define DEFAULT_I2C_ADDR    0x11
#define DEFAULT_TIME_OUT    2000



#define M1   0b1000
#define M2   0b0100
#define M3   0b0010
#define M4   0b0001

#define M1M2  0b1100
#define M1M3  0b1010
#define M1M4  0b1001

#define M2M3  0b0110
#define M2M4  0b0101

#define M3M4  0b0011

#define M1M2M3  0b1110
#define M1M2M4  0b1101
#define M1M3M4  0b1011
#define M2M3M4  0b0111

#define S1  	0b1100
#define S2  	0b0011
#define S1S2  0b1111
#define S2S1  0b0000

#define M1M2M3M4  0b1111

static void (*reset_this_CPU)(void) = 0x0000;

Servo myServoB1;
Servo myServoB2;
Servo myServoB3;
Servo myServoB4;

unsigned long now = 0;
 unsigned long last_step_time  = 0; 
 int number_of_steps = 200;      // total number of steps this motor can take
 int step_number = 0;          // which step the motor is on
 
 
 long S1_counter = 0;
 long S2_counter = 0;
 long zero_counter = 0;
 int S1_state;
 int S2_state;
 int zero_state;
 int zero_pin;
 long zero_max_step;
 
 uint8_t S1_ZERO_PIN = _ZW_A1_;
 uint8_t S2_ZERO_PIN = _ZW_A2_;
 
 const long S1_max_step	 = 9999;//35;
 const long S2_max_step  = 35;//48;
 
 

/****************************************************************************************************
 * I2C slave code
 * These codes used to start the i2c slave service and its command processing, If it is not
 * necessary, Do not modify this part of the code
****************************************************************************************************/
union
{
  byte byteVal[16];
  int16_t intVal[8];
  float floatVal[4];
  long longVal[4];
}val;

char bufI2C[32];
int16_t rd,wr;

/**
 * \par Function
 *   I2C_init
 * \par Description
 *   I2C initialization function, set the baudrate, device address, and configuration some 
 *   registers
 * \param[in]
 *   address - device address 
 * \par Output
 *   None
 * \return
 *   None
 * \par Others
 *   None
 */
void I2C_init(uint8_t address)
{
  // load address into TWI address register
  TWAR = address;

  TWCR = 0x00;   //Disable TWI
  TWBR = 0x02;   //Set the baudrate: CPU Clock/16+2(TWBR)
  TWSR|= 0x00;   //Set Divider factor

  //Set the TWCR to enable address matching and enable TWI, clear TWINT, enable TWI interrupt
  TWCR = (1<<TWIE) | (1<<TWEA) | (1<<TWINT) | (1<<TWEN);
}

/**
 * \par Function
 *   ISR(TWI_vect)
 * \par Description
 *   This function is used to process data from i2c host
 * \param[in]
 *   None 
 * \par Output
 *   bufI2C[]
 * \return
 *   None
 * \par Others
 *   None
 */
ISR(TWI_vect)
{
  // temporary stores the received data
  uint8_t data;

  // own address has been acknowledged
  if( (TWSR & 0xF8) == TW_SR_SLA_ACK )
  {  
    rd=0;
    wr=0;
    // clear TWI interrupt flag, prepare to receive next byte and acknowledge
    TWCR = (1<<TWEN) | (1<<TWIE) | (1<<TWINT) | (1<<TWEA);
  }
  else if( (TWSR & 0xF8) == TW_SR_DATA_ACK )
  { 
    // data has been received in slave receiver mode
    // save the received byte inside data 
    data = TWDR;
    bufI2C[rd++] = data;
    TWCR = (1<<TWEN) | (1<<TWIE) | (1<<TWINT) | (1<<TWEA);
  }
  else if((TWSR & 0xF8) == TW_ST_SLA_ACK)
  {
    // the start of i2c read
    TWDR = bufI2C[wr++]; // todo: errata of avr, to insert delay between twdr and twcr?
    // clear TWI interrupt flag, prepare to send next byte and receive acknowledge
    TWCR |= (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN); 
  }
  else if( (TWSR & 0xF8) == TW_ST_DATA_ACK )
  { 
    // device has been addressed to be a transmitter
    // copy the specified buffer address into the TWDR register for transmission
    TWDR = bufI2C[wr++];
    // clear TWI interrupt flag, prepare to send next byte and receive acknowledge
    TWCR |= (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN); 
  }
  else if((TWSR & 0xF8) == TW_SR_STOP)
  {
    ParseI2cCmd(bufI2C);
    TWCR = _BV(TWEN) | _BV(TWIE) | _BV(TWEA) | _BV(TWINT);
  }
  else
  {
    TWCR = _BV(TWEN) | _BV(TWIE) | _BV(TWEA) | _BV(TWINT)|_BV(TWSTO);
    while(TWCR & _BV(TWSTO))
    {
      continue;
    }
    TWCR = _BV(TWEN) | _BV(TWIE) | _BV(TWEA) | _BV(TWINT);
  }
}

/**
 * \par Function
 *   ParseI2cCmd
 * \par Description
 *   This function is used to process command from i2c host
 * \param[in]
 *   (bufI2C[])byte 0:   motor index
 *   (bufI2C[])byte 1:   cmd
 *   (bufI2C[])byte 2-n: parameters
 * \par Output
 *   None
 * \return
 *   None
 * \par Others
 *   None
 */
void ParseI2cCmd(char * c)
{
  int rpm;
  long angle;
  int power;
  uint8_t cmd =  (c[1] & 0x3f);
  uint8_t slot = c[0];
  memcpy(&val,c+2,16);
#ifdef DEBUG_INFO
  Serial.print("cmd: 0x");
  Serial.println(cmd,HEX);
  Serial.print("slot 0b");Serial.print(slot,BIN);
  Serial.print("  ");
  Serial.print(val.longVal[0]);
  Serial.print("  ");
  Serial.println(val.longVal[1]);
#endif
  switch(cmd){
    // move state and function
    case CMD_RESET:
      resetBroad();
      break;
    case CMD_RESET_STEPPER:
      	reset_stepper(slot);
      break;
    case CMD_GET_POWER_VOL:
      get_power_voltage();
      memcpy(&bufI2C[0],&pin_data.voltage,4);
     
      break;
    case CMD_SET_PIN_TYPE:
        pinMode(slot,val.byteVal[0]);
      break;
    case CMD_SET_PIN_DIGITAL_VAL:
        if(slot == _ZW_B1_) myServoB1.detach();
        else if(slot == _ZW_B2_) myServoB2.detach();
        else if(slot == _ZW_B3_) myServoB3.detach();
        else if(slot == _ZW_B4_) myServoB4.detach();

        pinMode(slot,OUTPUT);
        digitalWrite(slot,val.byteVal[0]);
        //Serial.print("pin ");
        //Serial.print(slot);
        //Serial.print("   value = ");
        //Serial.println(val.byteVal[0]);
      break;
    case CMD_SET_PIN_ANALOG_VAL:
        if(slot == _ZW_B1_) myServoB1.detach();
        else if(slot == _ZW_B2_) myServoB2.detach();
        else if(slot == _ZW_B3_) myServoB3.detach();
        else if(slot == _ZW_B4_) myServoB4.detach();

        pinMode(slot,OUTPUT);
        analogWrite(slot,val.longVal[0]);
      break;
    case CMD_SET_MOTOR:
      MotorControl(slot,val.longVal[0]);
      
      break;
    case CMD_SET_STEPPER:
      //Serial.print("stepper = ");Serial.print(slot);
      //Serial.print("Speed = ");Serial.print(val.longVal[0]);
      //Serial.print("steps to move = ");Serial.println(val.longVal[1]);
      StepperControl(slot,val.longVal[0],val.longVal[1]);
      //Serial.print("S1_counter =");Serial.println(S1_counter);
      //Serial.print("S2_counter =");Serial.println(S2_counter);
      
     
      break;
    case CMD_SET_STEPPER_ZERO_PIN:
      //	if(slot == S1)
     // 	S1_ZERO_PIN = val.byteVal[0];��
     // 	else if(slot == S2)S2_ZERO_PIN = val.byteVal[0];��
      
    case CMD_SET_STEPPER_SYNC:
          
      Serial.print("stepper = ");Serial.print(slot);
      Serial.print(" Speed = ");Serial.print(val.longVal[0]);
      Serial.print(" S1 steps to move = ");Serial.print(val.longVal[1]);
      Serial.print(" S2 steps to move = ");Serial.println(val.longVal[2]);
      StepperControlsync(slot,val.longVal[0],val.longVal[1],val.longVal[2]);
     Serial.print("S1_coutner = ");
    Serial.print(S1_counter);
    Serial.print("  S2_counter = ");
    Serial.println(S2_counter);
      
      break;
    case CMD_GET_PIN_TYPE:
      break;
      case CMD_GET_PIN_DIGITAL_VAL:
          if(slot == _ZW_B1_) myServoB1.detach();
          else if(slot == _ZW_B2_) myServoB1.detach();
          else if(slot == _ZW_B3_) myServoB1.detach();
          else if(slot == _ZW_B4_) myServoB1.detach();
          pinMode(slot,INPUT);
          digitalReadSlave(slot);
          memcpy(&bufI2C[0],&_value,4);
          break;
      case CMD_GET_PIN_ANALOG_VAL:
          if(slot == _ZW_B1_) myServoB1.detach();
          else if(slot == _ZW_B2_) myServoB2.detach();
          else if(slot == _ZW_B3_) myServoB3.detach();
          else if(slot == _ZW_B4_) myServoB4.detach();
          pinMode(slot,INPUT);
          analogReadSlave(slot);
          
        
          memcpy(&bufI2C[0],&_value,4);
          break;
          
      case CMD_GET_STEPPER_ZERO_PIN:    
        if(slot == S1)
        memcpy(&bufI2C[0],&S1_ZERO_PIN,2);
      	else if(slot == S2)
       memcpy(&bufI2C[0],&S1_ZERO_PIN,2);
      		break; 
          
      case CMD_GET_STEPPER_COUNTER:     
      
       	if(slot == S1)
      	{
      		memcpy(&bufI2C[0],&S1_counter,4);
      	}
      	else if(slot == S2)
      	{
      		memcpy(&bufI2C[0],&S2_counter,4);  
      	}
      	else if(slot == S1S2)
      	{
      		memcpy(&bufI2C[0],&S1_counter,4);
      		memcpy(&bufI2C[4],&S2_counter,4);  
      	}	    
     Serial.print("slot = ");Serial.println(slot);
     Serial.print("S1_counter = ");Serial.println(S1_counter);
    Serial.print("S2_counter = ");Serial.println(S2_counter);
   	delay(100); 
        break;
          
      case CMD_SET_DEVID:
        setDevid(val.byteVal[0]);
        
      case CMD_SET_SERVO:
      if(slot == _ZW_B1_)
      {
      	myServoB1.write(constrain(val.longVal[0],0,180));
      }
      else if(slot == _ZW_B2_)
      {
      	myServoB2.write(constrain(val.longVal[0],0,180));
      }
      else if(slot == _ZW_B3_)
      {
      	myServoB3.write(constrain(val.longVal[0],0,180));
      }
      else if(slot == _ZW_B4_)
      {
     	 	myServoB4.write(constrain(val.longVal[0],0,180));
      }
      break;   

                                                                                                            
     default:
     break;
  }
}



void resetBroad()
{
  readEEPROM();
  delay(10);
  initSensor();  
  I2C_init((dev_id) << 1);
  S1_counter = 0;
  S2_counter = 0;
}
void reset_stepper(int slot)
{
	switch(slot){
	case S1:
		StepperControl(S1,400,-S1_max_step);
		break;
	case S2:
	  StepperControl(S2,400,-S2_max_step);
		break;	
	case S1S2:
	StepperControlsync(S1,400,-S1_max_step,-S2_max_step);
 Serial.print("S1_coutner = ");
 Serial.print(S1_counter);
 Serial.print("S2_counter = ");
 Serial.println(S2_counter);
		break;
	
}

}



/****************************************************************************************************
 * Parameters configuration
****************************************************************************************************/
void setDefaultvalue(void)
{
  StarterProEEPROM.start_data = EEPROM_CAL_START;
  StarterProEEPROM.devid = DEFAULT_I2C_ADDR;
 
  StarterProEEPROM.ZW_A1_pin = _ZW_A1_;
  StarterProEEPROM.ZW_A1_type = INPUT;

  StarterProEEPROM.ZW_A2_pin = _ZW_A2_;
  StarterProEEPROM.ZW_A2_type = INPUT;

  StarterProEEPROM.ZW_A3_pin = _ZW_A3_;
  StarterProEEPROM.ZW_A3_type = INPUT;

  StarterProEEPROM.ZW_A4_pin = _ZW_A4_;
  StarterProEEPROM.ZW_A4_type = INPUT;

  StarterProEEPROM.ZW_B1_pin = _ZW_B1_;
  StarterProEEPROM.ZW_B1_type = OUTPUT;

  StarterProEEPROM.ZW_B2_pin = _ZW_B2_;
  StarterProEEPROM.ZW_B2_type = OUTPUT;

  StarterProEEPROM.ZW_B3_pin = _ZW_B3_;
  StarterProEEPROM.ZW_B3_type = OUTPUT;

  StarterProEEPROM.ZW_B4_pin = _ZW_B4_;
  StarterProEEPROM.ZW_B4_type = OUTPUT;

  StarterProEEPROM.Beep = BEEP;

  StarterProEEPROM.M1P = MOTOR1P;
  StarterProEEPROM.M1N = MOTOR1M;
  StarterProEEPROM.M2P = MOTOR2P;
  StarterProEEPROM.M2N = MOTOR2M;
  StarterProEEPROM.M3P = MOTOR3P;
  StarterProEEPROM.M3N = MOTOR3M;
  StarterProEEPROM.M4P = MOTOR4P;
  StarterProEEPROM.M4N = MOTOR4M;
  
  StarterProEEPROM.mid_data = EEPROM_CAL_MID;

  
  
  StarterProEEPROM.end_data = EEPROM_CAL_END;
}

void FloatToEEPROM(int address,int num,float *f)
{
  int i,j,bakupaddress;
  bakupaddress = address +  EEPROM.length()/2;
  for(i=0;i<2;i++)
  {
    for(j=0;j<num;j++)
    {
      EEPROM.put(address, f[j]);  
      address = address + sizeof(float);
    }
    address = bakupaddress;
  }
}

void IntToEEPROM(int address,int num, uint16_t *data)
{
  int i,j,bakupaddress;
  bakupaddress = address +  EEPROM.length()/2;
  for(i=0;i<2;i++)
  {
    for(j=0;j<num;j++)
    {
      EEPROM.put(address, data[j]);  
      address = address + sizeof(uint16_t);
    }
    address = bakupaddress;
  }
}

void ByteToEEPROM(int address,int num, uint8_t *data)
{
  int i,j,bakupaddress;
  bakupaddress = address +  EEPROM.length()/2;
  for(i=0;i<2;i++)
  {
    for(j=0;j<num;j++)
    {
      EEPROM.put(address, data[j]);  
      address = address + sizeof(uint8_t);
    }
    address = bakupaddress;
  }
}

void clearEEPROM(void)
{
 for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);
  } 
  delay(100);
}

void writetoEEPROM(void)
{
  int16_t i,address, length;
  length = EEPROM.length();
  for(i = 0; i < 2; i++)
  {
    EEPROM.write(EEPROM_START_POS, EEPROM_IF_HAVECAL_CHECK1);
    EEPROM.write(EEPROM_START_POS + 1, EEPROM_IF_HAVECAL_CHECK2);
    EEPROM.put(STORE_START_ADDR, StarterProEEPROM);
    address = length/2;
  } 
}

void updatefromBackuparea(void)
{
  int16_t address, length;
  length = EEPROM.length();
  address = length/2;
  if((EEPROM.read(address) == EEPROM_IF_HAVECAL_CHECK1) & (EEPROM.read(address + 1) == EEPROM_IF_HAVECAL_CHECK2))
  {
    address = length/2 + 2;
    EEPROM.get(address, StarterProEEPROM);
    if((StarterProEEPROM.start_data == EEPROM_CAL_START) & (StarterProEEPROM.mid_data == EEPROM_CAL_MID) & (StarterProEEPROM.end_data == EEPROM_CAL_END))
    {
      EEPROM.write(EEPROM_START_POS, EEPROM_IF_HAVECAL_CHECK1);
      EEPROM.write(EEPROM_START_POS+1, EEPROM_IF_HAVECAL_CHECK2);
      EEPROM.put(STORE_START_ADDR, StarterProEEPROM);
    }
    else
    {
      setDefaultvalue();  
      writetoEEPROM(); 
    }
  }
}

boolean readEEPROM(void)
{
  int16_t length = EEPROM.length();
  Serial.println( "Read data from EEPROM " );

  //EEPROM.get(STORE_DEVID_ADDR, encoder_eeprom_new.devid);
//  Serial.print("devid:");
 // Serial.println(encoder_eeprom_new.devid,DEC);
   
  if((EEPROM.read(EEPROM_START_POS) == EEPROM_IF_HAVECAL_CHECK1) & (EEPROM.read(EEPROM_START_POS + 1) == EEPROM_IF_HAVECAL_CHECK2))
  {
    EEPROM.get(STORE_START_ADDR, StarterProEEPROM);
    Serial.print("Dev ID: ");Serial.println(StarterProEEPROM.devid);
    Serial.println("Pin info:");
    Serial.print("ZW_A0: "); Serial.print(StarterProEEPROM.ZW_A1_pin);Serial.print(" ");
    Serial.println(StarterProEEPROM.ZW_A1_type);
    Serial.print("ZW_A1: ");Serial.print(StarterProEEPROM.ZW_A2_pin);Serial.print(" ");
    Serial.println(StarterProEEPROM.ZW_A2_type);
    Serial.print("ZW_A2: ");Serial.print(StarterProEEPROM.ZW_A3_pin);Serial.print(" ");
    Serial.println(StarterProEEPROM.ZW_A3_type);
    Serial.print("ZW_A3: ");Serial.print(StarterProEEPROM.ZW_A4_pin);Serial.print(" "); 
    Serial.println(StarterProEEPROM.ZW_A4_type);
    Serial.print("ZW_B1: ");Serial.print(StarterProEEPROM.ZW_B1_pin);Serial.print(" ");
    Serial.println(StarterProEEPROM.ZW_B1_type);
    Serial.print("ZW_B2: ");Serial.print(StarterProEEPROM.ZW_B2_pin);Serial.print(" ");
    Serial.println(StarterProEEPROM.ZW_B2_type);
    Serial.print("ZW_B3: ");Serial.print(StarterProEEPROM.ZW_B3_pin);Serial.print(" ");
    Serial.println(StarterProEEPROM.ZW_B3_type);
    Serial.print("ZW_B4: ");Serial.print(StarterProEEPROM.ZW_B4_pin);Serial.print(" ");
    Serial.println(StarterProEEPROM.ZW_B4_type);

    Serial.print("Beep: ");Serial.println(StarterProEEPROM.Beep);
    Serial.print("M1P: ");Serial.print(StarterProEEPROM.M1P);Serial.println(" ");
    Serial.print("M1N: ");Serial.print(StarterProEEPROM.M1N);Serial.println(" ");
    Serial.print("M2P: ");Serial.print(StarterProEEPROM.M2P);Serial.println(" ");
    Serial.print("M2N: ");Serial.print(StarterProEEPROM.M2N);Serial.println(" ");
    Serial.print("M3P: ");Serial.print(StarterProEEPROM.M3P);Serial.println(" ");
    Serial.print("M3N: ");Serial.print(StarterProEEPROM.M3N);Serial.println(" ");
    Serial.print("M4P: ");Serial.print(StarterProEEPROM.M4P);Serial.println(" ");
    Serial.print("M4N: ");Serial.print(StarterProEEPROM.M4N);Serial.println(" ");
  
       
    //Serial.print("size = ");
    //Serial.println(sizeof(encoder_eeprom_type));
    //Serial.print("start data:");Serial.println(encoder_eeprom.start_data,HEX);
    //EEPROM.get(STORE_S7_PIN_ADDR, encoder_eeprom.S5_pin);
    //Serial.print("S5 maxval:");Serial.println(encoder_eeprom.S5_pin);

    //  Serial.print("devid:");
     // Serial.println(encoder_eeprom.devid,DEC);
    if((StarterProEEPROM.start_data == EEPROM_CAL_START) & (StarterProEEPROM.mid_data == EEPROM_CAL_MID) & (StarterProEEPROM.end_data == EEPROM_CAL_END))
    {
      return true;
    }
    else
    {
      Serial.println( "updatefromBackuparea" );
      updatefromBackuparea();  
      return true;  
    }
  }
  else if((EEPROM.read(length/2) == EEPROM_IF_HAVECAL_CHECK1) & (EEPROM.read(length/2 + 1) == EEPROM_IF_HAVECAL_CHECK2))
  {
    Serial.println( "updatefromBackuparea 2" );
    updatefromBackuparea(); 
    return true;
  }
  else
  {
    
    setDefaultvalue();
    writetoEEPROM();
    return false;
  }


}


void setDevid(uint8_t devid)
{
  memset(&pin_data,0,sizeof(pin_data_type));
  StarterProEEPROM.devid = devid;
  ByteToEEPROM(STORE_DEVID_ADDR,1,&devid);
}

void  setPinType(uint8_t  pin, uint8_t  type)
{
  pinMode(pin,type);
}

void digitalWriteSlave(uint8_t pin, uint8_t  value)
{
  pinMode(pin,OUTPUT);
  digitalWrite(pin, value);  
}

void analogWriteSlave(uint8_t pin, uint8_t  value)
{

  
  if(pin == 3 || pin == 5 || pin == 6 || pin == 9 || pin == 10 || pin == 11)
  {
    value = constrain( value, 0, 255);
    pinMode(pin, OUTPUT);
    analogWrite(pin, value);
  }
}



void digitalReadSlave(uint8_t pin)
{
 // long value;
  _value = digitalRead(pin);
}
void analogReadSlave(uint8_t pin)
{
  //long value;
  pinMode(pin, INPUT);
  delay(100);
  _value = analogRead(pin);
  Serial.print("value = ");
  Serial.println(_value);
}

void initSensor()
{
  // memset(&StarterProEEPROM,0,sizeof(eeprom_type));
   dev_id = StarterProEEPROM.devid;  

   pinMode(StarterProEEPROM.ZW_A1_pin,StarterProEEPROM.ZW_A1_type);
   pinMode(StarterProEEPROM.ZW_A2_pin,StarterProEEPROM.ZW_A2_type);
   pinMode(StarterProEEPROM.ZW_A3_pin,StarterProEEPROM.ZW_A3_type);
   pinMode(StarterProEEPROM.ZW_A4_pin,StarterProEEPROM.ZW_A4_type);
   pinMode(StarterProEEPROM.ZW_B1_pin,StarterProEEPROM.ZW_B1_type);
   pinMode(StarterProEEPROM.ZW_B2_pin,StarterProEEPROM.ZW_B2_type);
   pinMode(StarterProEEPROM.ZW_B3_pin,StarterProEEPROM.ZW_B3_type);
   pinMode(StarterProEEPROM.ZW_B4_pin,StarterProEEPROM.ZW_B4_type);

   pinMode(StarterProEEPROM.Beep,OUTPUT);
   digitalWrite(StarterProEEPROM.Beep,LOW);

   pinMode(StarterProEEPROM.M1P,OUTPUT);
   pinMode(StarterProEEPROM.M1N,OUTPUT);
   pinMode(StarterProEEPROM.M2P,OUTPUT);
   pinMode(StarterProEEPROM.M2N,OUTPUT);
   pinMode(StarterProEEPROM.M3P,OUTPUT);
   pinMode(StarterProEEPROM.M3N,OUTPUT);
   pinMode(StarterProEEPROM.M4P,OUTPUT);
   pinMode(StarterProEEPROM.M4N,OUTPUT);
   digitalWrite(StarterProEEPROM.M1P,LOW);
   digitalWrite(StarterProEEPROM.M1N,LOW);
   digitalWrite(StarterProEEPROM.M2P,LOW);
   digitalWrite(StarterProEEPROM.M2N,LOW);
   digitalWrite(StarterProEEPROM.M3P,LOW);
   digitalWrite(StarterProEEPROM.M3N,LOW);
   digitalWrite(StarterProEEPROM.M4P,LOW);
   digitalWrite(StarterProEEPROM.M4N,LOW);

}

void get_power_voltage()
{
    pin_data.voltage = analogRead(A6);
    Serial.print("voltage = "); Serial.println(pin_data.voltage);;
    //memcpy(&bufI2C[0],&pin_data.voltage,4);
  
}



 void stepMotor(uint8_t slot,int thisStep)
{
    int motor_pin_1,motor_pin_2,motor_pin_3,motor_pin_4;
    int zero_state;
    int zero_pin;
    switch(slot)
    {
        case S1:
            motor_pin_1  = MOTOR1P;
            motor_pin_2  = MOTOR1M;
            motor_pin_3  = MOTOR2P;
            motor_pin_4  = MOTOR2M;
            zero_pin = S1_ZERO_PIN;
            break;
        case S2:
            motor_pin_1  = MOTOR3P;
            motor_pin_2  = MOTOR3M;
            motor_pin_3  = MOTOR4P;
            motor_pin_4  = MOTOR4M;
            zero_pin = S2_ZERO_PIN;
            break; 
    
    }
 
  
  	zero_state = digitalRead(zero_pin);
  	if(zero_state)
  	{
    //Serial.println("******************");
    	switch (thisStep) {
      	case 0:  // 1010
        digitalWrite(motor_pin_1, HIGH);
        digitalWrite(motor_pin_2, LOW);
        digitalWrite(motor_pin_3, HIGH);
        digitalWrite(motor_pin_4, LOW);
        //Serial.println(0);
      	break;
      	case 1:  // 0110
        digitalWrite(motor_pin_1, HIGH);
        digitalWrite(motor_pin_2, HIGH);
        digitalWrite(motor_pin_3, HIGH);
        digitalWrite(motor_pin_4, LOW);
        // Serial.println(1);
      	break;
      	case 2:  //0101
        digitalWrite(motor_pin_1, HIGH);
        digitalWrite(motor_pin_2, HIGH);
        digitalWrite(motor_pin_3, HIGH);
        digitalWrite(motor_pin_4, HIGH);
        //Serial.println(2);
      	break;
      	case 3:  //1001
        digitalWrite(motor_pin_1, HIGH);
        digitalWrite(motor_pin_2, LOW);
        digitalWrite(motor_pin_3, HIGH);
        digitalWrite(motor_pin_4, HIGH);
         //Serial.println(3);
      	break;
    	}
  	}
  	else
  	{
  			digitalWrite(motor_pin_1, LOW);
  			digitalWrite(motor_pin_3, LOW);
  	}
}



void StepperControlsync(uint8_t slot,long whatSpeed,long steps_to_move1,long steps_to_move2 )
{

	  unsigned long time_start;
    unsigned long step_delay;
    int direction1;            // Direction of rotation
    int direction2;
    int curr_step1;
    int curr_step2;
    int max_step;
    int steps_move1;
    int steps_move2;
    step_delay = 60L * 1000L * 1000L / number_of_steps / whatSpeed;

     // determine direction based on whether steps_to_mode is + or -:
  	if (steps_to_move1 > 0) 
  		{ 
  			direction1 = 1; 
  			if(S1_counter + steps_to_move1 > S1_max_step) steps_move1 = S1_max_step -steps_to_move1;
  			else steps_move1 = steps_to_move1;
  		}
  	if (steps_to_move1 < 0) 
  		{ 
  			direction1 = 0; 
  			if(steps_to_move1 + S1_counter >0 )steps_move1 = abs(steps_to_move1);
   	 		else steps_move1 = S1_counter;
   	 	}
    		
  	if (steps_to_move2 > 0) 
  		{ 
  			direction2 = 1; 
  			if(S2_counter + steps_to_move2 > S2_max_step) steps_move2 = S2_max_step -steps_to_move2;
  			else steps_move2 = steps_to_move2;
  		}
  	if (steps_to_move2 < 0) 
  		{ 
  			direction2 = 0; 
  			if(steps_to_move2+ S2_counter >0 )steps_move2 = abs(steps_to_move2);
   	 		else steps_move2 = S2_counter;
   	 	}
  		Serial.print("S1 direction = ");Serial.println(direction1);
  		Serial.print("S2 direction = ");Serial.println(direction2);
  
  	max_step = abs(steps_move1) > abs(steps_move2) ? abs(steps_move1) : abs(steps_move2);
  	curr_step1 = abs(steps_move1);
  	curr_step2 = abs(steps_move2);
   
    int motor_pin_1,motor_pin_2,motor_pin_3,motor_pin_4;
    int motor_pin_5,motor_pin_6,motor_pin_7,motor_pin_8;
    switch(slot)
    {
        case S1S2:
            motor_pin_1  = MOTOR1P;
            motor_pin_2  = MOTOR1M;
            motor_pin_3  = MOTOR2P;
            motor_pin_4  = MOTOR2M;
            motor_pin_5  = MOTOR3P;
            motor_pin_6  = MOTOR3M;
            motor_pin_7  = MOTOR4P;
            motor_pin_8  = MOTOR4M;
            break;
        case S2S1:
            motor_pin_1  = MOTOR3P;
            motor_pin_2  = MOTOR3M;
            motor_pin_3  = MOTOR4P;
            motor_pin_4  = MOTOR4M;
            motor_pin_5  = MOTOR1P;
            motor_pin_6  = MOTOR1M;
            motor_pin_7  = MOTOR2P;
            motor_pin_8  = MOTOR2M;
            break; 
    
    }
    
	
  for(int j = 0; j<abs(max_step); j++)
  {
  		S1_state = digitalRead(S1_ZERO_PIN);
  		S2_state = digitalRead(S2_ZERO_PIN);
  		
  		
  		
    for(int i = 0; i<50; i++)
    {
      if(direction1 == 1 && direction2 == 1)
      {
      	if(curr_step1 >0 /*&& S1_state == 1*/)
      	{
        	digitalWrite(motor_pin_1, HIGH);
        	digitalWrite(motor_pin_2, LOW);
        	digitalWrite(motor_pin_3, HIGH);
        	digitalWrite(motor_pin_4, LOW);
        	
        }
        else
        {
         	digitalWrite(motor_pin_1, LOW);
         	digitalWrite(motor_pin_3, LOW);        	
        }
        
        
        if(curr_step2 >0 /*&& S2_state == 1*/)
        {
        	digitalWrite(motor_pin_5, HIGH);
        	digitalWrite(motor_pin_6, LOW);
        	digitalWrite(motor_pin_7, HIGH);
        	digitalWrite(motor_pin_8, LOW);  
        	
        }
        else
        {
         	digitalWrite(motor_pin_5, LOW);
         	digitalWrite(motor_pin_7, LOW);
         	
        }   
        
        delayMicroseconds(step_delay); 
        if(curr_step1 >0 /*&& S1_state == 1*/)
      	{
        	digitalWrite(motor_pin_1, HIGH);
        	digitalWrite(motor_pin_2, HIGH);
        	digitalWrite(motor_pin_3, HIGH);
        	digitalWrite(motor_pin_4, LOW); 
        }
        else
        {
         	digitalWrite(motor_pin_1, LOW);
         	digitalWrite(motor_pin_3, LOW);
        }
        if(curr_step2 >0/*&& S2_state == 1*/)
        {
        	digitalWrite(motor_pin_5, HIGH);
        	digitalWrite(motor_pin_6, HIGH);
        	digitalWrite(motor_pin_7, HIGH);
        	digitalWrite(motor_pin_8, LOW); 
        }
        else
        {
         	digitalWrite(motor_pin_5, LOW);
         	digitalWrite(motor_pin_7, LOW);
        }
       
        delayMicroseconds(step_delay); 
        
        if(curr_step1 >0 /*&& S1_state == 1*/)
      	{
        	digitalWrite(motor_pin_1, HIGH);
        	digitalWrite(motor_pin_2, HIGH);
        	digitalWrite(motor_pin_3, HIGH);
        	digitalWrite(motor_pin_4, HIGH);
        }
        else
        {
         	digitalWrite(motor_pin_1, LOW);
         	digitalWrite(motor_pin_3, LOW);
        }
        if(curr_step2 >0/*&& S2_state == 1*/)
        {
        	digitalWrite(motor_pin_5, HIGH);
        	digitalWrite(motor_pin_6, HIGH);
        	digitalWrite(motor_pin_7, HIGH);
        	digitalWrite(motor_pin_8, HIGH);
        }
        else
        {
         	digitalWrite(motor_pin_5, LOW);
         	digitalWrite(motor_pin_7, LOW);
        }
       
        delayMicroseconds(step_delay); 
        if(curr_step1 >0 /*&& S1_state == 1*/)
      	{
        	digitalWrite(motor_pin_1, HIGH);
        	digitalWrite(motor_pin_2, LOW);
        	digitalWrite(motor_pin_3, HIGH);
        	digitalWrite(motor_pin_4, HIGH);
        }
        else
        {
         	digitalWrite(motor_pin_1, LOW);
         	digitalWrite(motor_pin_3, LOW);
        }
        if(curr_step2 >0/*&& S2_state == 1*/)
        {
        	digitalWrite(motor_pin_5, HIGH);
        	digitalWrite(motor_pin_6, LOW);
        	digitalWrite(motor_pin_7, HIGH);
        	digitalWrite(motor_pin_8, HIGH); 
        }
        else
        {
         	digitalWrite(motor_pin_5, LOW);
         	digitalWrite(motor_pin_7, LOW);
        }
        delayMicroseconds(step_delay); 
      }
      else if(direction1 == 0 && direction2 == 0)
      {  
      	if(curr_step1 >0 && S1_state == 1)
      	{ 
        	digitalWrite(motor_pin_1, HIGH);
        	digitalWrite(motor_pin_2, LOW);
        	digitalWrite(motor_pin_3, HIGH);
        	digitalWrite(motor_pin_4, LOW);
        
        	
        }
        else
        {
         	digitalWrite(motor_pin_1, LOW);
         	digitalWrite(motor_pin_3, LOW);
         	
        }
        if(curr_step2 >0&& S2_state == 1)
        {
        	digitalWrite(motor_pin_5, HIGH);
        	digitalWrite(motor_pin_6, LOW);
        	digitalWrite(motor_pin_7, HIGH);
        	digitalWrite(motor_pin_8, LOW);  
        	
        }
        else
        {
         	digitalWrite(motor_pin_5, LOW);
         	digitalWrite(motor_pin_7, LOW);
         	
        }
         
        delayMicroseconds(step_delay); 
        if(curr_step1 >0 && S1_state == 1)
      	{
        	digitalWrite(motor_pin_1, HIGH);
        	digitalWrite(motor_pin_2, LOW);
        	digitalWrite(motor_pin_3, HIGH);
        	digitalWrite(motor_pin_4, HIGH);
        }
        else
        {
         	digitalWrite(motor_pin_1, LOW);
         	digitalWrite(motor_pin_3, LOW);
        }
        if(curr_step2 >0&& S2_state == 1)
        {
        	digitalWrite(motor_pin_5, HIGH);
        	digitalWrite(motor_pin_6, LOW);
        	digitalWrite(motor_pin_7, HIGH);
        	digitalWrite(motor_pin_8, HIGH); 
        }
        else
        {
         	digitalWrite(motor_pin_5, LOW);
         	digitalWrite(motor_pin_7, LOW);
        }
       
        delayMicroseconds(step_delay); 
        if(curr_step1 >0 && S1_state == 1)
      	{
        	digitalWrite(motor_pin_1, HIGH);
        	digitalWrite(motor_pin_2, HIGH);
        	digitalWrite(motor_pin_3, HIGH);
        	digitalWrite(motor_pin_4, HIGH);
        }
        else
        {
         	digitalWrite(motor_pin_1, LOW);
         	digitalWrite(motor_pin_3, LOW);
        }
        if(curr_step2 >0&& S2_state == 1)
        {
        	digitalWrite(motor_pin_5, HIGH);
        	digitalWrite(motor_pin_6, HIGH);
        	digitalWrite(motor_pin_7, HIGH);
        	digitalWrite(motor_pin_8, HIGH);  
        }
        else
        {
         	digitalWrite(motor_pin_5, LOW);
         	digitalWrite(motor_pin_7, LOW);
        }
       
        delayMicroseconds(step_delay); 
        if(curr_step1 >0 && S1_state == 1)
      	{
        	digitalWrite(motor_pin_1, HIGH);
        	digitalWrite(motor_pin_2, HIGH);
        	digitalWrite(motor_pin_3, HIGH);
        	digitalWrite(motor_pin_4, LOW);
        }
          else
         {
         	digitalWrite(motor_pin_1, LOW);
         	digitalWrite(motor_pin_3, LOW);
         }
        if(curr_step2 >0&& S2_state == 1)
        {
        	digitalWrite(motor_pin_5, HIGH);
        	digitalWrite(motor_pin_6, HIGH);
        	digitalWrite(motor_pin_7, HIGH);
        	digitalWrite(motor_pin_8, LOW);       
        }
        else
        {
         	digitalWrite(motor_pin_5, LOW);
         	digitalWrite(motor_pin_7, LOW);
        }
       
        delayMicroseconds(step_delay);     
      } 
      else if(direction1 == 1 && direction2 == 0)
      {
       
       	if(curr_step1 >0 /*&& S1_state == 1*/)
      	{
        	digitalWrite(motor_pin_1, HIGH);
        	digitalWrite(motor_pin_2, LOW);
        	digitalWrite(motor_pin_3, HIGH);
        	digitalWrite(motor_pin_4, LOW);
        	
        }
        else
        {
         	digitalWrite(motor_pin_1, LOW);
         	digitalWrite(motor_pin_3, LOW);
         	
        }
        if(curr_step2 >0&& S2_state == 1 )
        {
        	digitalWrite(motor_pin_5, HIGH);
        	digitalWrite(motor_pin_6, LOW);
        	digitalWrite(motor_pin_7, HIGH);
        	digitalWrite(motor_pin_8, LOW);  
        	
        }
       	else
        {
         	digitalWrite(motor_pin_5, LOW);
         	digitalWrite(motor_pin_7, LOW);
         	
        }
        delayMicroseconds(step_delay); 
        if(curr_step1 >0 /*&& S1_state == 1*/)
      	{
        	digitalWrite(motor_pin_1, HIGH);
        	digitalWrite(motor_pin_2, HIGH);
        	digitalWrite(motor_pin_3, HIGH);
        	digitalWrite(motor_pin_4, LOW); 
        }
        else
        {
         	digitalWrite(motor_pin_1, LOW);
         	digitalWrite(motor_pin_3, LOW);
        }
        if(curr_step2 >0&& S2_state == 1)
        {
        	digitalWrite(motor_pin_5, HIGH);
        	digitalWrite(motor_pin_6, LOW);
        	digitalWrite(motor_pin_7, HIGH);
        	digitalWrite(motor_pin_8, HIGH); 
        }
       	else
        {
         	digitalWrite(motor_pin_5, LOW);
         	digitalWrite(motor_pin_7, LOW);
        }
        delayMicroseconds(step_delay); 
        if(curr_step1 >0 /*&& S1_state == 1*/)
      	{
        	digitalWrite(motor_pin_1, HIGH);
        	digitalWrite(motor_pin_2, HIGH);
        	digitalWrite(motor_pin_3, HIGH);
        	digitalWrite(motor_pin_4, HIGH);   
        }
        else
        {
         	digitalWrite(motor_pin_1, LOW);
         	digitalWrite(motor_pin_3, LOW);
        }
        if(curr_step2 >0&& S2_state == 1)
        {
        	digitalWrite(motor_pin_5, HIGH);
        	digitalWrite(motor_pin_6, HIGH);
        	digitalWrite(motor_pin_7, HIGH);
        	digitalWrite(motor_pin_8, HIGH); 
        }
        else
         {
         	digitalWrite(motor_pin_5, LOW);
         	digitalWrite(motor_pin_7, LOW);
         }
       
        delayMicroseconds(step_delay); 
        if(curr_step1 >0 /*&& S1_state == 1*/)
      	{
        	digitalWrite(motor_pin_1, HIGH);
        	digitalWrite(motor_pin_2, LOW);
        	digitalWrite(motor_pin_3, HIGH);
        	digitalWrite(motor_pin_4, HIGH); 
        }
        else
        {
         	digitalWrite(motor_pin_1, LOW);
         	digitalWrite(motor_pin_3, LOW);
        }
        if(curr_step2 >0&& S2_state == 1)
        {
        	digitalWrite(motor_pin_5, HIGH);
        	digitalWrite(motor_pin_6, HIGH);
        	digitalWrite(motor_pin_7, HIGH);
        	digitalWrite(motor_pin_8, LOW);  
        }
        else
        {
         	digitalWrite(motor_pin_5, LOW);
         	digitalWrite(motor_pin_7, LOW);
        }
       
        delayMicroseconds(step_delay); 
       }
       else if(direction1 == 0 && direction2 == 1)
       {
        if(curr_step1 >0 && S1_state == 1)
      	{
        	digitalWrite(motor_pin_1, HIGH);
        	digitalWrite(motor_pin_2, LOW);
        	digitalWrite(motor_pin_3, HIGH);
        	digitalWrite(motor_pin_4, LOW);
        	
        }
        else
        {
         	digitalWrite(motor_pin_1, LOW);
         	digitalWrite(motor_pin_3, LOW);
         	
        }
        if(curr_step2 >0/*&& S2_state == 1*/)
        {
        	digitalWrite(motor_pin_5, HIGH);
        	digitalWrite(motor_pin_6, LOW);
        	digitalWrite(motor_pin_7, HIGH);
        	digitalWrite(motor_pin_8, LOW);   
        	
        }
         else
         {
         	digitalWrite(motor_pin_5, LOW);
         	digitalWrite(motor_pin_7, LOW);
         	
         }
        delayMicroseconds(step_delay); 
        if(curr_step1 >0 && S1_state == 1)
      	{
        	digitalWrite(motor_pin_1, HIGH);
        	digitalWrite(motor_pin_2, LOW);
        	digitalWrite(motor_pin_3, HIGH);
        	digitalWrite(motor_pin_4, HIGH);
         }
          else
         {
         	digitalWrite(motor_pin_1, LOW);
         	digitalWrite(motor_pin_3, LOW);
         }
        if(curr_step2 >0/*&& S2_state == 1*/)
        {
        	digitalWrite(motor_pin_5, HIGH);
        	digitalWrite(motor_pin_6, HIGH);
        	digitalWrite(motor_pin_7, HIGH);
        	digitalWrite(motor_pin_8, LOW); 
        }  
         else
         {
         	digitalWrite(motor_pin_5, LOW);
         	digitalWrite(motor_pin_7, LOW);
         } 
        delayMicroseconds(step_delay);  
        if(curr_step1 >0 && S1_state == 1)
      	{
       	 	digitalWrite(motor_pin_1, HIGH);
        	digitalWrite(motor_pin_2, HIGH);
        	digitalWrite(motor_pin_3, HIGH);
        	digitalWrite(motor_pin_4, HIGH);
         }
          else
         {
         	digitalWrite(motor_pin_1, LOW);
         	digitalWrite(motor_pin_3, LOW);
         }
        if(curr_step2 >0/*&& S2_state == 1*/)
        {
        	digitalWrite(motor_pin_5, HIGH);
        	digitalWrite(motor_pin_6, HIGH);
        	digitalWrite(motor_pin_7, HIGH);
        	digitalWrite(motor_pin_8, HIGH); 
        }
        else
         {
         	digitalWrite(motor_pin_5, LOW);
         	digitalWrite(motor_pin_7, LOW);
         }
        delayMicroseconds(step_delay);
        if(curr_step1 >0 && S1_state == 1)
      	{ 
        	digitalWrite(motor_pin_1, HIGH);
        	digitalWrite(motor_pin_2, HIGH);
        	digitalWrite(motor_pin_3, HIGH);
        	digitalWrite(motor_pin_4, LOW); 
         }
          else
         {
         	digitalWrite(motor_pin_1, LOW);
         	digitalWrite(motor_pin_3, LOW);
         }
        if(curr_step2 >0/*&& S2_state == 1*/)
        {
        	digitalWrite(motor_pin_5, HIGH);
        	digitalWrite(motor_pin_6, LOW);
        	digitalWrite(motor_pin_7, HIGH);
        	digitalWrite(motor_pin_8, HIGH); 
        }
        else
        {
         	digitalWrite(motor_pin_5, LOW);
         	digitalWrite(motor_pin_7, LOW);
        }
        delayMicroseconds(step_delay); 
        
       
       }
    }
    
    if(S1_state == 1)     
    {
    	 
    	if(curr_step1>0)
    	{
      	if(direction1 == 1) S1_counter++;
 				else 							 S1_counter--;
 			}
 			else
 			{
 			digitalWrite(motor_pin_1, LOW);
 			digitalWrite(motor_pin_3, LOW);
 			}
 			curr_step1--;
    }
    else
    {
    	if(curr_step1>0 && direction1 == 1) S1_counter++;
    	else
    	{
    		S1_counter = 0;
    		digitalWrite(motor_pin_1, LOW);
 				digitalWrite(motor_pin_3, LOW);
    	}
    	
    }	
    
    if(S2_state ==1)
    {
 		
    	if(curr_step2 >0)
    	{
       if(direction2 == 1) S2_counter++;
 			 else 							 S2_counter--; 				
 			}
 			else
 			{
 				digitalWrite(motor_pin_5, LOW);
 				digitalWrite(motor_pin_7, LOW);
 			}
 			curr_step2--;
 		}
 		else
 		{
 			if(curr_step2>0 && direction2 == 1) S2_counter++;
 			else
 			{
 				S2_counter =0;
 				digitalWrite(motor_pin_5, LOW);
 				digitalWrite(motor_pin_7, LOW);
 			}
 			
 		}
 		
 		 
    
  }    
  
  digitalWrite(motor_pin_1, LOW);		
  digitalWrite(motor_pin_3, LOW);
 	digitalWrite(motor_pin_5, LOW);
 	digitalWrite(motor_pin_7, LOW);         
}
 
 
 // 如果零点开关触碰到，则只能正向移动。
 //如果计数步数超过最大步数，则只能负向移动
 
void StepperControl(uint8_t slot,long whatSpeed,long steps_to_move)
{

   unsigned long step_delay;
   int direction;            // Direction of rotation
   
   int steps_move;
   step_delay = 60L * 1000L * 1000L / number_of_steps / whatSpeed;
   

   int motor_pin_1,motor_pin_2,motor_pin_3,motor_pin_4;
   switch(slot)
   {
        case S1:
            motor_pin_1  = MOTOR1P;
            motor_pin_2  = MOTOR1M;
            motor_pin_3  = MOTOR2P;
            motor_pin_4  = MOTOR2M;
            zero_state = S1_state;
            zero_pin = S1_ZERO_PIN; 
            zero_counter = S1_counter;
            zero_max_step = S1_max_step;
            break;
        case S2:
            motor_pin_1  = MOTOR3P;
            motor_pin_2  = MOTOR3M;
            motor_pin_3  = MOTOR4P;
            motor_pin_4  = MOTOR4M;
            zero_state = S2_state;
            zero_pin = S2_ZERO_PIN;   
            zero_counter = S2_counter;   
            zero_max_step = S2_max_step;
            break;   
    }



   // determine direction based on whether steps_to_mode is + or -:
   if (steps_to_move > 0) 
   {
   		 direction = 1;
   		
   		// if(steps_to_move + zero_counter <zero_max_step) steps_move = steps_to_move;
   		// else steps_move = zero_max_step - zero_counter;
       steps_move = steps_to_move;
   }
   if (steps_to_move < 0)
   	 { 
   	 	direction = 0; 
   	 	//if(steps_to_move + zero_counter >0 )steps_move = abs(steps_to_move);
   	 //	else steps_move = S1_counter;

      steps_move = abs(steps_to_move);
   	 }  
    
	Serial.print("Slot = ");Serial.print(slot);
	Serial.print("direction = ");Serial.println(direction);
	Serial.print("steps to move = ");Serial.println(steps_move);
	Serial.print("step counter before move = ");Serial.println(zero_counter);
	
  for(int j = 0; j<steps_move; j++)
  {
   	
   	zero_state = digitalRead(zero_pin);
   	if(direction == 1)
   	{   		
          //Serial.println("positive");
     			for(int i = 0; i<200; i++)
      		{         	
          	stepMotor(slot,i % 4);
          	delayMicroseconds(step_delay);          
      		}
      		
      switch(slot)
     	{
        case S1:
    		 	S1_counter++;
    		 	zero_counter = S1_counter;	
    			break;
        case S2:
        	S2_counter++;
        	zero_counter = S2_counter;	
        	break;      
     	}	
      	
    }
    else if(zero_state ==1 && direction == 0)
    { 
      	for(int i = 0; i<200; i++)
      	{
          int number ;
          number = 3 - i % 4;          
          stepMotor(slot,number);
          delayMicroseconds(step_delay); 
         
       	}       	
       	switch(slot)
     		{
        	case S1:
    			S1_counter--;    
    			zero_counter = S1_counter;	
    			break;
        	case S2:
       	 	S2_counter--;
       	 	zero_counter = S2_counter;	
        	break;
     		}
    }   	      
   	else
   	{ 	
     		digitalWrite(motor_pin_1, LOW);
        digitalWrite(motor_pin_3, LOW);
     		switch(slot)
     		{
        	case S1:
    			S1_counter = 0;   		
    			zero_counter = S1_counter;	
    			break;
        	case S2:
        	S2_counter =0; 	
        	zero_counter = S2_counter;	
        	break;
        
     		}
   	}
  }           
  digitalWrite(motor_pin_1, LOW);
  digitalWrite(motor_pin_3, LOW);
 
  Serial.print("step counter after move = ");Serial.println(zero_counter);
  
 }
 

/*
void StepperControl(uint8_t slot,long whatSpeed,long steps_to_move)
{
    unsigned long step_delay;
    int direction;            // Direction of rotation
    step_delay = 60L * 1000L * 1000L / number_of_steps / whatSpeed;
    
    long steps_left = abs(steps_to_move*200);  // how many steps to take

  	// determine direction based on whether steps_to_mode is + or -:
  	if (steps_to_move > 0) { direction = 1; }
  	if (steps_to_move < 0) { direction = 0; }

  	// decrement the number of steps, moving one step each time:
  	while (steps_left > 0){
  		//Serial.println(steps_left);
    	 now = micros();
    	// move only if the appropriate delay has passed:
    	if (now - last_step_time >=  step_delay){
      	// get the timeStamp of when you stepped:
      	last_step_time = now;
      	// increment or decrement the step number,
      	// depending on direction:
      	if (direction == 1){
        	step_number++;
        	if (step_number == number_of_steps) {
          step_number = 0;
       	 	}
      	}else{
        	if (step_number == 0) {
          step_number = number_of_steps;
        	}
        	step_number--;
      	}
      	// decrement the steps left:
      	steps_left--;
      	// step the motor to step number 0, 1, ..., {3 or 10}
       Serial.println(steps_left);
       stepMotor(slot,step_number % 4);
       //delayMicroseconds(10);
    	}
  	}
  	
  	switch(slot)
  	{
  		case S1:
  			digitalWrite(MOTOR1P, LOW);
        digitalWrite(MOTOR2P, LOW);
  		break;
  			
  		case S2:
  			digitalWrite(MOTOR3P, LOW);
        digitalWrite(MOTOR4P, LOW);
  		break;	
   }
  	
 	
}
*/

void MotorControl(uint8_t MotorNumber,long Speed) {

  int M1_flag, M2_flag,M3_flag,M4_flag;

  M4_flag = MotorNumber & 0b0001;
  M3_flag = (MotorNumber & 0b0010) >> 1;
  M2_flag = (MotorNumber & 0b0100) >> 2;
  M1_flag = (MotorNumber & 0b1000) >> 3;


  boolean reverse = 0;

  if (Speed < 0)
  {
    Speed = -Speed; // make speed a positive quantity
    reverse = 1;    // preserve the direction
  }
  if (Speed > 254)  // Max
    Speed = 254;


Serial.print("Speed = ");Serial.println(Speed);
Serial.print("reverse = "); Serial.print(reverse);
  if(M1_flag)
  {
    if(reverse)
    {
        analogWrite(MOTOR1P,Speed);
        digitalWrite(MOTOR1M,HIGH);  
    }
    else
    {
        analogWrite(MOTOR1P,Speed);
        digitalWrite(MOTOR1M,LOW);  
    }    
  }

  
  if(M2_flag)
  {
     if(reverse)
    {
        analogWrite(MOTOR2P,Speed);
        digitalWrite(MOTOR2M,HIGH);  
    }
    else
    {
        analogWrite(MOTOR2P,Speed);
        digitalWrite(MOTOR2M,LOW);  
    }    
  }

  
  if(M3_flag)
  {
     if(reverse)
    {
        analogWrite(MOTOR3P,Speed);
        digitalWrite(MOTOR3M,HIGH);  
    }
    else
    {
        analogWrite(MOTOR3P,Speed);
        digitalWrite(MOTOR3M,LOW);  
    }    
  }

 
  if(M4_flag)
  {
      if(reverse)
    {
      Serial.println("M4 reverse");
        analogWrite(MOTOR4P,Speed);
        digitalWrite(MOTOR4M,HIGH);  
    }
    else
    {
      Serial.print("M4 ");
        analogWrite(MOTOR4P,Speed);
        digitalWrite(MOTOR4M,LOW);  
    }    
  }

}

/****************************************************************************************************
 * Arduino main function
****************************************************************************************************/
void setup() {
  delay(10);
  Serial.begin(115200);
  Serial.println( "Reset");
//clearEEPROM();
 //delay(1000);
  readEEPROM();
  delay(10);
  initSensor();
    
  I2C_init((dev_id) << 1);
  Serial.print("device id:");
  Serial.println(dev_id);
  
  myServoB1.attach(_ZW_B1_);
  myServoB2.attach(_ZW_B2_);
  myServoB3.attach(_ZW_B3_);
  myServoB4.attach(_ZW_B4_);
  playPowerOn();
    
}

char Uart_Buf[64];
char bufindex;
int num = 0;

void loop() 
{
    
}
