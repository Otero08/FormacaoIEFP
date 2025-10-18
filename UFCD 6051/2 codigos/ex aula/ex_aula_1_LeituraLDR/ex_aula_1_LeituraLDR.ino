const int sensorluz = A0;
int valorluz = 0;
unsigned long tempoanterior = 0;
int valores[5];
int soma = 0; 
int media = 0;
int contagem = 0;


void setup() {
  Serial.begin(9600);
  pinMode(sensorluz,INPUT);

}

void loop() {
  if (millis()-tempoanterior>=1000)
  {
    tempoanterior = millis();
    valorluz = analogRead(sensorluz);
    Serial.print("Valor da Luz: ");
    Serial.println(valorluz);

    valores[contagem] = valorluz;
    contagem++;
  
  }
  if (contagem >= 5)
  {
       contagem = 0;
    soma=valores[0]+valores[1]+valores[2]+valores[3]+valores[4];
    media=soma/5;
    Serial.print("Media de valor de LUZ: ");
    Serial.println(media);
 
  }


}
