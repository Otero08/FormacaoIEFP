int input = 7;
int input2= 0;


void setup() {
  Serial.begin(9600);
  if (input>0)
  {
    Serial.print("Valor Absoluto =" );
    Serial.println(input);
  }
  else if (input<0)
  {
    input2 = input*(-1);
    Serial.print("Valor Absoluto = ");
    Serial.println(input2);
  }
  else
  {
    Serial.println("Valor Absoluto = 0");
  }

  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
