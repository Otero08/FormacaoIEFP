const int sensorLuz = A0;  // Define o pino A0 como a entrada do LDR

void setup() {
  Serial.begin(9600);      // Inicializa a comunicação serial
  pinMode(sensorLuz, INPUT); // Configura o pino como entrada (já é o padrão, mas é bom ser explícito)
}

void loop() {
  int valorLuz = analogRead(sensorLuz); // Lê o valor analógico do LDR
  Serial.print("Valor da luz: ");
  Serial.println(valorLuz);       // Imprime o valor no Serial Monitor
  delay(100);                  // Pequeno atraso para estabilidade
}