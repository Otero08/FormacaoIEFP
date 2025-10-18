// C++ code
//
void setup()
{
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
}

void loop()
{
  digitalWrite(11, HIGH);
  delay(2000); // Wait for 2000 millisecond(s)
  digitalWrite(11, LOW);
  digitalWrite(10, HIGH);
  delay(2000); // Wait for 2000 millisecond(s)
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
  digitalWrite(11, LOW);
  delay(2000); // Wait for 2000 millisecond(s)
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);
  delay(2000); // Wait for 2000 millisecond(s)
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
}