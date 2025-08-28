const int ldrPin = A0;
const int ledvermelho = 8;
const int ledverde = 9;
const int ventoinha = 10;

void setup() {
  pinMode(ledvermelho, OUTPUT);
  pinMode(ledverde, OUTPUT);
  pinMode(ventoinha, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int ldrValue = analogRead(ldrPin);

  if (ldrValue < 350) {
    digitalWrite(ledvermelho, HIGH); // LED acende em ambientes escuros
    digitalWrite(ledverde, LOW);
    Serial.print("Escuro - Valor LDR: Ligar Vermelho "); //escreve no serial monitor
    Serial.println(ldrValue);//escreve no serial monitor
    digitalWrite(ventoinha, LOW);
  } else {
    digitalWrite(ventoinha, HIGH);//liga ventoinha
    digitalWrite(ledverde, HIGH); // LED acende em com luz acima de 350 (lido pelo LDR)
    digitalWrite(ledvermelho, LOW);
    Serial.print("Claro - Valor LDR: Ligar Verde ");//escreve no serial monitor
    Serial.println(ldrValue);//escreve no serial monitor
  }
  delay(100); //atraso para estabilidade
}