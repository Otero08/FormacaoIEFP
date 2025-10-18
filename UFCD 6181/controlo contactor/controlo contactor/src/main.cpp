#include <Arduino.h>

#define contactor_PIN 12 

void setup() {

  pinMode(contactor_PIN, OUTPUT);
  digitalWrite(contactor_PIN, LOW); 
}


void loop() {

  digitalWrite(contactor_PIN, HIGH); 
  delay(200); 
  delay(2000); 
  digitalWrite(contactor_PIN, LOW);
  delay(200);
  delay(2000); 
}