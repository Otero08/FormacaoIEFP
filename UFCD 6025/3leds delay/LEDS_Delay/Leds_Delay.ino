const int ledverde = 3;
const int ledazul = 4;
const int ledvermelho = 5;

const int intervalo = 500;

void setup()
{
  pinMode(ledverde, OUTPUT);
  pinMode(ledazul, OUTPUT);
  pinMode(ledvermelho, OUTPUT);
}

void loop() 
{
  digitalWrite(ledverde, HIGH);
  digitalWrite(ledazul,LOW);
  digitalWrite(ledvermelho,LOW);
  delay(intervalo);

  digitalWrite(ledverde, LOW);
  digitalWrite(ledazul,HIGH);
  digitalWrite(ledvermelho,LOW);
  delay(intervalo);

  digitalWrite(ledverde, LOW);
  digitalWrite(ledazul,LOW);
  digitalWrite(ledvermelho, HIGH);
  delay(intervalo);

  digitalWrite(ledverde, LOW);
  digitalWrite(ledazul,HIGH);
  digitalWrite(ledvermelho,LOW);
  delay(intervalo);

}