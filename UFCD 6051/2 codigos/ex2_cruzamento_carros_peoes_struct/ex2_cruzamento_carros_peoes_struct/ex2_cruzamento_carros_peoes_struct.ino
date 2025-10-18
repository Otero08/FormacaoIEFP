struct sem_carros {
  unsigned int tempo_vermelho;
  unsigned int tempo_amarelo;
  unsigned int tempo_verde;
  int led_vermelho;
  int led_amarelo;
  int led_verde;
  const int porta_vermelho;
  const int porta_amarelo;
  const int porta_verde;

  };

struct sem_peoes {
  int led_vermelho;
  int led_verde;
  const int porta_vermelho;
  const int porte_verde;
  unsigned int tempo_vermelho;
  unsigned int tempo_verde;
  };

  struct sem_carros sc1 = {
    .tempo_vermelho = 15000,
    .tempo_amarelo = 2000,
    .tempo_verde = 15000,
    .led_vermelho = LOW,
    .led_amarelo = LOW,
    .led_verde = LOW,
    .porta_vermelho = 2,
    .porta_amarelo = 3,
    .porta_verde = 4,
  };
    struct sem_carros sc2 = {
    .tempo_vermelho = 15000,
    .tempo_amarelo = 2000,
    .tempo_verde = 15000,
    .led_vermelho = LOW,
    .led_amarelo = LOW,
    .led_verde = LOW,
    .porta_vermelho = 5,
    .porta_amarelo = 6,
    .porta_verde = 7,
  };
unsigned long tempo_anterior = 0;

void setup() {
  pinMode(sc1.porta_vermelho, OUTPUT);
  pinMode(sc1.porta_amarelo, OUTPUT);
  pinMode(sc1.porta_verde, OUTPUT);
  pinMode(sc2.porta_vermelho, OUTPUT);
  pinMode(sc2.porta_amarelo, OUTPUT);
  pinMode(sc2.porta_verde, OUTPUT);

  sc1.led_vermelho = HIGH;
  sc1.led_amarelo = LOW;
  sc1.led_verde = LOW;
  sc2.led_vermelho = LOW;
  sc2.led_amarelo = LOW;
  sc2.led_verde = HIGH;
}
int estado = 0;

void loop() {
  switch (estado) {
    case 0:
    sc1.led_vermelho = HIGH;
    sc1.led_amarelo = LOW;
    sc1.led_verde = LOW;
    sc2.led_vermelho = LOW;
    sc2.led_amarelo = LOW;
    sc2.led_verde = HIGH;

  digitalWrite(sc1.porta_amarelo,sc1.led_amarelo);
  digitalWrite(sc1.porta_verde,sc1.led_verde);
  digitalWrite(sc1.porta_vermelho,sc1.led_vermelho);

  digitalWrite(sc2.porta_amarelo,sc1.led_amarelo);
  digitalWrite(sc2.porta_verde,sc1.led_verde);
  digitalWrite(sc2.porta_vermelho,sc1.led_vermelho);

  if (millis()- tempo_anterior > sc1.tempo_vermelho) {
    estado = 1;

  tempo_anterior = millis();
  }
  break;

    case 1:
    sc1.led_vermelho = HIGH;
    sc1.led_amarelo = LOW;
    sc1.led_verde = LOW;
    sc2.led_vermelho = LOW;
    sc2.led_amarelo = HIGH;
    sc2.led_verde = LOW;

  digitalWrite(sc1.porta_amarelo,sc1.led_amarelo);
  digitalWrite(sc1.porta_verde,sc1.led_verde);
  digitalWrite(sc1.porta_vermelho,sc1.led_vermelho);

  digitalWrite(sc2.porta_amarelo,sc1.led_amarelo);
  digitalWrite(sc2.porta_verde,sc1.led_verde);
  digitalWrite(sc2.porta_vermelho,sc1.led_vermelho);

  if (millis()- tempo_anterior > sc1.tempo_amarelo) {
    estado = 2;

  tempo_anterior = millis();
  }
  break;
  case 2:
    sc1.led_vermelho = LOW;
    sc1.led_amarelo = LOW;
    sc1.led_verde = HIGH;
    sc2.led_vermelho = HIGH;
    sc2.led_amarelo = LOW;
    sc2.led_verde = LOW;

  digitalWrite(sc1.porta_amarelo,sc1.led_amarelo);
  digitalWrite(sc1.porta_verde,sc1.led_verde);
  digitalWrite(sc1.porta_vermelho,sc1.led_vermelho);

  digitalWrite(sc2.porta_amarelo,sc1.led_amarelo);
  digitalWrite(sc2.porta_verde,sc1.led_verde);
  digitalWrite(sc2.porta_vermelho,sc1.led_vermelho);

  if (millis()- tempo_anterior > sc1.tempo_verde) {
    estado = 3;

  tempo_anterior = millis();
  }
break;
case 3:
    sc1.led_vermelho = LOW;
    sc1.led_amarelo = HIGH;
    sc1.led_verde = LOW;
    sc2.led_vermelho = HIGH;
    sc2.led_amarelo = LOW;
    sc2.led_verde = LOW;

  digitalWrite(sc1.porta_amarelo,sc1.led_amarelo);
  digitalWrite(sc1.porta_verde,sc1.led_verde);
  digitalWrite(sc1.porta_vermelho,sc1.led_vermelho);

  digitalWrite(sc2.porta_amarelo,sc1.led_amarelo);
  digitalWrite(sc2.porta_verde,sc1.led_verde);
  digitalWrite(sc2.porta_vermelho,sc1.led_vermelho);

  if (millis()- tempo_anterior > sc1.tempo_amarelo) {
    estado = 0;

  tempo_anterior = millis();
  }
break;

}
}
