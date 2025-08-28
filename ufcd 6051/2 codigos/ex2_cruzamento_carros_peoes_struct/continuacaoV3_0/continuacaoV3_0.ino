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
      .led_vermelho = 0,
      .led_amarelo = 0,
      .led_verde = 0,
      .porta_vermelho = 2,
      .porta_amarelo = 3,
      .porta_verde = 4,
    };
    struct sem_carros sc2 = {
      .led_vermelho = 0,
      .led_amarelo = 0,
      .led_verde = 0,
      .porta_vermelho = 5,
      .porta_amarelo = 6,
      .porta_verde = 7,
    };
    struct sem_peoes sp1 = {
      .led_verde = 0,
      .led_vermelho = 0,
      .porta_vermelho = 8,
      .porta_verde= 9,
    };
    struct sem_peoes sp2 = {
      .led_verde = 0,
      .led_vermelho = 0,
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
  

  sc1.led_vermelho = 1;
  sc1.led_amarelo = 0;
  sc1.led_verde = 0;
  sp1.led_vermelho = 0;
  sp1.led_verde = 1;
  sc2.led_vermelho= 0;
  sc2.led_amarelo = 0;
  sc2.led_verde = 1;
  sp2.led_verde = 0;
  sp2.led_vermelho = 1;
}
int estado = 0;

void loop() {
  switch (estado) {
    case 0:
    sc1.led_vermelho = 1;
    sc1.led_amarelo = 0;
    sc1.led_verde = 0;
    sp1.led_vermelho = 0;
    sp1.led_verde = 1;

    sc2.led_vermelho = 0;
    sc2.led_amarelo = 0;
    sc2.led_verde = 1;
    sp2.led_verde = 0;
    sp2.led_vermelho =1;

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
    sc1.led_vermelho = 1;
    sc1.led_amarelo = 0;
    sc1.led_verde = 0;
    sp1.led_vermelho = 1;
    sp1.led_verde = 0;

    sc2.led_vermelho = 0;
    sc2.led_amarelo = 1;
    sc2.led_verde = 0;
    sp2.led_verde =0;
    sp2.led_vermelho = 1;

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
    sc1.led_vermelho = 0;
    sc1.led_amarelo = 0;
    sc1.led_verde = 1;
    sp1.led_verde = 0;
    sp1.led_vermelho =1;

    sc2.led_vermelho = 1;
    sc2.led_amarelo = 0;
    sc2.led_verde = 0;
    sp2.led_verde = 1;
    sp2.led_vermelho = 0;

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
    sc1.led_vermelho = 0;
    sc1.led_amarelo = 1;
    sc1.led_verde = 0;
    sp1.led_verde = 0;
    sp1.led_vermelho = 1;

    sc2.led_vermelho =1;
    sc2.led_amarelo = 0;
    sc2.led_verde = 0;
    sp2.led_verde = 0;
    sp2.led_vermelho = 1;

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