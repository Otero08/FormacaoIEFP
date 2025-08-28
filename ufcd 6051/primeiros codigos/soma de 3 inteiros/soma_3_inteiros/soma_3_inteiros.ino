int numero_1 = 2;
int numero_3 =4;
int numero_2 = 4;
int soma_total = 0;


void setup() {
   Serial.begin(9600);
   soma_total = numero_1 + numero_2 +numero_3;
   Serial.print("Soma Total é:");
   Serial.println( soma_total);
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
