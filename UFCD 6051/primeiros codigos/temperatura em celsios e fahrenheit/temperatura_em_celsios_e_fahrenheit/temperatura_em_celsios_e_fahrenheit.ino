double c = 0.0f;
double k =0.0f ;
double f = 0.0f;



void setup() {
  // put your setup code (here, to run once:
Serial.begin(9600);
f = (c*9/5)+32;
k = c+273.15;
Serial.print("Graus em Celsius : ");
Serial.println(c);
Serial.print("Graus em Fahrenheit : ");
Serial.println(f);
Serial.print("Gruas em  Kelvin : ");
Serial.println(k);
Serial.println(" ");


}

void loop() {
  // put your main code here, to run repeatedly:

}
