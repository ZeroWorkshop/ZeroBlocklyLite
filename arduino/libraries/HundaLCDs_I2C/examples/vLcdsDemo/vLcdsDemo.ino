// IIC Wire lcd Master Writer
// by martin xhli <http://www.hundatech.com>

// This example code is in the public domain.

#include <LiquidCrystalDisplay.h>


const uint8_t String01[]="Password ok!";
const uint8_t String02[]="Password error!";
const uint8_t String03[]="Error";

const uint8_t String04[]="Input number ok!";
const uint8_t String05[]="Input number error!";

uint8_t   identifier,cnt;
uint8_t   cmd_buffer[CMD_MAX_SIZE];
uint8_t   data_size;
uint8_t   update_en;
uint8_t   command_cmd;
uint8_t   command_statu;
uint8_t   command_length;
uint8_t   page_Id_bk = 0;
uint8_t   page_Id = 0;
uint8_t   targe_Id = 0;

LiquidCrystal TFTlcd(13);//RST pin13

void setup()
{
   update_en =0;
   data_size =0;
   TFTlcd.queue_reset();
   
   Serial.begin(9600);
   Serial.println(F("Paint!"));
   TFTlcd.begin();

   attachInterrupt(0,LcdIICInterrupt,FALLING);//Interrupt 0 is D2 PIN
   TFTlcd.SetPage(4);//main page id is 4
}

void LcdIICInterrupt()
{
    command_cmd = TFTlcd.I2C_Read();
    TFTlcd.queue_push(command_cmd);
    for(cnt =0;cnt <2;cnt++)
    {
     identifier = TFTlcd.I2C_Read();
     TFTlcd.queue_push(identifier);
     //Serial.println(identifier, HEX);
    }
    command_statu = TFTlcd.I2C_Read();
    TFTlcd.queue_push(command_statu);
    identifier = TFTlcd.I2C_Read();
    TFTlcd.queue_push(identifier);
    command_length = TFTlcd.I2C_Read();
    TFTlcd.queue_push(command_length);
    if((command_cmd == GET_EDIT_VALUE && command_statu == 0x6f)||(command_cmd == GET_TOUCH_EDIT_VALUE && command_statu == 0x6f))
    {
       for(cnt =0;cnt <command_length;cnt++)
      {
       identifier = TFTlcd.I2C_Read();
       TFTlcd.queue_push(identifier);
       //Serial.println(identifier, HEX);
      }
    }
}

void loop()
{
	data_size = TFTlcd.queue_find_cmd(cmd_buffer,CMD_MAX_SIZE);
  if(data_size>0)//receive command
  {
    //Serial.println(data_size, HEX);
    Serial.println(F("ProcessMessage"));
    ProcessMessage((PCTRL_MSG)cmd_buffer, data_size);//command process
  } 

  if(update_en)
  {
    Serial.println(F("UpdateUI"));
    update_en = 0;
    delay(100);
    UpdateUI();
  }
}

void ProcessMessage( PCTRL_MSG msg, uint16_t dataSize )
{
    uint8_t cmd_type    = msg->cmd_type;
    uint8_t control_id  = msg->control_id;
    uint8_t page_id     = msg->page_id;
    uint8_t _status     = msg->status;
    uint8_t key_type    = msg->key_type;
    uint8_t key_value   = msg->key_value;
    switch(cmd_type)
    {
    case NOTIFY_TOUCH_BUTTON:
      NotifyTouchButton(page_id,control_id,_status,key_type,key_value);
      break;
  
    case NOTIFY_TOUCH_CHECKBOX:
      NotifyTouchCheckbox(page_id,control_id,_status,key_type,key_value);
      break;
  
    case NOTIFY_TOUCH_SLIDER:
      NotifyTouchSlider(page_id,control_id,_status,key_type,key_value);
      break;

    case NOTIFY_TOUCH_EDIT:
    NotifyTouchEdit(page_id,control_id,_status,key_type,key_value);
    break;
    
    case NOTIFY_GET_EDIT:
     NotifyGetEdit((PEDIT_MSG)cmd_buffer);
      break;

    case NOTIFY_GET_TOUCH_EDIT:
    NotifyGetTouchEdit((PEDIT_MSG)cmd_buffer);
    break;
  
    case NOTIFY_GET_PAGE:
      NotifyGetPage(page_id,_status);
      break;
  
    case NOTIFY_GET_CHECKBOX:
      NotifyGetCheckbox(page_id,control_id,_status,key_type,key_value);
      break;
  
    case NOTIFY_GET_SLIDER:
      NotifyGetSlider(page_id,control_id,_status,key_type,key_value);
      break;
      
    default:
      break;
  }
}

