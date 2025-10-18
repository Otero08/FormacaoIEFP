void setup() {
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}
void ligarledvermelho1(int pino1, int pino2, int pino3, bool estado) {
  digitalWrite(8, HIGH);//vermelho1
  digitalWrite(9, LOW);//amarelo1
  digitalWrite(10, LOW);//verde1
}


  
void loop() {
  // put your main code here, to run repeatedly:
  //digitalWrite(8, HIGH);//vermelho1
  //digitalWrite(9, LOW);//amarelo1
  //digitalWrite(10, LOW);//verde1
ligarledvermelho1;    
  digitalWrite(11, LOW);//vermelho2
  digitalWrite(12, LOW);//amarelo2
  digitalWrite(13, HIGH);//verde2
delay(10000);
    // put your main code here, to run repeatedly:
  digitalWrite(8, HIGH);//vermelho1
  digitalWrite(9, LOW);//amarelo1
  digitalWrite(10, LOW);//verde1
      
  digitalWrite(11, LOW);//vermelho2
  digitalWrite(12, HIGH);//amarelo2
  digitalWrite(13, LOW);//verde2
delay(3000);
  digitalWrite(12, LOW);//amarelo2
delay(500);
  digitalWrite(12, HIGH);//amarelo2
delay(500);
  digitalWrite(12, LOW);//amarelo2
delay(500);
  digitalWrite(12, HIGH);//amarelo2
delay(500);
  // put your main code here, to run repeatedly:
  digitalWrite(8, LOW);//vermelho1
  digitalWrite(9, LOW);//amarelo1
  digitalWrite(10, HIGH);//verde1
      
  digitalWrite(11, HIGH);//vermelho2
  digitalWrite(12, LOW);//amarelo2
  digitalWrite(13, LOW);//verde2
delay(10000);
  // put your main code here, to run repeatedly:
  digitalWrite(8, LOW);//vermelho1
  digitalWrite(9, HIGH);//amarelo1
  digitalWrite(10, LOW);//verde1

  digitalWrite(11, HIGH);//vermelho2
  digitalWrite(12, LOW);//amarelo2
  digitalWrite(13, LOW);//verde2

delay(3000);
  digitalWrite(9, LOW);//amarelo2
delay(500);
  digitalWrite(9, HIGH);//amarelo2
delay(500);
  digitalWrite(9, LOW);//amarelo2
delay(500);
  digitalWrite(9, HIGH);//amarelo2
delay(500);    

}
