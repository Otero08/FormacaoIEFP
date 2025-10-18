
#include <WiFi.h>
#include <WebServer.h>

// Replace with your network credentials
const char* ssid = "Vodafone-ACD044";
const char* password = "b9uJnxdvxJVugnCy";

// Assign output variables to GPIO pins
const int output26 = 4; // LED 1
const int output27 = 12; // LED 2

// --- Configuração do LDR ---
const int LDR_PIN = 34; // Pino GPIO para o LDR (entrada analógica)
const int LDR_LIMIT = 2000; // Limite para a leitura do LDR (ajuste este valor!)
                            // A leitura analógica do ESP32 vai de 0 a 4095.
                            // Um valor de 2000 é aproximadamente a metade do alcance.
                            // Você precisará ajustar LDR_LIMIT com base na sua luz ambiente e resistor.

// Variável para armazenar a leitura do LDR
int ldrValue = 0;

// Variáveis para controlar o tempo da atualização do sensor
unsigned long lastLDRReadMillis = 0;
const long ldrReadInterval = 500; // Ler o LDR a cada 500ms

// Create a web server object
WebServer server(80);

// --- Funções de leitura do LDR ---
int readLDR() {
  return analogRead(LDR_PIN);
}

// Function to handle the root URL and show the current states
void handleRoot() {
  // HTML como um Raw String Literal para melhor legibilidade
  // Usamos um placeholder para os valores dinâmicos (LDR, estados dos LEDs)
  const char* htmlTemplate = R"raw_html(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<meta charset="UTF-8">
<link rel="icon" href="data:,">
<title>ESP32 Web Server - Controlo por LDR</title>
<style>
  html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}
  .button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px; text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}
  .button2 { background-color: #555555; }
</style>
<meta http-equiv="refresh" content="1"> 
</head>
<body>
<h1>ESP32 Web Server - Controlo por LDR</h1>

<p>Leitura LDR: <strong>%LDR_VALUE%</strong></p>

<p>GPIO 26 (LED 1 - Escuro) - State: <strong>%GPIO26_STATE%</strong></p>

<p>GPIO 27 (LED 2 - Claro) - State: <strong>%GPIO27_STATE%</strong></p>

</body>
</html>
)raw_html"; // Fim do raw string literal

  // Cria um objeto String para poder fazer as substituições
  String finalHtml = String(htmlTemplate);

  // Substitui os placeholders pelos valores reais
  finalHtml.replace("%LDR_VALUE%", String(ldrValue));

  if (digitalRead(output26) == HIGH) {
    finalHtml.replace("%GPIO26_STATE%", "on");
  } else {
    finalHtml.replace("%GPIO26_STATE%", "off");
  }

  if (digitalRead(output27) == HIGH) {
    finalHtml.replace("%GPIO27_STATE%", "on");
  } else {
    finalHtml.replace("%GPIO27_STATE%", "off");
  }

  server.send(200, "text/html", finalHtml);
}

void setup() {
  Serial.begin(115200);

  // Initialize the output variables as outputs
  pinMode(output26, OUTPUT);
  pinMode(output27, OUTPUT);
  // Set outputs to LOW initially
  digitalWrite(output26, LOW);
  digitalWrite(output27, LOW);

  // Connect to Wi-Fi network
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  // Modificação: Loop de tentativas de conexão Wi-Fi com limite de 5
  int attempts = 0;
  const int maxAttempts = 15;

  while (WiFi.status() != WL_CONNECTED && attempts < maxAttempts) {
    delay(1000); // Aumentei o delay para 1 segundo
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    // Set up the web server to handle different routes
    server.on("/", handleRoot);

    // Start the web server
    server.begin();
    Serial.println("HTTP server started");
  } else {
    Serial.println("\nNão foi possível estabelecer conexão Wi-Fi após 5 tentativas.");
    Serial.println("Verifique as credenciais ou o alcance da rede.");
    // Opcional: Adicionar um loop infinito ou reinício aqui se a conexão for crucial
  }
}

void loop() {
  // Handle incoming client requests ONLY if WiFi is connected
  if (WiFi.status() == WL_CONNECTED) {
    server.handleClient();

    // Lógica para ler o LDR e controlar os LEDs
    unsigned long currentMillis = millis();
    if (currentMillis - lastLDRReadMillis >= ldrReadInterval) {
      lastLDRReadMillis = currentMillis; // Reinicia o timer

      ldrValue = readLDR(); // Lê o valor do LDR
      Serial.print("LDR Value: ");
      Serial.println(ldrValue);

      // Condição IF para controlar os LEDs com base na leitura do LDR
      if (ldrValue < LDR_LIMIT) { // Se estiver mais escuro que o limite
        digitalWrite(output26, HIGH); // Liga o LED 1 (GPIO 26)
        digitalWrite(output27, LOW);  // Desliga o LED 2 (GPIO 27)
        Serial.println("Ambiente escuro: LED 26 LIGADO.");
      } else { // Se estiver mais claro que o limite
        digitalWrite(output26, LOW);  // Desliga o LED 1 (GPIO 26)
        digitalWrite(output27, HIGH); // Liga o LED 2 (GPIO 27)
        Serial.println("Ambiente claro: LED 27 LIGADO.");
      }
    }
  }
}