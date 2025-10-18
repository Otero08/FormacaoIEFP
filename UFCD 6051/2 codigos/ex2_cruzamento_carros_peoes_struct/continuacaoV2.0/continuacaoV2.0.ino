unsigned int sc_tempo_vermelho = 15000;
unsigned int sc_tempo_amarelo = 2000;
unsigned int sc_tempo_verde = 15000;

struct sem_carros {

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
  const int porta_verde;

  };

  struct sem_carros sc1 = {
      .led_vermelho = LOW,
      .led_amarelo = LOW,
      .led_verde = LOW,
      .porta_vermelho = 2,
      .porta_amarelo = 3,
      .porta_verde = 4,
    };
    struct sem_carros sc2 = {
      .led_vermelho = LOW,
      .led_amarelo = LOW,
      .led_verde = LOW,
      .porta_vermelho = 5,
      .porta_amarelo = 6,
      .porta_verde = 7,
    };
    struct sem_peoes sp1 = {
      .led_verde = LOW,
      .led_vermelho = LOW,
      .porta_vermelho = 8,
      .porta_verde= 9,
    };
    struct sem_peoes sp2 = {
      .led_verde = LOW,
      .led_vermelho = LOW,
      .porta_vermelho = 10,
      .porta_verde = 11,
    };

unsigned long tempo_anterior = 0;

void setup() {
  pinMode(sc1.porta_vermelho, OUTPUT);
  pinMode(sc1.porta_amarelo, OUTPUT);
  pinMode(sc1.porta_verde, OUTPUT);
  pinMode(sc2.porta_vermelho, OUTPUT);
  pinMode(sc2.porta_amarelo, OUTPUT);
  pinMode(sc2.porta_verde, OUTPUT);
  pinMode(sp1.porta_vermelho, OUTPUT);
  pinMode(sp1.porta_verde,OUTPUT);
  pinMode(sp2.porta_vermelho, OUTPUT);
  pinMode(sp2.porta_verde,OUTPUT);
  

  sc1.led_vermelho = HIGH;
  sc1.led_amarelo = LOW;
  sc1.led_verde = LOW;
  sp1.led_vermelho = LOW;
  sp1.led_verde = HIGH;
  sc2.led_vermelho = LOW;
  sc2.led_amarelo = LOW;
  sc2.led_verde = HIGH;
  sp2.led_verde = LOW;
  sp2.led_vermelho = HIGH;
}
int estado = 0;

