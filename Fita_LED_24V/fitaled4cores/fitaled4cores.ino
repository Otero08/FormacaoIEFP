// Definição dos pinos do Arduino conectados aos MOSFETs
#define PIN_RED   5  // Pino PWM para cor Vermelha
#define PIN_GREEN 6  // Pino PWM para cor Verde
#define PIN_BLUE  9  // Pino PWM para cor Azul
#define PIN_WHITE 10 // Pino PWM para cor Branca

void setup() {
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);
    pinMode(PIN_WHITE, OUTPUT);
}

// Função para definir a cor do LED (valores de 0 a 255)
void setColor(int red, int green, int blue, int white) {
    analogWrite(PIN_RED, red);
    analogWrite(PIN_GREEN, green);
    analogWrite(PIN_BLUE, blue);
    analogWrite(PIN_WHITE, white);
}

void loop() {
    setColor(255, 0, 0, 0); // Vermelho
    delay(500);
    setColor(0, 255, 0, 0); // Verde
    delay(500);
    setColor(0, 0, 255, 0); // Azul
    delay(500);
    setColor(0, 0, 0, 255); // Branco
    delay(500);
    setColor(255, 255, 255, 255); // Todas as cores
    delay(500);
}

