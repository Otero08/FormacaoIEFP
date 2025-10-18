const unsigned long pisca = 5000;
const unsigned long pisca_botao=3000;

const int ledvermelho = 9;
const int ledamarelo = 5;
const int ledverde = 12;
const int botao = 2;

unsigned long millis_ant = 0;
unsigned long millis_botao = 0;



void setup()
{
  //def pin mode
  pinMode(ledvermelho, OUTPUT);
  pinMode(ledamarelo,OUTPUT);
  pinMode(ledverde,OUTPUT);
  pinMode(botao,INPUT_PULLUP);
  digitalWrite(ledverde, HIGH);
}

void loop()
{

  unsigned long millis_atual= millis();
  
  if (digitalRead(botao) == HIGH) {
    digitalWrite(ledamarelo, LOW);
    millis_botao = millis_atual;
  }

  else 
  {
    if (millis_botao-millis_atual >= pisca_botao)
      digitalWrite(ledamarelo,HIGH);
       millis_botao = millis_atual;
      
  }
  
 
  
  
  
  if(millis_atual - millis_ant >= pisca) 
  {
  	if(digitalRead(ledverde))
    {
      digitalWrite(ledverde,LOW);
      digitalWrite(ledvermelho,HIGH);
    }
    else
    {
      digitalWrite(ledvermelho,LOW);
      digitalWrite(ledverde,HIGH);
    }
    millis_ant = millis_atual;
    
  } 
}