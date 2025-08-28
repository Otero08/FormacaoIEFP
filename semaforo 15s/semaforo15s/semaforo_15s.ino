//def variaveis
const int verde = 4;
const int amarelo = 7;
const int vermelho = 9;
int estado = 1;

unsigned long tempo = 0;


void setup ()
{
  pinMode(4,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(9,OUTPUT);
}
void loop ()
{
  if(millis()- tempo>=5000)
  {
    tempo = millis();
    if (estado==1)
    {
    digitalWrite(verde, HIGH);
    digitalWrite(amarelo, LOW);
    digitalWrite(vermelho, LOW);
    }
    else if (estado ==2)
    {
    digitalWrite(verde, LOW);
    digitalWrite(amarelo, HIGH);
    digitalWrite(vermelho, LOW);
    }
    else if (estado ==3)
    {
    digitalWrite(verde, LOW);
    digitalWrite(amarelo, LOW);
    digitalWrite(vermelho, HIGH);
    }
    estado = estado + 1;
    if (estado > 3)
    {
      estado = 1;
    }
   }
}