#include <Arduino.h>

void setup() 
{
  //configurar comunicaçao usb
  Serial.begin(9600);
}

void loop() 
{
  Serial.println("ola");
  delay(10000);
}

