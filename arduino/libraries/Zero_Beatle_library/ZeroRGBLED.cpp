#include "ZeroRGBLED.h"



// constructor (doesn't do anything)
ZeroRGBLED::ZeroRGBLED(uint8_t pin, uint8_t num)
{
	  initialized = false;
		_pin = pin;
		_num = num;
		//Serial.print("pin =");Serial.println(_pin);
		//Serial.print("num = ");Serial.println(_num);
		strip= Adafruit_NeoPixel(_num,_pin,NEO_GRB + NEO_KHZ800);
  
}

void ZeroRGBLED::init2()
{
	 strip.begin();
	  for(uint16_t i=0; i<_num; i++) {
    strip.setPixelColor(i, strip.Color(255,0,0));  
  }
	 strip.show(); 
}


// Fill 12 RGB to one color
void ZeroRGBLED::colorAll(uint32_t c) {
	init();// 
  for(uint16_t i=0; i<_num; i++) {
    strip.setPixelColor(i, c);  
  }
  strip.show();    
}


 
// Fill the dots one after the other with a color


void ZeroRGBLED::colorWipe(uint32_t c, uint8_t wait,uint8_t num_of_pin) {
	init();// 
	
	if(millis()- FStartT > wait)
	{
		for(int i = 0; i < num_of_pin;i++)
		{
			if(firstloop+i <_num) strip.setPixelColor(firstloop+i, c);   	
		}
		
	  if(firstloop>0)	
	  	
	  	strip.setPixelColor(firstloop-1, strip.Color(0,0,0));   	
   		strip.show();
   		FStartT = millis();
   	firstloop++;
   	if(firstloop >strip.numPixels() ) firstloop = 0;
	}
			
}  

void ZeroRGBLED::rainbow(uint8_t wait) {
	init();// 
  uint16_t i;

	if(millis()- FStartT > wait)
	{ 	
    for(i=0; i<strip.numPixels() ; i++) {
      strip.setPixelColor(i, Wheel((i+firstloop) & 255));
    }
    strip.show();
   	FStartT = millis();
  	firstloop++;
   	if(firstloop >256) firstloop = 0;
	}
}

