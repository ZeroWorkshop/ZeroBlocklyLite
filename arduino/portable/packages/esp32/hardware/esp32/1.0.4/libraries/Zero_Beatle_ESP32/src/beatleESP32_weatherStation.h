#include "NextionAll.h"

#include "Adafruit_BMP280.h" //https://github.com/Takatsuki0204/BME280-I2C-ESP32
#include <ArduinoJson.h>    //https://github.com/bblanchon/ArduinoJson
#include <WiFi.h>
//const char* ssid     = "zeroworkshop-2.4G";
//const char* password = "zerotech105";

String CityID = "1796236"; //Sparta, Greece
String APIKEY = "3c7da18a07454be9d2e4adf41a4638fb";
#define ALTITUDE 216.0 // Altitude in Sparta, Greece

#define I2C_SDA 21
#define I2C_SCL 22
#define LED_PIN 13

#define RXD2 16
#define TXD2 17

Adafruit_BMP280 bme;//(I2C_SDA, I2C_SCL);

WiFiClient client;
char* servername ="api.openweathermap.org";  // remote server we will connect to
String result;

#define FRESH_CYCLE  1000  //
int  iterations = 3600;
String weatherDescription ="";
String weatherLocation = "";
float temperature = 0;
float humidity = 0;
float pressure = 0;
int weatherID = 8;


NexPicture  pWeather = NexPicture(0, 8, "weather");
NexText     tTemperature = NexText(0, 2, "temperature");
NexText     tHumidity = NexText(0, 3, "humidity");
NexText     tPressure = NexText(0, 6, "pressure");
NexTimer    tm0 = NexTimer(0, 9, "tm0");

void initSensor();
void connectToWifi(const char* ssid, const char* password);
void getWeatherData();
float getTemperature();
float getPressure();
//float getHumidity();
void printWeatherIcon(int id);

void sendTemperatureToNextion()
{

  char buf[100];
  sprintf(buf, "%.1f", temperature);
  tTemperature.setText(buf);
  
}

void sendPressureToNextion()
{ 
  char buf[100];
  sprintf(buf, "%.1f", pressure);
  tPressure.setText(buf);
}

void drawFog()
{
pWeather.setPic(13);
}

void drawHeavySnowfall()
{
pWeather.setPic(8);
}

void drawModerateSnowfall()
{
pWeather.setPic(8);
}

void drawLightSnowfall()
{
pWeather.setPic(11);
}

void drawHeavyRain()
{
pWeather.setPic(10);
}

void drawModerateRain()
{
pWeather.setPic(6);
}

void drawLightRain()
{
pWeather.setPic(6);
}

void drawLightRainWithSunOrMoon()
{
 pWeather.setPic(7);
}
void drawThunderstorm()
{
 pWeather.setPic(3);
}

void drawClearWeather()
{
  pWeather.setPic(4);
}

void drawCloud()
{
   pWeather.setPic(9);
}

void drawFewClouds()
{
  pWeather.setPic(5);
}





/*
 * The timer respond function 
 * In this example,the timer will respond when set cycle time done and puls one for a variable. 
 */


void tm0TimerCallback(void *ptr)
{  
   if(iterations == 3600)  //update weather every 3600 * FRESH_CYCLE ms
   {
      getWeatherData();
      printWeatherIcon(weatherID);
      iterations = 0;   
   }  
   //update Temperature/Humidity/Pressure  every FRESH_CYCLE ms
   getTemperature();
   sendTemperatureToNextion();
//   getHumidity();
//   sendHumidityToNextion();
   getPressure();
   sendPressureToNextion();

   iterations++;
}

NexTouch *nex_listen_list[] = 
{
    &pWeather,
    &tTemperature ,
    &tHumidity,
    &tPressure,
    &tm0,
    NULL
};

void connectToWifi(const char* ssid, const char* password)
{

    dbSerialPrintln("Connecting to ");
    dbSerialPrintln(ssid);
    
  WiFi.enableSTA(true);
  
  delay(2000);

  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        dbSerialPrint(".");
    }

  dbSerialPrintln("");
  dbSerialPrintln("WiFi connected");
  dbSerialPrintln("IP address: ");
  dbSerialPrintln(WiFi.localIP());
}

