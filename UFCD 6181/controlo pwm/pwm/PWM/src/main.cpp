#include <Arduino.h>

const int ledPin = D9; //Define LED Pin
const int freq = 5000;   //Set PWM signal frequency
const int ledChannel = 0;   //There are 16 channels from 0 to 15, set to PWM channel 0
const int resolution = 8;    //Set the duty cycle resolution of the signal, from 1 to 16 bits. Select 8-bit resolution here, ranging from 0 to 255

void setup(){
  ledcSetup(ledChannel,freq,resolution);
  ledcAttachPin(ledPin,ledChannel);    //Set the pin for outputting PWM signals and the channel for generating PWM signals

}

void loop(){
  for(int dutyCycle = 0;dutyCycle <= 255;dutyCycle++){
    ledcWrite(ledChannel,dutyCycle);   
    delay(50);
  }
  for(int dutyCycle = 255;dutyCycle >= 0;dutyCycle--){
    ledcWrite(ledChannel,dutyCycle);
    delay(50);
  }
}