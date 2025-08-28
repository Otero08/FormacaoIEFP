float nota1 = 15.84f;
float nota2 = 13.76f;
float nota3 = 16.25f;
float media = 0.0f;
void setup() 
{
  Serial.begin(9600);
  media = (nota1 + nota2 + nota3)/3;
  Serial.print("Media de notas = ");
  Serial.println(media);

}
void loop() 
{
  // put your main code here, to run repeatedly:

}
