#include <Arduino.h>
#include <avr/io.h>
#include <util/twi.h>
#include <avr/interrupt.h>
#include <EEPROM.h>
#include "Stepper.h"
#include "Starter_I2CSlave.h"

//Print message priority
//#define DEBUG_INFO_ERROR
//#define DEBUG_INFO_HIGH  
//#define DEBUG_INFO_MID
//#define DEBUG_INFO_LOW
#define DEBUG_INFO

//Common parameter configuration
#define DEFAULT_I2C_ADDR    0x09
#define DEFAULT_TIME_OUT    2000



#define M1   0b1000
#define M2   0b0100
//#define M3   0b0010
//#define M4   0b0001

#define M1M2  0b1100
//#define M1M3  0b1010
//#define M1M4  0b1001

//#define M2M3  0b0110
//#define M2M4  0b0101

//#define M3M4  0b0011

//#define M1M2M3  0b1110
//#define M1M2M4  0b1101
//#define M1M3M4  0b1011
//#define M2M3M4  0b0111

//#define M1M2M3M4  0b1111

#define STEPS   200
Stepper stepper(STEPS,4,5,7,6);

static void (*reset_this_CPU)(void) = 0x0000;


 unsigned long last_step_time  = 0; 
 int number_of_steps = 200;      // total number of steps this motor can take
 int step_number = 0;          // which step the motor is on

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
  Serial.print("cmd:");
  Serial.println(cmd);
//  Serial.print("pin ");Serial.print(slot);
//  Serial.print("  ");
//  Serial.println(val.longVal[0]);
#endif
  switch(cmd){
    // move state and function
    case CMD_RESET:
      resetBroad();
      break;
      case CMD_GET_POWER_VOL:
      get_power_voltage();
      memcpy(&bufI2C[0],&pin_data.voltage,4);
     
      break;
      case CMD_SET_PIN_TYPE:
        pinMode(slot,val.byteVal[0]);
      break;
      case CMD_SET_PIN_DIGITAL_VAL:
        pinMode(slot,OUTPUT);
        digitalWrite(slot,val.byteVal[0]);
        Serial.print("pin ");
        Serial.print(slot);
        Serial.print("   value = ");
        Serial.println(val.byteVal[0]);
      break;
       case CMD_SET_PIN_ANALOG_VAL:
        pinMode(slot,OUTPUT);
        analogWrite(slot,val.longVal[0]);
      break;
      case CMD_SET_MOTOR:
      MotorControl(slot,(uint8_t)val.longVal[0],val.longVal[1]);
      break;
      case CMD_SET_STEPPER:
      
      stepper.setSpeed(val.longVal[0]);
      stepper.step(val.longVal[1]);
      //StepperContorl(slot,val.longVal[0],val.longVal[1]);
      Serial.print("stepper = ");Serial.print(slot);
      Serial.print("Speed = ");Serial.print(val.longVal[0]);
      Serial.print("steps to move = ");Serial.println(val.longVal[1]);
      break;
      case CMD_GET_PIN_TYPE:
      break;
      case CMD_GET_PIN_DIGITAL_VAL:
          digitalReadSlave(slot);
          memcpy(&bufI2C[0],&_value,4);
          break;
      case CMD_GET_PIN_ANALOG_VAL:
          analogReadSlave(slot);
        
          memcpy(&bufI2C[0],&_value,4);
          break;
      case CMD_SET_DEVID:
        setDevid(val.byteVal[0]);
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
 //  pinMode(StarterProEEPROM.M3P,OUTPUT);
 //  pinMode(StarterProEEPROM.M3N,OUTPUT);
 //  pinMode(StarterProEEPROM.M4P,OUTPUT);
 //  pinMode(StarterProEEPROM.M4N,OUTPUT);
   digitalWrite(StarterProEEPROM.M1P,LOW);
   digitalWrite(StarterProEEPROM.M1N,LOW);
   digitalWrite(StarterProEEPROM.M2P,LOW);
   digitalWrite(StarterProEEPROM.M2N,LOW);
 //  digitalWrite(StarterProEEPROM.M3P,LOW);
 //  digitalWrite(StarterProEEPROM.M3N,LOW);
 //  digitalWrite(StarterProEEPROM.M4P,LOW);
 //  digitalWrite(StarterProEEPROM.M4N,LOW);

}

