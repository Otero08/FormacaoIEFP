unsigned long previous500 = 0; // Temporizador para 500ms
unsigned long previous1000 = 0; // Temporizador para 1000ms
bool state500 = LOW;  // Estado do LED que pisca a cada 500ms
bool state1000 = LOW; // Estado do LED que pisca a cada 1000ms

const int ldrPin = A0;  // Pino do LDR
const int ledLDR = 11;  // LED controlado pelo LDR
const int threshold = 500; // Limite para ativação do LED (ajustável)

void setup() {
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(ledLDR, OUTPUT);
  Serial.begin(9600); // Para debug (opcional)
}

void loop() {
  // Pisca o LED do pino 12 a cada 500ms
  if (millis() - previous500 >= 500) {
    previous500 = millis();
    state500 = !state500;
    digitalWrite(12, state500);
  }

  // Pisca o LED do pino 13 a cada 1000ms
  if (millis() - previous1000 >= 1000) {
    previous1000 = millis();
    state1000 = !state1000;
    digitalWrite(13, state1000);
  }

  // Lê o valor do LDR
  int ldrValue = analogRead(ldrPin);
  Serial.println(ldrValue); // Mostra o valor no monitor serial

  // Controla o LED 11 com base na luz
  if (ldrValue < threshold) {
    digitalWrite(ledLDR, HIGH); // Acende se estiver escuro
  } else {
    digitalWrite(ledLDR, LOW); // Apaga se houver luz suficiente
  }

  delay(10); // Pequena pausa para estabilidade da leitura do LDR
}
