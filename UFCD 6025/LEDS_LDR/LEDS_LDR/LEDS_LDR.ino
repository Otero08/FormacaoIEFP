const int led1 = 2;
const int led2 = 3;
const int led3 = 4;

const int pinoLDR = A0;
const int ledLDR = 8;
const int limite = 200;

unsigned long tempoAnterior = 0;
const long intervalo = 500;

int ledAtual = 1;
int direcao = 1; // 1 para frente, -1 para trás

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(ledLDR, OUTPUT);
  pinMode(pinoLDR, INPUT);
  Serial.begin(9600);
}

void loop() {
  if (millis() - tempoAnterior >= intervalo) {
    tempoAnterior = millis();

    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);

    if (ledAtual == 1) {
      digitalWrite(led1, HIGH);
    } else if (ledAtual == 2) {
      digitalWrite(led2, HIGH);
    } else if (ledAtual == 3) {
      digitalWrite(led3, HIGH);
    }

    ledAtual += direcao;

    if (ledAtual > 3) {
      ledAtual = 2;
      direcao = -1;
    } else if (ledAtual < 1) {
      ledAtual = 2;
      direcao = 1;
    }
  }
  int leituraLDR = analogRead(pinoLDR);
  Serial.println(leituraLDR);
  

  if (leituraLDR < 5) {  
    digitalWrite(ledLDR, HIGH);  // acende sem luz
  } else {
    digitalWrite(ledLDR, LOW);   // Aapaga com luz
  }
}