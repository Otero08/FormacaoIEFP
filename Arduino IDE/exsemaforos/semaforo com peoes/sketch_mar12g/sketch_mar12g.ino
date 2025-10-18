//semaforo carro 1
const int vermelhocarro1 = 2;
const int amarelocarro1 = 3;
const int verdecarro1 = 4;
//semaforo peao 1
const int vermelhopeao1 = 8;
const int verdepeao1 = 9;
//semaforo carro 2
const int vermelhocarro2 = 5;
const int amarelocarro2 = 6;
const int verdecarro2 = 7;
//semaforo peao 2
const int vermelhopeao2 = 11;
const int verdepeao2 = 13;
//botao
const int botao = 12;

void semaforocarro1verde (){
  //semaforocarro1
  digitalWrite(verdecarro1, HIGH);
  digitalWrite(amarelocarro1, LOW);
  digitalWrite(vermelhocarro1, LOW);
  //semaforopeao1
  digitalWrite(vermelhopeao1, HIGH);
  digitalWrite(verdepeao1, LOW);
  digitalWrite(vermelhopeao2, LOW);
  digitalWrite(verdepeao2, HIGH);

}



void semaforocarro1amarelo(){
  // Semáforo carro 1
  digitalWrite(verdecarro1, LOW);
  digitalWrite(amarelocarro1, HIGH);
  digitalWrite(vermelhocarro1, LOW);
    
  // Ambos os semáforos dos peões devem estar vermelhos
  digitalWrite(vermelhopeao1, HIGH);
  digitalWrite(verdepeao1, LOW);
  digitalWrite(vermelhopeao2, LOW); 
  digitalWrite(verdepeao2, HIGH);
}

  

void semaforocarro1vermelho(){
    //semaforocarro1
  digitalWrite(verdecarro1, LOW);
  digitalWrite(amarelocarro1, LOW);
  digitalWrite(vermelhocarro1, HIGH);
  //semaforopeao1
  digitalWrite(vermelhopeao1, LOW);
  digitalWrite(verdepeao1, HIGH); 
  digitalWrite(vermelhopeao2, HIGH);
  digitalWrite(verdepeao2, LOW);
}
//////////////////////////
void semaforocarro2verde (){
  //semaforocarro2
  digitalWrite(verdecarro2, HIGH);
  digitalWrite(amarelocarro2, LOW);
  digitalWrite(vermelhocarro2, LOW);
  //semaforopeao2
  digitalWrite(vermelhopeao2, HIGH);
  digitalWrite(verdepeao2, LOW);
  digitalWrite(vermelhopeao1, LOW);
  digitalWrite(verdepeao1, HIGH);

}
void semaforocarro2amarelo(){
  // Semáforo carro 2
  digitalWrite(verdecarro2, LOW);
  digitalWrite(amarelocarro2, HIGH);
  digitalWrite(vermelhocarro2, LOW);
    
  // Ambos os semáforos dos peões devem estar vermelhos
  digitalWrite(vermelhopeao2, HIGH); 
  digitalWrite(verdepeao2, LOW);
  digitalWrite(vermelhopeao1, LOW);
  digitalWrite(verdepeao1, HIGH);
}


void semaforocarro2vermelho(){
    //semaforocarro2
  digitalWrite(verdecarro2, LOW);
  digitalWrite(amarelocarro2, LOW);
  digitalWrite(vermelhocarro2, HIGH);
  //semaforopeao2
  digitalWrite(vermelhopeao1, HIGH);
  digitalWrite(verdepeao1, LOW);
  digitalWrite(vermelhopeao2, LOW);
  digitalWrite(verdepeao2, HIGH);
}



void setup(){
  pinMode(vermelhocarro1, OUTPUT);
  pinMode(amarelocarro1, OUTPUT);
  pinMode(verdecarro1, OUTPUT);

  pinMode(vermelhopeao1, OUTPUT);
  pinMode(verdepeao1, OUTPUT);

  pinMode(vermelhocarro2, OUTPUT);
  pinMode(amarelocarro2, OUTPUT);
  pinMode(verdecarro2, OUTPUT);

  pinMode(vermelhopeao2, OUTPUT);
  pinMode(verdepeao2, OUTPUT);

  pinMode(botao, INPUT_PULLUP);
}

void loop(){
 semaforocarro1verde();
  semaforocarro2vermelho();
  delay(10000);
  semaforocarro1amarelo();
  semaforocarro2vermelho();
  delay(10000);
  semaforocarro1vermelho();
  semaforocarro2verde();
  delay(10000);
  semaforocarro1vermelho();
  semaforocarro2amarelo();
  delay(10000);


}