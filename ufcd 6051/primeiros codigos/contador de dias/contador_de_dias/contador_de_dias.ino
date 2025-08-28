int dias = 21;
int semanas =0;
int resto_dias=0;


void setup() {
 Serial.begin(9600);
 semanas = dias/7;
 resto_dias = dias % 7;

 Serial.print("Dias : ");
 Serial.println(dias);
 Serial.print("Nº de Semanas : ");
 Serial.print(semanas );
 Serial.print(" e ");
 Serial.print(resto_dias );
 Serial.println(" dias");


}

void loop() {
  // put your main code here, to run repeatedly:

}
