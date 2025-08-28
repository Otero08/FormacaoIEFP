int x = 30;
int y =30;

void setup() 
{
  Serial.begin(9600);

  if(x>y)
  {
    Serial.println("X e maior que  Y!");
  }
  else if  (x<y)
  {
    Serial.println("Y e maior que X!");
  }
  else if (x == y) //ou apenas else 
  {
  Serial.println("X e Y sao iguais");
  }
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
