const int LuzSensor1 = A0;
const int LuzSensor2 = A1;

struct SensorLuz {
  int valorLuz;
  int soma;
  int media;
  int contagem;
  int valores[5];
};

SensorLuz sensor1;
SensorLuz sensor2;

unsigned long tempoanterior = 0;


void setup() {
  Serial.begin(9600);
  pinMode(LuzSensor1, INPUT);
  pinMode(LuzSensor2, INPUT);


  sensor1.soma = 0;
  sensor1.media = 0;
  sensor1.contagem = 0;

  sensor2.soma = 0;
  sensor2.media = 0;
  sensor2.contagem = 0;


  
}

void loop() {
  if (millis() - tempoanterior >= 1000) {
    tempoanterior = millis();
    sensor1.valorLuz = analogRead(LuzSensor1);
    sensor2.valorLuz = analogRead(LuzSensor2);
    Serial.print("Valor da Luz 1: ");
    Serial.println(sensor1.valorLuz);
    Serial.print("Valor da Luz 2: ");
    Serial.println(sensor2.valorLuz);

    sensor1.valores[sensor1.contagem] = sensor1.valorLuz;
    sensor1.contagem++;
    sensor2.valores[sensor2.contagem] = sensor2.valorLuz;
    sensor2.contagem++;
  }

  if (sensor1.contagem >= 5) {
    sensor1.contagem = 0;
    sensor1.soma = sensor1.valores[0] + sensor1.valores[1] + sensor1.valores[2] + sensor1.valores[3] + sensor1.valores[4];
    sensor1.media = sensor1.soma / 5;
    Serial.print("Media de valor de LUZ 1: ");
    Serial.println(sensor1.media);
  }
  if (sensor2.contagem >=5){
    sensor2.contagem=0;
    sensor2.soma=sensor2.valores[0] + sensor2.valores[1] + sensor2.valores[2] + sensor2.valores[3] + sensor2.valores[4];
    sensor2.media = sensor2.soma / 5;
    Serial.print("Media de valor de LUZ 2: ");
    Serial.println(sensor2.media);

  }


}