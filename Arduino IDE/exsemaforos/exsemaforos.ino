// Definição dos pinos dos LEDs para os dois semáforos
const int vermelho1 = 8;
const int amarelo1 = 9;
const int verde1 = 10;

const int vermelho2 = 11;
const int amarelo2 = 12;
const int verde2 = 13;

unsigned long tempoAnterior = 0;
int estado = 0; // Estado do semáforo

void setup() {
  pinMode(vermelho1, OUTPUT);
  pinMode(amarelo1, OUTPUT);
  pinMode(verde1, OUTPUT);

  pinMode(vermelho2, OUTPUT);
  pinMode(amarelo2, OUTPUT);
  pinMode(verde2, OUTPUT);
}

void loop() {
  unsigned long tempoAtual = millis();

  switch (estado) {
    case 0:  // 🔴 Semáforo 1: Vermelho | 🟢 Semáforo 2: Verde
      digitalWrite(vermelho1, HIGH);
      digitalWrite(amarelo1, LOW);
      digitalWrite(verde1, LOW);
      
      digitalWrite(vermelho2, LOW);
      digitalWrite(amarelo2, LOW);
      digitalWrite(verde2, HIGH);

      if (tempoAtual - tempoAnterior >= 20000) { // 20s
        tempoAnterior = tempoAtual;
        estado = 1;
      }
      break;

    case 1:  // 🟡 Semáforo 2: Amarelo | 🟢 Semáforo 1: Ainda Vermelho
      digitalWrite(vermelho2, LOW);
      digitalWrite(amarelo2, HIGH);
      digitalWrite(verde2, LOW);

      if (tempoAtual - tempoAnterior >= 5000) { // 5s
        tempoAnterior = tempoAtual;
        estado = 2;
      }
      break;

    case 2:  // 🟢 Semáforo 1: Verde | 🔴 Semáforo 2: Vermelho
      digitalWrite(verde1, HIGH);
      digitalWrite(amarelo1, LOW);
      digitalWrite(vermelho1, LOW);
      
      digitalWrite(vermelho2, HIGH);
      digitalWrite(amarelo2, LOW);
      digitalWrite(verde2, LOW);

      if (tempoAtual - tempoAnterior >= 20000) { // 20s
        tempoAnterior = tempoAtual;
        estado = 3;
      }
      break;

    case 3:  // 🟡 Semáforo 1: Amarelo | 🔴 Semáforo 2: Ainda Vermelho
      digitalWrite(verde1, LOW);
      digitalWrite(amarelo1, HIGH);
      digitalWrite(vermelho1, LOW);

      if (tempoAtual - tempoAnterior >= 5000) { // 5s
        tempoAnterior = tempoAtual;
        estado = 0; // Volta para o primeiro estado
      }
      break;
  }
}
