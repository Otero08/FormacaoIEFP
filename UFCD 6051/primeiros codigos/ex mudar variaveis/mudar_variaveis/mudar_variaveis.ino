int variavel_temporaria = 0;
int variavel_1 = 5;
int variavel_2 = 10;


void setup() {
  Serial.begin(9600);
  variavel_temporaria = variavel_1;
  variavel_1=variavel_2;
  variavel_2=variavel_temporaria;

  Serial.println(variavel_1);
  Serial.print(variavel_2);


}

void loop() {
  // put your main code here, to run repeatedly:

}
