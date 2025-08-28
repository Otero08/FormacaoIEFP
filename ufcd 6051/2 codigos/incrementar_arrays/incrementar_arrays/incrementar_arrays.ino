int posicao=0;
int valores[5];



void setup() {

Serial.begin(9600);

}

void loop() {

  valores[posicao]=10;
  
  Serial.println(valores[posicao]);

  posicao++;

  if (posicao>4)
  {
    posicao = 0;
  }
}



