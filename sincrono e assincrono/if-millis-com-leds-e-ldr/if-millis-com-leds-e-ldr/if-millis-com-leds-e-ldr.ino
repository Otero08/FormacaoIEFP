const int led1 = 8;
const int led2 = 9;
const int ledLDR = 10;
const int pinoLDR = A0;
const int limite = 300;  // Ajuste conforme necessário

unsigned long tempoAnterior = 0;
const int intervalo = 500;  // 500ms entre piscadas
bool estadoLed = false;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(ledLDR, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Controle dos LEDs piscando alternadamente
  if (millis() - tempoAnterior >= intervalo) {
    tempoAnterior = millis();
    estadoLed = !estadoLed;
    
    digitalWrite(led1, estadoLed);
    digitalWrite(led2, !estadoLed);
  }

  // Controle do LED via LDR
  int leituraLDR = analogRead(pinoLDR);
  Serial.println(leituraLDR);  // Monitorar no Serial Monitor

  if (leituraLDR < limite) {  
    digitalWrite(ledLDR, HIGH);  // Acende no escuro
  } else {
    digitalWrite(ledLDR, LOW);   // Apaga na claridade
  }
}