void get_power_voltage()
{
    pin_data.voltage = analogRead(A6);
    Serial.print("voltage = "); Serial.println(pin_data.voltage);;
    //memcpy(&bufI2C[0],&pin_data.voltage,4);
  
}

 
void MotorControl(uint8_t MotorNumber, long RunningStatus,long Speed) {

  int M1_flag, M2_flag,M3_flag,M4_flag;

  //M4_flag = MotorNumber & 0b0001;
  //M3_flag = (MotorNumber & 0b0010) >> 1;
  M2_flag = (MotorNumber & 0b0100) >> 2;
  M1_flag = (MotorNumber & 0b1000) >> 3;


  if(M1_flag)
  {
      if (RunningStatus == FORWARD) {     
     
       digitalWrite(MOTOR1P, HIGH);
		 int PWMvalue = 255 - Speed;
 		 analogWrite(MOTOR1M, PWMvalue);
    
    }
    else if (RunningStatus == BACKWARD) {
      digitalWrite(MOTOR1P, LOW);
	    analogWrite(MOTOR1M, Speed);
   
    }
    else if (RunningStatus == STOP) {
      digitalWrite(MOTOR1P, LOW);
      digitalWrite(MOTOR1M, LOW);
    }
  }

  
  if(M2_flag)
  {
      if (RunningStatus == FORWARD) {     
         digitalWrite(MOTOR2P, HIGH);
		 int PWMvalue = 255 - Speed;
 		 analogWrite(MOTOR2M, PWMvalue);
    
    }
    else if (RunningStatus == BACKWARD) {
      digitalWrite(MOTOR2P, LOW);
	    analogWrite(MOTOR2M, Speed);
   
    }
    else if (RunningStatus == STOP) {
      digitalWrite(MOTOR2P, LOW);
      digitalWrite(MOTOR2M, LOW);
    }
  }

 
  

   //Serial.println(MotorNumber);
  // Serial.print("M1_falg  = ");Serial.print(M1_flag);
  // Serial.print(" M2_falg  = ");Serial.print(M2_flag);
  // Serial.print(" M3_falg  = ");Serial.print(M3_flag);
  // Serial.print(" M4_falg  = ");Serial.println(M4_flag);
 /* switch (MotorNumber) {
  case 1:
    if (RunningStatus == FORWARD) {
     Serial.println("forward");
     
      analogWrite(MOTOR1P, Speed);
      digitalWrite(MOTOR1M, HIGH);
    
    }
    else if (RunningStatus == BACKWARD) {
    Serial.println("backward");
      analogWrite(MOTOR1P, Speed);
      digitalWrite(MOTOR1M, LOW);
   
    }
    else if (RunningStatus == STOP) {
      digitalWrite(MOTOR1P, LOW);
      digitalWrite(MOTOR1M, LOW);
    }
    break;
  case 2:
    if (RunningStatus == FORWARD) {
    
      analogWrite(MOTOR2P, Speed);
      digitalWrite(MOTOR2M, HIGH);
      
   
    }
    else if (RunningStatus == BACKWARD) {
     
      analogWrite(MOTOR2P, Speed);
      digitalWrite(MOTOR2M, LOW);
     
    }
    else if (RunningStatus == STOP) {
      digitalWrite(MOTOR2P, LOW);
      digitalWrite(MOTOR2M, LOW);
    }
    break;
  case 3:
    if (RunningStatus == FORWARD) {
     
      analogWrite(MOTOR3P, Speed);
      digitalWrite(MOTOR3M, HIGH);
   
    }
    else if (RunningStatus == BACKWARD) {
      
      analogWrite(MOTOR3P, Speed);
      digitalWrite(MOTOR3M, LOW);
     
    }
    else if (RunningStatus == STOP) {
      digitalWrite(MOTOR3P, LOW);
      digitalWrite(MOTOR3M, LOW);
      
    }
    break;
  case 4:
    if (RunningStatus == FORWARD) {
  
      analogWrite(MOTOR4P, Speed);
      digitalWrite(MOTOR4M, HIGH);
     
    }
    else if (RunningStatus == BACKWARD) {
    
      analogWrite(MOTOR4P, Speed);
      digitalWrite(MOTOR4M, LOW);
      
  
    }
    else if (RunningStatus == STOP) {
      digitalWrite(MOTOR4P, LOW);
      digitalWrite(MOTOR4M, LOW);
    }
    break;
  default:
    break;
  }*/
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
  
  
}

char Uart_Buf[64];
char bufindex;
int num = 0;

void loop() 
{
    
  
 
}