void loop() {
  switch (estado) {
    case 0:
    sc1.led_vermelho = HIGH;
    sc1.led_amarelo = LOW;
    sc1.led_verde = LOW;
    sp1.led_vermelho = LOW;
    sp1.led_verde = HIGH;

    sc2.led_vermelho = LOW;
    sc2.led_amarelo = LOW;
    sc2.led_verde = HIGH;
    sp2.led_verde = LOW;
    sp2.led_vermelho = HIGH;

  digitalWrite(sc1.porta_amarelo,sc1.led_amarelo);
  digitalWrite(sc1.porta_verde,sc1.led_verde);
  digitalWrite(sc1.porta_vermelho,sc1.led_vermelho);
  digitalWrite(sp1.porta_vermelho,sp1.led_vermelho);
  digitalWrite(sp1.porta_verde,sp1.led_verde);

  digitalWrite(sc2.porta_amarelo,sc2.led_amarelo);
  digitalWrite(sc2.porta_verde,sc2.led_verde);
  digitalWrite(sc2.porta_vermelho,sc2.led_vermelho);
  digitalWrite(sp2.porta_vermelho,sp2.led_vermelho);
  digitalWrite(sp2.porta_verde,sp2.led_verde);

  if (millis()- tempo_anterior > sc_tempo_vermelho) {
    estado = 1;

  tempo_anterior = millis();
  }
  break;

    case 1:
    sc1.led_vermelho = HIGH;
    sc1.led_amarelo = LOW;
    sc1.led_verde = LOW;
    sp1.led_vermelho = HIGH;
    sp1.led_verde = LOW;

    sc2.led_vermelho = LOW;
    sc2.led_amarelo = HIGH;
    sc2.led_verde = LOW;
    sp2.led_verde = LOW;
    sp2.led_vermelho = HIGH;

  digitalWrite(sc1.porta_amarelo,sc1.led_amarelo);
  digitalWrite(sc1.porta_verde,sc1.led_verde);
  digitalWrite(sc1.porta_vermelho,sc1.led_vermelho);
  digitalWrite(sp1.porta_vermelho,sp1.led_vermelho);
  digitalWrite(sp1.porta_verde,sp1.led_verde);

  digitalWrite(sc2.porta_amarelo,sc2.led_amarelo);
  digitalWrite(sc2.porta_verde,sc2.led_verde);
  digitalWrite(sc2.porta_vermelho,sc2.led_vermelho);
  digitalWrite(sp2.porta_vermelho,sp2.led_vermelho);
  digitalWrite(sp2.porta_verde,sp2.led_verde);

  if (millis()- tempo_anterior > sc_tempo_amarelo) {
    estado = 2;

  tempo_anterior = millis();
  }
  break;
  case 2:
    sc1.led_vermelho = LOW;
    sc1.led_amarelo = LOW;
    sc1.led_verde = HIGH;
    sp1.led_verde = LOW;
    sp1.led_vermelho = HIGH;

    sc2.led_vermelho = HIGH;
    sc2.led_amarelo = LOW;
    sc2.led_verde = LOW;
    sp2.led_verde = HIGH;
    sp2.led_vermelho = LOW;

  digitalWrite(sc1.porta_amarelo,sc1.led_amarelo);
  digitalWrite(sc1.porta_verde,sc1.led_verde);
  digitalWrite(sc1.porta_vermelho,sc1.led_vermelho);
  digitalWrite(sp1.porta_vermelho,sp1.led_vermelho);
  digitalWrite(sp1.porta_verde,sp1.led_verde);

  digitalWrite(sc2.porta_amarelo,sc2.led_amarelo);
  digitalWrite(sc2.porta_verde,sc2.led_verde);
  digitalWrite(sc2.porta_vermelho,sc2.led_vermelho);
  digitalWrite(sp2.porta_vermelho,sp2.led_vermelho);
  digitalWrite(sp2.porta_verde,sp2.led_verde);

  if (millis()- tempo_anterior > sc_tempo_verde) {
    estado = 3;

  tempo_anterior = millis();
  }
break;
case 3:
    sc1.led_vermelho = LOW;
    sc1.led_amarelo = HIGH;
    sc1.led_verde = LOW;
    sp1.led_verde = LOW;
    sp1.led_vermelho = HIGH;

    sc2.led_vermelho = HIGH;
    sc2.led_amarelo = LOW;
    sc2.led_verde = LOW;
    sp2.led_verde = LOW;
    sp2.led_vermelho = HIGH;

  digitalWrite(sc1.porta_amarelo,sc1.led_amarelo);
  digitalWrite(sc1.porta_verde,sc1.led_verde);
  digitalWrite(sc1.porta_vermelho,sc1.led_vermelho);
  digitalWrite(sp1.porta_vermelho,sp1.led_vermelho);
  digitalWrite(sp1.porta_verde,sp1.led_verde);

  digitalWrite(sc2.porta_amarelo,sc2.led_amarelo);
  digitalWrite(sc2.porta_verde,sc2.led_verde);
  digitalWrite(sc2.porta_vermelho,sc2.led_vermelho);
  digitalWrite(sp2.porta_vermelho,sp2.led_vermelho);
  digitalWrite(sp2.porta_verde,sp2.led_verde);

  if (millis()- tempo_anterior > sc_tempo_amarelo) {
    estado = 0;

  tempo_anterior = millis();
  }
break;

}
}