#include <Arduino.h>
#include <Wifi.h>
#include <webServer.h>

//Definir variaveis SSID e PASSWORD
const char* ssid = "Vodafone-ACD044";
const char* password = "nopasswd";

//Criar o servidor com o ESP32
WebServer server(80); 

void setup() {
  Serial.begin(115200);
  Serial.println("\nIniciando ESP32...");

  // ... (inicialização de pinos e sensores, como DHT.begin(), etc.) ...

  Serial.print("Conectando ao WiFi ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  //Defenir numero de tentativas de conexão
  // e o tempo de espera entre elas
  int tentativas = 0;
  const int maxTentativas = 5; // Define o número máximo de tentativas

  // Loop para tentar a conexão com limite de tentativas
  while (WiFi.status() != WL_CONNECTED && tentativas < maxTentativas) {
    delay(1000); // Espera 1 segundo entre as tentativas
    Serial.print("."); // Mostra um ponto a cada tentativa
    tentativas++;
  }

  // --- Condição IF para verificar o resultado da conexão ---
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi Conectado!");
    Serial.print("Endereço IP: ");
    Serial.println(WiFi.localIP());

    // AQUI VOCÊ COLOCA O CÓDIGO QUE SÓ DEVE EXECUTAR SE O WI-FI ESTIVER CONECTADO
    // Por exemplo, iniciar o servidor web:
    // server.on("/", handleRoot);
    // server.begin();
    // Serial.println("Servidor Web HTTP iniciado.");

    // E a primeira leitura dos sensores, etc.
    // distanceCm = readUltrasonicSensorCm();
    // readDHT11Sensor();
    // Serial.print("Valores iniciais: Distância = "); Serial.print(distanceCm);
    // Serial.print("cm, Temp = "); Serial.print(temperatureC);
    // Serial.print("°C, Hum = "); Serial.print(humidity); Serial.println("%");

  } else {
    // AQUI VOCÊ COLOCA O CÓDIGO QUE DEVE EXECUTAR SE A CONEXÃO FALHAR
    Serial.println("\nNão foi possível estabelecer conexão Wi-Fi após 5 tentativas.");
    Serial.println("Verifique as credenciais da rede ou o alcance.");
    // Opcional: Você pode adicionar um loop infinito aqui para parar o programa
    // e indicar uma falha crítica, ou reiniciar o ESP32.
    // while(true) { delay(100); } // Exemplo de loop infinito
    // ESP.restart(); // Exemplo de reinício do ESP32 (requer #include <ESP.h>)
  }
}

void loop() {
  // O código aqui só fará sentido se o Wi-Fi estiver conectado.
  // Você pode adicionar uma verificação aqui também, se necessário.
  // if (WiFi.status() == WL_CONNECTED) {
  //   server.handleClient();
  //   // ... (restante da lógica do loop) ...
  // }
}