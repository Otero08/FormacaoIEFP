//def led
const int  amarelo = 13 ;

unsigned long tempoant = millis();

//def tempo

void setup()
{
  pinMode (13, OUTPUT);
  Serial.begin(9600);
}
void loop()
{ 
  if (millis() - tempoant >= 1000)
  {
    if(digitalRead(amarelo))
  
    {
      Serial.println("Desligar LED");
      digitalWrite(amarelo,LOW);
    }
    else 
    {
    Serial.println("Ligar LED");
    digitalWrite(amarelo,HIGH);
    }
  tempoant = millis();

}


}
   