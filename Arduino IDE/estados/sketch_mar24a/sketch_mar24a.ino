#include <Arduino.h>

enum State {
  OFF = 0,
  ON
};

State state = OFF;
unsigned long previousMillis = 0;
const unsigned long interval = 1000;

void setup() {
  Serial.begin(9600);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    switch (state) {
      case OFF:
        Serial.println("OFF");
        state = ON;
        break;
      case ON:
        Serial.println("ON");
        state = OFF;
        break;
      default:
        Serial.println("Error");
    }
  }
}