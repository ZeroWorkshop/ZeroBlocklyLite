#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include <ZumoShield.h>

#define DSL  11
#define DSR  13 
#define RGB_PIN 2
#define RGB_NUM 12

#define SPEED  255
ZumoBuzzer buzzer;
ZumoReflectanceSensorArray reflectanceSensors;
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);


Adafruit_NeoPixel  rgb_display_ZW_A1= Adafruit_NeoPixel(RGB_NUM,RGB_PIN,NEO_GRB + NEO_KHZ800);

int LeftValue;
int RightValue;

int Type = 0;


double FStartT = 0;
long firstPixelHue = 0;
int firstloop = 0;
int secondloop = 0;

void theaterChaseRainbow(int wait, long *firstPixHue, int *outerloop, int *innerloop) {
  for (int c = *innerloop; c < rgb_display_ZW_A1.numPixels(); c += 3) {
    int hue = *firstPixHue + c * 65536L / rgb_display_ZW_A1.numPixels();
    uint32_t color = rgb_display_ZW_A1.gamma32(rgb_display_ZW_A1.ColorHSV(hue)); // hue -> RGB
    rgb_display_ZW_A1.setPixelColor(c, color);
  }
  if (millis() - FStartT <= wait) {
    rgb_display_ZW_A1.show();
  }
  else {
    rgb_display_ZW_A1.clear();
    FStartT = millis();
    *firstPixHue += 65536 / 90;
    *innerloop += 1;

    if (*innerloop >= 3) {
      *innerloop = 0;
      *outerloop += 1;
    }
    if (*outerloop >= 30) {
      *outerloop = 0;
      *firstPixHue = 0;
    }
  }
}

void rainbow_stream(uint8_t wait, long *firstPixHue) {
  for (int i = 0; i < rgb_display_ZW_A1.numPixels(); i++) {
    int pixelHue = *firstPixHue + (i * 65536L / rgb_display_ZW_A1.numPixels());
    rgb_display_ZW_A1.setPixelColor(i, rgb_display_ZW_A1.gamma32(rgb_display_ZW_A1.ColorHSV(pixelHue)));
  }
  if (millis() - FStartT > wait) {
    rgb_display_ZW_A1.show(); // Update strip with new contents
    FStartT = millis();
     *firstPixHue += 256;
    if (*firstPixHue > 3 * 65536)
      *firstPixHue = 0;
  }
}

void setup() {
  // put your setup code here, to run once:

  pinMode(DSL,INPUT);
  pinMode(DSR,INPUT);
  Serial.begin(115200);
  rgb_display_ZW_A1.begin();
  //strip.show(); // Initialize all pixels to 'off'
  for(int i = 0; i<200; i++)
  rainbow_stream(20, &firstPixelHue);
  
  buzzer.play(">g32>>c32");

  button.waitForButton(); 

  // Play music and wait for it to finish before we start driving.
  buzzer.play("L16 cdegreg4");
  while(buzzer.isPlaying());


}

void loop() {
  // put your main code here, to run repeatedly:

  LeftValue = digitalRead(DSL);
  RightValue = digitalRead(DSR);

  //theaterChaseRainbow(20, &firstPixelHue, &firstloop, &secondloop);
  rainbow_stream(2, &firstPixelHue);
  if((LeftValue == 0) && (RightValue == 0))
  {
     //colorWipe(strip.Color(255, 0, 0), 50);  
     motors.setSpeeds(-SPEED, -SPEED);
     delay(300);
     motors.setSpeeds(SPEED, -SPEED);
     delay(200);
  }
   if(LeftValue == 0)
  {
    // colorWipe(strip.Color(0, 255, 0), 50);  
    motors.setSpeeds(SPEED, -SPEED);
    delay(200);
  }
  else if(RightValue == 0)
  {

    //colorWipe(strip.Color(0, 0, 255), 50);  
    motors.setSpeeds(-SPEED, SPEED);
    delay(200);
  }
  else
  {
    //colorWipe(strip.Color(127, 127, 127), 50); 
    motors.setSpeeds(SPEED, SPEED);
  }
  

}

