#include<Adafruit_NeoPixel.h>

#define RGB_PIN  2
#define RGB_NUM  12
#define BRIGHT   64

#define FLASH_DURATION 		200
#define SLOW   						2
#define MIDDLE 						1
#define FAST   						0


#define OFF        				0
#define ON         				1
#define SCALE      				1

#define SWAP              1
#define UNSWAP            0

#define LED_MAX_BRIGHT    255 / SCALE
#define ON_WHITE_MAX   		strip.Color(255, 255, 255)
#define ON_WHITE   				strip.Color(255 / SCALE, 255 / SCALE, 255 / SCALE)

#define ON_RED_MAX     		strip.Color(0 ,  255, 0)
#define ON_GREEN_MAX 	  	strip.Color(255, 0 ,  0)
#define ON_BLUE_MAX   		strip.Color(0,   0,   255)
#define ON_YELLOW_MAX			strip.Color(255, 255, 0)
#define ON_WHITE_MAX			strip.Color(255, 255, 255)


#define ON_RED     				strip.Color(255 / SCALE, 0,           0)
#define ON_GREEN   				strip.Color(0,           255 / SCALE, 0)
#define ON_BLUE    				strip.Color(0,           0,           255 / SCALE)
#define ON_YELLOW  				strip.Color(255 / SCALE, 255 / SCALE, 0)

#define ON_CYAN    				strip.Color(0,           255 / SCALE, 255 / SCALE)
#define ON_YELLOW  				strip.Color(255 / SCALE, 255 / SCALE, 0)
#define ON_MAGENTA 				strip.Color(255 / SCALE, 0,           255 / SCALE)
#define ON_PURPLE  				strip.Color(128 / SCALE, 0,           128 / SCALE)
#define OFF_RGB    				strip.Color(0,           0,           0)
	

class ZeroRGBLED_ESP32: public Adafruit_NeoPixel
{
public:
	
 

  ZeroRGBLED_ESP32(uint8_t pin = RGB_PIN,uint8_t num = RGB_NUM);
 // ZeroRGBLED_ESP32::ZeroRGBLED_ESP32(uint8_t pin = RGB_PIN, uint8_t num= RGB_NUM, uint8_t ;
   
  Adafruit_NeoPixel  strip;// = Adafruit_NeoPixel(RGB_NUM,RGB_PIN,NEO_GRB + NEO_KHZ800);
 
  void colorWipe(uint32_t c, uint8_t wait=50,uint8_t num_of_pin=1 );
  void colorAll(uint32_t c) ; //set the color of all LED

  void rainbow(uint8_t wait) ;
  void rainbowCycle(uint8_t wait);
  void theaterChase(uint32_t c, uint8_t wait) ;
  //void theaterChaseRainbow(uint8_t wait);
  uint32_t Wheel(byte WheelPos) ;

  
 //void rainbow_stream(uint8_t wait, long *firstPixHue);
  void rainbow_stream(uint8_t wait);
  void theaterChaseRainbow(int wait); 
  void FlashOneLED_RGB(int flash_speed, uint8_t pixel, uint32_t c);
	void FlashOneLED_RGB(int flash_speed, uint8_t pixel, uint32_t c, int swap) ;
  void OneLED_RGB(uint8_t pixel, uint32_t c);
  void policeLightWipe(int pix_num, int *pixel);
  void policeLightFlash(int pix_num, int flashSpeed, int swap);
  void policeLightRun(int TotalPix, int *pixels);
  
  void setBrightness(int value);
  
  void init()
  {
    if (!initialized)
    {
      initialized = true;
      init2();
      Serial.println("init");
    }

  }

    
private:
	int _num;
	int _pin;
	
	
	int _brightness;
	
  bool firstRun = true;
  
  unsigned long FStartT = 0;
	long firstPixelHue = 0;
	int firstloop = 0;
	int secondloop = 0;
	
  unsigned long WipeStartTime = 0;
  unsigned long FlashStartTime = 0;
  unsigned long policeLightStart = 0;
    
	

 void init2();

 bool initialized;
  
 
};