void initSensor()
{
  bool status = bme.begin();
  if (!status) {
    dbSerialPrintln("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
}




float getTemperature()
{
  temperature = bme.readTemperature();
  dbSerialPrintln(F("BME280 temp = "));Serial.println(temperature);
}
//
//float getHumidity()
//{
//  humidity = bme.readHumidity();
//  dbSerialPrintln(F("BME280 humidity = "));Serial.println(humidity);
//}

float getPressure()
{
  pressure = bme.readPressure();
  pressure = bme.seaLevelForAltitude(ALTITUDE,pressure);
  pressure = pressure/100.0F;
  dbSerialPrintln(F("BME280 pressure = "));Serial.println(pressure);
}

void getWeatherData() //client function to send/receive GET request data.
{

  dbSerialPrintln("GetWeatherData");
  String result ="";
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(servername, httpPort)) {
        return;
    }
      // We now create a URI for the request
    String url = "/data/2.5/forecast?id="+CityID+"&units=metric&cnt=1&APPID="+APIKEY;

       // This will send the request to the server
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + servername + "\r\n" +
                 "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 5000) {
            client.stop();
            return;
        }
    }

    // Read all the lines of the reply from server
    while(client.available()) {
        result = client.readStringUntil('\r');
    }

result.replace('[', ' ');
result.replace(']', ' ');

char jsonArray [result.length()+1];
result.toCharArray(jsonArray,sizeof(jsonArray));
jsonArray[result.length() + 1] = '\0';

StaticJsonBuffer<1024> json_buf;
JsonObject &root = json_buf.parseObject(jsonArray);
if (!root.success())
{
  Serial.println("parseObject() failed");
}

String location = root["city"]["name"];
String temperature = root["list"]["main"]["temp"];
String weather = root["list"]["weather"]["main"];
String description = root["list"]["weather"]["description"];
String idString = root["list"]["weather"]["id"];
String timeS = root["list"]["dt_txt"];


dbSerialPrint(F("temperature = ")); dbSerialPrintln(temperature);
dbSerialPrint(F("weather     = ")); dbSerialPrintln(weather);

weatherID = idString.toInt();
dbSerialPrint("\nWeatherID: ");
dbSerialPrintln(weatherID);
//printWeatherIcon(weatherID);
}

void showConnectingIcon()
{
  pWeather.setPic(3);
}

//void sendHumidityToNextion()
//{
//  char buf[100];
//  
//  sprintf(buf, "%.1f", humidity);
//  tHumidity.setText(buf);
//}



void printWeatherIcon(int id)
{
 switch(id)
 {
  case 800: drawClearWeather(); break;
  case 801: drawFewClouds(); break;
  case 802: drawFewClouds(); break;
  case 803: drawCloud(); break;
  case 804: drawCloud(); break;
  
  case 200: drawThunderstorm(); break;
  case 201: drawThunderstorm(); break;
  case 202: drawThunderstorm(); break;
  case 210: drawThunderstorm(); break;
  case 211: drawThunderstorm(); break;
  case 212: drawThunderstorm(); break;
  case 221: drawThunderstorm(); break;
  case 230: drawThunderstorm(); break;
  case 231: drawThunderstorm(); break;
  case 232: drawThunderstorm(); break;

  case 300: drawLightRain(); break;
  case 301: drawLightRain(); break;
  case 302: drawLightRain(); break;
  case 310: drawLightRain(); break;
  case 311: drawLightRain(); break;
  case 312: drawLightRain(); break;
  case 313: drawLightRain(); break;
  case 314: drawLightRain(); break;
  case 321: drawLightRain(); break;

  case 500: drawLightRainWithSunOrMoon(); break;
  case 501: drawLightRainWithSunOrMoon(); break;
  case 502: drawLightRainWithSunOrMoon(); break;
  case 503: drawLightRainWithSunOrMoon(); break;
  case 504: drawLightRainWithSunOrMoon(); break;
  case 511: drawLightRain(); break;
  case 520: drawModerateRain(); break;
  case 521: drawModerateRain(); break;
  case 522: drawHeavyRain(); break;
  case 531: drawHeavyRain(); break;

  case 600: drawLightSnowfall(); break;
  case 601: drawModerateSnowfall(); break;
  case 602: drawHeavySnowfall(); break;
  case 611: drawLightSnowfall(); break;
  case 612: drawLightSnowfall(); break;
  case 615: drawLightSnowfall(); break;
  case 616: drawLightSnowfall(); break;
  case 620: drawLightSnowfall(); break;
  case 621: drawModerateSnowfall(); break;
  case 622: drawHeavySnowfall(); break;

  case 701: drawFog(); break;
  case 711: drawFog(); break;
  case 721: drawFog(); break;
  case 731: drawFog(); break;
  case 741: drawFog(); break;
  case 751: drawFog(); break;
  case 761: drawFog(); break;
  case 762: drawFog(); break;
  case 771: drawFog(); break;
  case 781: drawFog(); break;

  default:break; 
 }
}




void weathersation_setup(const char* ssid, const char* password) {
  // put your setup code here, to run once:

    nexInit();
    tm0.attachTimer(tm0TimerCallback);
    tm0.setCycle(FRESH_CYCLE);
    dbSerialPrintln("setup done"); 
    initSensor();
    connectToWifi(ssid, password);
}

void weathersation_loop() {
  // put your main code here, to run repeatedly:
  nexLoop(nex_listen_list);
}



