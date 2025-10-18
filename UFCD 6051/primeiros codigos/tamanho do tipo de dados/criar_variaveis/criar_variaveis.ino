bool led_maquina = LOW;
float sensor_temperatura_maquina = 20.25;
int numero_maquina = 3;
char primeiro_caracter_maquina = "A";


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
    Serial.println("Maquina Numero");
  Serial.println(numero_maquina);
  Serial.println("Nome da maquina:");
  Serial.println(primeiro_caracter_maquina);
  Serial.println("Temperatura da maquina");
  Serial.println(sensor_temperatura_maquina);
  Serial.println("Temperatura normal");




}

void loop() {
  // put your main code here, to run repeatedly:

}
