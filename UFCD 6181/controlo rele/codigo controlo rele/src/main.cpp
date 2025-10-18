#include <Arduino.h>

#define RELAY_PIN1  12 
#define RELAY_PIN2  14

void setup() {

  pinMode(RELAY_PIN1, OUTPUT);
  pinMode(RELAY_PIN2, OUTPUT);

  digitalWrite(RELAY_PIN1, LOW);
  digitalWrite(RELAY_PIN2, HIGH);
}
void loop() {
  digitalWrite(RELAY_PIN2, HIGH);
  delay(200);  
  digitalWrite(RELAY_PIN1, LOW);
  delay(2000);

  digitalWrite(RELAY_PIN1, HIGH);
  delay(200);
  digitalWrite(RELAY_PIN2, LOW);
  delay(2000);


  

}
