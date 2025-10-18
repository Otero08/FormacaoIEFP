#include <Arduino.h>


int intervalo = 2000;

void loop() {
  if(millis() - intervalo < 4000 ){
    printf("ZZZZ");

  }
  printf("ooooo");
}
