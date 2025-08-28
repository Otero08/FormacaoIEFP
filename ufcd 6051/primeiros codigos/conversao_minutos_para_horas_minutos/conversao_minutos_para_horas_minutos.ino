int minutos1 = 90;
int minutos2 = 0;
int horas = 0;

void setup() {
  Serial.begin(9600);
horas = minutos1 / 60;
minutos2 = (minutos1%60);



Serial.println(horas);
Serial.println(minutos2);

;




  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
