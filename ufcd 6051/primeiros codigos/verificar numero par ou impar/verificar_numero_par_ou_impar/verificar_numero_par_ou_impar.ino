int x = 9;
int y = 2; // dividir por 2 para verificar o resto se e 0 ou nao, numero par ou impar


void setup() 
{
  Serial.begin(9600);

  if (x % y==0) 
  {
    Serial.println("Numero Par");

  }
  else 
  {
    Serial.println("Numero Impar");
  }

}

void loop() {
  // put your main code here, to run repeatedly:

}
