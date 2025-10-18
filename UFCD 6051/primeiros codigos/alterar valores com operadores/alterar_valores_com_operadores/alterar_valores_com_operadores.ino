int x =10;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

//Serial.prinln(x+=10);
x+=10;
Serial.println(x);
x-=10;
Serial.println(x);
x/=10;
Serial.println(x);
x*=10;
Serial.println(x);
x++;
Serial.println(x);
x--;
Serial.println(x);

Serial.println();
}

void loop() {
  // put your main code here, to run repeatedly:

}
