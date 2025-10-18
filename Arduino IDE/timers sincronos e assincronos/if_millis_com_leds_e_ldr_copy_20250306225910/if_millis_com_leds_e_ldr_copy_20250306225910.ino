const int led1 = 8;
const int led2 = 9;
const int ledLDR = 13;
const int pinoLDR = A0;
const int limite = 500;


unsigned long tempoAnterior = 0;
const int intervalo = 500;  // 5s entre os leds
bool estadoLed = false;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(ledLDR, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // controla o piscar dos led alternado
  if (millis() - tempoAnterior >= intervalo) {
    tempoAnterior = millis();
    estadoLed = !estadoLed; //inverte o estado do led e regista
    
    digitalWrite(led1, estadoLed);
    digitalWrite(led2, !estadoLed);
  }

  // Controle do LED via LDR
  int leituraLDR = analogRead(pinoLDR);
  Serial.println(leituraLDR);

  if (leituraLDR < limite) {  
    digitalWrite(ledLDR, HIGH);  // acende sem luz
  } else {
    digitalWrite(ledLDR, LOW);   // Aapaga com luz
  }
}
