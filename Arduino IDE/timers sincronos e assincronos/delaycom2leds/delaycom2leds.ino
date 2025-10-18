void setup() {
  // put your setup code here, to run once:
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(8,HIGH);
  delay(1000); //timer sincrono
  digitalWrite(8,LOW);
  delay(100); //timer sincrono
  digitalWrite(9,HIGH);
  delay(1000); //timer sincrono
  digitalWrite(9,LOW);
  delay(100); //timer sincrono
}
