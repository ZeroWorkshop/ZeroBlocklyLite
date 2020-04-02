
//#ifdef _INCLUDE_RF_CONTROLLER_  
#include <PS2.h>
int Rx_Buffer[6];
int rfcontrol_temp[6];///

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
  #if	0
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

    if (inChar == 0xAA) {  //Find the head of a controller data. If AA is found, store it as the first byte of a rfcontrol_temp controller data.
      index = 0;
    }
    rfcontrol_temp[index++] = inChar;
    

    if (index == 6) valid_controller_data = true;  //If there is no another 0xAA before the first 6 byte end, it means the first 6-byte data is valid.
    else valid_controller_data = false;            //Otherwise the data captured is less than 6 bytes which is invalid data.

    if (valid_controller_data) {                   //Give the lastes valid data as the controller data.
      for (int i = 0; i < index; i++) {
        Rx_Buffer[i] = rfcontrol_temp[i];
#if 0        
        Serial.print("Latest Controller value is : ");
        Serial.println(Rx_Buffer[i], HEX);
#endif         
      }
    }
   
  }
#if 1
  Serial.print("***********                         0x");
  Serial.print(Rx_Buffer[2], HEX);
  Serial.print("\t0x");
  Serial.println(Rx_Buffer[3], HEX);
#endif
}



//#endif

