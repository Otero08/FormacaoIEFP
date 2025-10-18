// Definindo os pinos PWM para cada canal
#define RED_PIN 3
#define GREEN_PIN 5
#define BLUE_PIN 6
#define WHITE_PIN 9

void setup() {
  // Configurando os pinos como saída
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(WHITE_PIN, OUTPUT);
}

void loop() {
  // Exemplo de controle de cores
  setColor(255, 0, 0, 0);  // Vermelho
  delay(1000);
  setColor(0, 255, 0, 0);  // Verde
  delay(1000);
  setColor(0, 0, 255, 0);  // Azul
  delay(1000);
  setColor(0, 0, 0, 255);  // Branco
  delay(1000);
  setColor(255, 255, 255, 255);  // Branco total (todos os LEDs ligados)
  delay(1000);
}

void setColor(int red, int green, int blue, int white) {
  analogWrite(RED_PIN, red);
  analogWrite(GREEN_PIN, green);
  analogWrite(BLUE_PIN, blue);
  analogWrite(WHITE_PIN, white);
}