const int amarelo = 9;
unsigned long tempo = 0;


void setup()
{
  pinMode(amarelo, OUTPUT);
}

void loop()
{
	if (millis()-tempo>=1500) 
    {
      if (digitalRead(amarelo))
      {
        digitalWrite(amarelo,LOW);
      }
      else
      {
        digitalWrite(amarelo,HIGH);
      }
      tempo = millis();
    }
}