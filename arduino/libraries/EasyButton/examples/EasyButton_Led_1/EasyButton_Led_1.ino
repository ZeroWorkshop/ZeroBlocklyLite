#include <EasyButton.h>

const int buttonPin = A0;
const int ledPin = A2;

EasyButton button(buttonPin);

void setup() 
{
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
}

void loop() 
{
  button.update();

  if (button.IsPushed())
    digitalWrite(ledPin, HIGH);
 if(button.IsPushed())
    Serial.println("button is IsPushed");
    if(button.IsHold())
    Serial.println("button is hold");
 if(button.IsRelease())
    Serial.println("button is IsRelease");
    
}

