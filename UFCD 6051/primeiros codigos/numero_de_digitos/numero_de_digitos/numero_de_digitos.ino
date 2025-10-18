int input = 2534;
int contador = 0;


void setup() 
{
  Serial.begin(9600);

}

void loop() 
{
   if((input%10>)0)||((input/10)>0)
  {
    contador++; // = contador = contador +1
    input/=10;
  }

Serial.println(contador);


}