void UpdateUI()
{
    int i;
    int value;
    if(page_Id == Text_PAGE)
    {
      TFTlcd.SetNumberValue(page_Id,19,20);
      TFTlcd.SetNumberValue(page_Id,20,21);
      TFTlcd.SetNumberValue(page_Id,21,28);
      TFTlcd.SetNumberValue(page_Id,22,35);
      TFTlcd.SetNumberValue(page_Id,23,46);
      TFTlcd.SetNumberValue(page_Id,24,58);
      TFTlcd.SetLableValue(page_Id,16,(unsigned char *)String03);
      TFTlcd.SetLableValue(page_Id,17,(unsigned char *)String03);
      TFTlcd.SetLableValue(page_Id,18,(unsigned char *)String03);
    }
    else if(page_Id == Waveform_PAGE)
    {
       Serial.println(F("Waveform_PAGE"));
      for(i=-125;i<125;i+=1)
      {
        value = 20*sin(PI/50*i);
        TFTlcd.SetWaveformValue(page_Id,9,2,value+119);
        TFTlcd.SetWaveformValue(page_Id,9,1,value+59);
        delay(10);
      }
    }
    else if(page_Id == Temperture_PAGE)
    {
      value =20;
      for(i=0;i<=10;i+=1)
      {
        TFTlcd.SetThermometerValue(page_Id,9,value);
        TFTlcd.SetNumberValue(page_Id,11,value-20);
        value +=10;
        delay(200);
      }
  
      value =120;
      for(i=0;i<=10;i+=1)
      {
        TFTlcd.SetThermometerValue(page_Id,9,value);
        TFTlcd.SetNumberValue(page_Id,11,value-20);
        value -=10;
        delay(200);
      }
    }
    else if(page_Id == Slider_PAGE)
  {
    value =0;
    for(i=0;i<10;i+=1)
    {
      TFTlcd.SetProgressbarValue(page_Id,18,value);
      TFTlcd.SetProgressbarValue(page_Id,20,value);
      value +=10;
      delay(200);
    }
  }
  else if(page_Id == CircleGauge_PAGE)
  {
    value =0;
    for(i=0;i<=10;i+=1)
    {
      TFTlcd.SetCircleGaugeValue(page_Id,37,value);
      TFTlcd.SetBarGaugeValue(page_Id,40,value);
      
      value +=10;
      delay(200);
    }

    value =100;
    for(i=0;i<=10;i+=1)
    {
      TFTlcd.SetCircleGaugeValue(page_Id,37,value);
      TFTlcd.SetBarGaugeValue(page_Id,40,value);
      
      value -=10;
      delay(200);
    }
  }
  else if(page_Id == BarGauge_PAGE)
  {
    value =0;
    for(i=0;i<=10;i+=1)
    {
      TFTlcd.SetBatteryValue(page_Id,44,value);
      TFTlcd.SetWaterGaugeValue(page_Id,42,value);
      value +=10;
      delay(100);
    }

    value =100;
    for(i=0;i<=10;i+=1)
    {
      TFTlcd.SetBatteryValue(page_Id,44,value);
      TFTlcd.SetWaterGaugeValue(page_Id,42,value);
      value -=10;
      delay(100);
    }
  }
}

void NotifyTouchButton(uint8_t page_id, uint8_t control_id, uint8_t  state,uint8_t type,uint8_t value)
{
  //TODO:
  if(type == CHANGE_PAGE&& state == KEY_RELEASE)
  {
    page_Id = value;
    update_en = 1;
    //UpdateUI();
  }
  else if(type == ENTER&& state == KEY_RELEASE)
  {
    targe_Id = value;//targe Edit Id
     TFTlcd.GetEditValue(page_Id,targe_Id);
  }
  else if(type == CHAR)
  {
  
  }
  else if(type == UPLOAD_CONTROL_ID)
  {
  }
  else if(type == CLEAR)
  {
  }

}

void NotifyTouchCheckbox(uint8_t page_id, uint8_t control_id, uint8_t  state,uint8_t type,uint8_t value)
{
  //TODO:
  if(state == SELECT)
    update_en = 1;
  //UpdateUI();
}

void NotifyTouchSlider(uint8_t page_id, uint8_t control_id, uint8_t  state,uint8_t type,uint8_t value)
{
  //TODO:
  if(update_en != 1)
  TFTlcd.SetNumberValue(page_Id,28,(uint16_t)value);
  //UpdateUI();
}

void NotifyTouchEdit(uint8_t page_id, uint8_t control_id, uint8_t  state,uint8_t type,uint8_t value)
{
  //TODO:
  if(update_en != 1)
    TFTlcd.GetTouchEditValue(page_Id,control_id);
  
}

void NotifyGetEdit(PEDIT_MSG msg)
{
  uint8_t cmd_type    = msg->cmd_type;  //command
  uint8_t control_id  = msg->control_id;//object Id
  uint8_t page_id     = msg->page_id;   //page Id
  uint8_t _status     = msg->status;


  //The test passward number 1 2 3 4,ASCII code is 0x31 0x32 0x33 0x34
  if(msg->param[0] == 0x31 && msg->param[1] == 0x32 && msg->param[2] == 0x33 && msg->param[3] == 0x34)
  {
    TFTlcd.Display_Message(0X18,2,(unsigned char *)String01);  
  }
  else
  {
    TFTlcd.Display_Message(0X18,2,(unsigned char *)String02);  
  }
 
}

void NotifyGetTouchEdit(PEDIT_MSG msg)
{
  uint8_t cmd_type    = msg->cmd_type;  //command
  uint8_t control_id  = msg->control_id;//object Id
  uint8_t page_id     = msg->page_id;   //page Id
  uint8_t _status     = msg->status;


  //The test passward number 1 2 3 4,ASCII code is 0x31 0x32 0x33 0x34
  if(msg->param[0] == 0x31 && msg->param[1] == 0x32 && msg->param[2] == 0x33 && msg->param[3] == 0x34)
  {
    TFTlcd.Display_Message(0X18,2,(unsigned char *)String04);  
  }
  else
  {
    TFTlcd.Display_Message(0X18,2,(unsigned char *)String05);  
  }
 
}

void NotifyGetPage(uint8_t page_id,uint8_t status)
{
  //TODO:
  if(status == SUCCESS)
    page_Id = page_id;
}


void NotifyGetCheckbox(uint8_t page_id, uint8_t control_id, uint8_t  state,uint8_t type,uint8_t value)
{
  //TODO:
  if(state == SELECT)
  {
    update_en = 1;
  }
  //UpdateUI();
}

void NotifyGetSlider(uint8_t page_id, uint8_t control_id, uint8_t  state,uint8_t type,uint8_t value)
{
  //TODO:
  if(state == SUCCESS)
  {
    //success get value
  }
  update_en = 1;
}



