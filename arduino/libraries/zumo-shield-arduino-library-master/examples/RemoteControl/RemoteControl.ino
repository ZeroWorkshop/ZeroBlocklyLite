#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include <ZumoShield.h>


#define SPEED  255
ZumoBuzzer buzzer;
ZumoReflectanceSensorArray reflectanceSensors;
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);



#define DSL  11
#define DSR  13 

#define RGB_PIN 2
#define RGB_NUM 12

Adafruit_NeoPixel strip = Adafruit_NeoPixel(RGB_NUM, RGB_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:  
  Serial.begin(115200);
  pinMode(DSL,INPUT);
  pinMode(DSR,INPUT);
  strip.begin();
  //strip.show(); // Initialize all pixels to 'off'
  colorWipe(strip.Color(255, 0, 0), 50); // Red
  colorWipe(strip.Color(0, 255, 0), 50); // Green
  colorWipe(strip.Color(0, 0, 255), 50); // Blue
  buzzer.play(">g32>>c32");

  button.waitForButton(); 

  // Play music and wait for it to finish before we start driving.
  buzzer.play("L16 cdegreg4");
  while(buzzer.isPlaying());
  

}

void loop() {
  // put your main code here, to run repeatedly:
    

if ( _ButtonUp)
  {
   motors.setSpeeds(SPEED, SPEED);
  }
  else if( _ButtonDown)
  {
   motors.setSpeeds(-SPEED, -SPEED);
  }
  else if(_ButtonLeft)
  {
     motors.setSpeeds(-SPEED, SPEED);    
  }
  else if(_ButtonRight)
  {
      motors.setSpeeds(SPEED, -SPEED);
  }
  else
 {
     motors.setSpeeds(0, 0);
 }
}



// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