// Slightly different, this makes the rainbow equally distributed throughout
void ZeroRGBLED::rainbowCycle(uint8_t wait) {
	init();// 
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< _num; i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / _num) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void ZeroRGBLED::theaterChase(uint32_t c, uint8_t wait) {
	init();// 
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < _num; i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < _num; i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
/*void ZeroRGBLED::theaterChaseRainbow(uint8_t wait) {
	init();// 
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < _num; i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < _num; i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}
*/
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t ZeroRGBLED::Wheel(byte WheelPos) {
	init();// 
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}




void ZeroRGBLED::theaterChaseRainbow(int wait) {
	init();// 
	
	///Serial.println("Led flash");
  for (int c = secondloop; c < strip.numPixels(); c += 3) {
    int hue = firstPixelHue + c * 65536L / strip.numPixels();
    uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
    strip.setPixelColor(c, color);
  }
  if (millis() - FStartT <= wait) {
    strip.show();
  }
  else {
    strip.clear();
    FStartT = millis();
    firstPixelHue += 65536 / 90;
    secondloop += 1;

    if (secondloop >= 3) {
      secondloop = 0;
      firstloop += 1;
    }
    if (firstloop >= 30) {
      firstloop = 0;
      firstPixelHue = 0;
    }
  }
}


void ZeroRGBLED::rainbow_stream(uint8_t wait) {
	init();// 
  for (int i = 0; i < strip.numPixels(); i++) {
    int pixelHue = firstPixelHue + (i * 65536L / _num);
    strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
  }
  if (millis() - FStartT > wait) {
    strip.show(); // Update strip with new contents
    FStartT = millis();
     firstPixelHue += 256;
    if (firstPixelHue > 3 * 65536)
      firstPixelHue = 0;
  }
}


void ZeroRGBLED::FlashOneLED_RGB(int flash_speed, uint8_t pixel, uint32_t c) {
	init();// 
  long flash_time;

  switch (flash_speed) {
  case FAST:
    flash_time = FLASH_DURATION * 0.2;
    break;
  case MIDDLE:
    flash_time = FLASH_DURATION * 0.6;
    break;
  case SLOW:
    flash_time = FLASH_DURATION * 1.0;
    break;
  }
  if (millis() - FStartT < flash_time / 2 ) {
    strip.setPixelColor(pixel, c);
    strip.show();
  }
  else if (millis() - FStartT < flash_time ) {
    strip.setPixelColor(pixel, strip.Color(0,0,0));
    strip.show();
  }
  else {
    FStartT = millis();
  }

}



void ZeroRGBLED::FlashOneLED_RGB(int flash_speed, uint8_t pixel, uint32_t c, int swap) {
	init();// 
  long flash_time;

  switch (flash_speed) {
  case FAST:
    flash_time = FLASH_DURATION * 0.2;
    break;
  case MIDDLE:
    flash_time = FLASH_DURATION * 0.6;
    break;
  case SLOW:
    flash_time = FLASH_DURATION * 1.0;
    break;
  }
  if (swap) {
    if (millis() - FStartT < flash_time / 2 ) {
      strip.setPixelColor(pixel, strip.Color(0,0,0));
      strip.show();
    }
    else if (millis() - FStartT < flash_time ) {
      strip.setPixelColor(pixel, c);
      strip.show();
    }
    else {
      FStartT = millis();
    }
  }
  else {
    if (millis() - FStartT < flash_time / 2 ) {
      strip.setPixelColor(pixel, c);
      strip.show();
    }
    else if (millis() - FStartT < flash_time ) {
      strip.setPixelColor(pixel, strip.Color(0,0,0));
      strip.show();
    }
    else {
      FStartT = millis();
    }
  }
}

void ZeroRGBLED::OneLED_RGB(uint8_t pixel, uint32_t c) {
	init();// 

  strip.setPixelColor(pixel, c);
  strip.show();

}


void ZeroRGBLED::policeLightWipe(int pix_num, int *pixel) {
	init();// 
  if (firstRun) {
    WipeStartTime = millis();
    firstRun = false;
  }

  if ((*pixel) < pix_num) {
    if (millis() - WipeStartTime < 100) {
      strip.setPixelColor((*pixel), ON_BLUE);
      strip.setPixelColor(pix_num - 1 - (*pixel), ON_RED);
      strip.show();
    }
    else {
      (*pixel)++;
      WipeStartTime = millis();
    }
  }
  else {
    if (millis() - WipeStartTime < 100) {
    	for (int i = 0; i < pix_num; i++) {
        OneLED_RGB(i, strip.Color(0,0,0));
      
      }
    }
    else {
      WipeStartTime = millis();
      (*pixel = pix_num / 2);
    }
  }
}


void ZeroRGBLED::policeLightFlash(int pix_num, int flashSpeed, int swap) {
	init();// 
  for (int i = 0; i < pix_num / 2; i++) {
    FlashOneLED_RGB(flashSpeed, i, ON_RED);
    FlashOneLED_RGB(flashSpeed, i + pix_num / 2, ON_BLUE, swap);
  }
}

void ZeroRGBLED::policeLightRun(int TotalPix, int *pixels) {
	init();// 

  if (millis() - policeLightStart < 4000) {
    policeLightFlash(TotalPix, MIDDLE, UNSWAP);
  }
  else if (millis() - policeLightStart < 10000) {
    policeLightFlash(TotalPix, SLOW, SWAP);
  }
  else if (millis() - policeLightStart < 15000) {
    policeLightWipe(TotalPix, pixels);
  }
  else if (millis() - policeLightStart < 20000) {
    policeLightFlash(TotalPix, FAST, UNSWAP);
  }
  else
    policeLightStart = millis();


}