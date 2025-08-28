//defenir pinos
const int verde = 4;
const int vermelho = 5;
const int amarelo = 7;
int estado = 1;


unsigned long tempo = 0;

void setup(){
pinMode (4, OUTPUT);
pinMode (5, OUTPUT);
pinMode (7, OUTPUT);
Serial.begin(9600);
}

void loop(){


if (millis() - tempo >= 5000)
{  tempo = millis();
  if (estado == 1)
  {
  Serial.println("verde");
  digitalWrite(verde, HIGH);
  digitalWrite(amarelo,LOW);
  digitalWrite(vermelho, LOW);
  }
  else if (estado == 2)
  {
   Serial.println("amarelo");
  digitalWrite(verde, LOW);
  digitalWrite(amarelo,HIGH);
  digitalWrite(vermelho, LOW);
  }
    else if (estado == 3)
  {
  Serial.println("vermelho");
  digitalWrite(verde, LOW);
  digitalWrite(amarelo,LOW);
  digitalWrite(vermelho, HIGH);
  }
  estado ++;
  if (estado >3)
  {
    estado = 1;
  }

}

}
  

