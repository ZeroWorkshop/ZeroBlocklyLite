
int x;//缓存函数
String comdata = "";//字符串函数

String getButtontValue() {
  String comdata_temp = "";//缓存清零
  if (Serial2.available() > 0)//判读是否串口有数据
  {
    
    while (Serial2.available() > 0)//循环串口是否有数据
    {
      comdata_temp += char(Serial2.read());//叠加数据到comdata_temp
      //delay(2);//延时等待响应
    }
    if (comdata_temp.length() > 0)//如果comdata_temp有数据
    {
      /*
      Serial.println(comdata_temp);//打印comdata_temp数据
      if (!comdata_temp.compareTo("chup"))
      {
        Serial.println("channel UP is pressed");
        
      }
      else if (!comdata_temp.compareTo("chdown"))
      {
        Serial.println("channel DOWN is pressed");
        
      }
      else if (!comdata_temp.compareTo("volup"))
      {
        Serial.println("volume UP is pressed");
        
      }
      else if (!comdata_temp.compareTo("voldown"))
      {
        Serial.println("volume down is pressed");
        
      }
      else if (!comdata_temp.compareTo("tempup"))
      {
        Serial.println("temperature UP is pressed");
        
      }
      else if (!comdata_temp.compareTo("tempdown"))
      {
        Serial.println("temperature DOWN is pressed");
        
      }
      else if (!comdata_temp.compareTo("windup"))
      {
        Serial.println("wind UP is pressed");
        
      }
      else if (!comdata_temp.compareTo("winddown"))
      {
        Serial.println("wind DOWN is pressed");
        
      }
      */
    }
    
  }
  return comdata_temp;
}