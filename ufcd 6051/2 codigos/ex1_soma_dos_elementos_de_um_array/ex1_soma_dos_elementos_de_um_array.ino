int numero[5];
int resultado = 0 ;
int soma = 0;
double media =0.0f;

void setup() {
  Serial.begin(9600);
numero[0]=1;
numero[1]=1;
numero[2]=2;
numero[3]=2;
numero[4]=1;

resultado = numero[2]; 
Serial.println(resultado);
soma = numero[0]+numero[1]+numero[2]+numero[3]+numero[4];
Serial.println(soma);
Serial.println(numero[2]);
media= soma/5.0;// 5.0 atençao ao resto
Serial.println(media);
}

void loop() {
 

}
