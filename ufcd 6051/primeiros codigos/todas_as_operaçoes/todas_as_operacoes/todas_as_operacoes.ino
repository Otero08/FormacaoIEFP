int numero1 = 10;
int numero2 = 3;
double soma = 0;
 double sub = 0;
 double multi =0;
 double divi = 0;
 int resto = 0;

void setup() {
   Serial.begin(9600);
   soma = numero1 + numero2;
   sub = numero1 - numero2 ;
   multi = numero1* numero2;
  divi = numero1 / numero2;
  resto = numero1 % numero2;

Serial.println (soma);
Serial.println (sub);
Serial.println (multi);
Serial.println (divi);
Serial.println (resto);

}

void loop() {
  // put your main code here, to run repeatedly:

}
