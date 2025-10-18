/*  
  Rui Santos & Sara Santos - Random Nerd Tutorials (Base para o Web Server)
  Adaptado por Diogo Otero (Adição de sensor de distância e interface de dados)
  SEM ESPmDNS
*/

#include <WiFi.h>
#include <WebServer.h>

// Substitua pelas suas credenciais de rede Wi-Fi
const char* ssid = "IEFP-Formacao";     // <<<<<<<<<<<<< Mude para o nome da sua rede WiFi
const char* password = ""; // <<<<<<<<<<<<< Mude para a senha da sua rede WiFi (deixe vazio "" se não tiver senha)

// --- Pinos GPIO para o Sensor Ultrassónico ---
const int TRIG_PIN = 14;         // Pino TRIG do sensor HC-SR04
const int ECHO_PIN = 12;         // Pino ECHO do sensor HC-SR04 (ATENÇÃO: DIVISOR DE TENSÃO NECESSÁRIO!)

// Variáveis para a leitura do sensor
long duration;   // Duração do pulso do sensor (microsegundos)
int distanceCm;  // Distância em centímetros
volatile int currentSensorValue = 0; // Armazenará a última leitura válida do sensor (volatile para acesso em diferentes contextos)

// Variáveis de controle de tempo para leituras do sensor
unsigned long previousMillisSensor = 0;
const long sensorReadInterval = 1000; // Intervalo de 1 segundo (1000 milissegundos) para leitura do sensor

// Create a web server object
WebServer server(80);

// --- Declarações de Funções ---
void handleRoot();
long readUltrasonicSensorCm(); // Função para ler o sensor
void handleSensorData();       // Função para enviar a leitura do sensor via HTTP (para o JavaScript)

// --- Funções de Manipuladores de Requisições HTTP ---

// Função para ler o sensor ultrassónico
long readUltrasonicSensorCm() {
  // Limpa o TRIG_PIN para garantir um estado LOW
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2); // Pequeno atraso

  // Envia um pulso de 10us no TRIG_PIN para iniciar a medição
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Lê a duração do pulso no ECHO_PIN (tempo que o som levou para ir e voltar)
  // pulseIn() retorna 0 se não houver pulso dentro do timeout (10000 microsegundos = 10ms)
  duration = pulseIn(ECHO_PIN, HIGH, 20000); // Aumentei o timeout para 20ms para maior alcance

  // Se o pulso não for recebido (duração 0) ou for muito alto (fora do alcance),
  // retorna um valor máximo ou um valor de erro.
  // O HC-SR04 geralmente tem um alcance útil de 2cm a 400cm.
  // Duração máxima para 400cm é aproximadamente 400 * 2 / 0.034 = 23529 microsegundos
  if (duration == 0 || duration > 23529) { 
      return 400; // Retorna 400cm (fora de alcance)
  }

  // Calcula a distância: (duração do pulso em microssegundos * velocidade do som em cm/us) / 2 (ida e volta)
  // Velocidade do som no ar é aproximadamente 0.034 cm/us (ou 340 m/s)
  distanceCm = duration * 0.034 / 2;

  // Garante que a distância não seja menor que 2cm (limite mínimo do HC-SR04)
  if (distanceCm < 2) {
      return 2;
  }
  return distanceCm;
}

// Handler para servir a leitura ATUAL do sensor (usada pelo JavaScript)
void handleSensorData() {
  // Esta função apenas retorna o valor armazenado em 'currentSensorValue'.
  // A leitura real do sensor é feita periodicamente no loop principal para não bloquear o servidor.
  server.send(200, "text/plain", String(currentSensorValue)); // Envia a distância como texto
  Serial.print("Distância enviada para o navegador (via /sensor): ");
  Serial.println(currentSensorValue);
}

// Function to handle the root URL and show the current states
void handleRoot() {
  String html = "<!DOCTYPE html>";
  html += "<html lang=\"en\">";
  html += "<head>";
  html += "<meta charset=\"UTF-8\">";
  html += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
  html += "<title>Monitor de Distância - ESP32</title>";
  html += "<style>";
  html += "body { font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; margin: 20px; background-color: #f4f4f4; color: #333; text-align: center; }";
  html += ".container { background-color: #fff; margin: 40px auto; padding: 30px; border-radius: 10px; box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1); max-width: 600px; }";
  html += "h1 { color: #2c3e50; margin-bottom: 30px; }";
  html += ".data-section { margin-bottom: 25px; padding: 15px; border: 1px solid #eee; border-radius: 8px; background-color: #fafafa; }";
  html += ".data-section h2 { color: #3498db; margin-top: 0; margin-bottom: 15px; font-size: 1.5em; }";
  html += "#lastReading { font-size: 3.5em; font-weight: bold; color: #e74c3c; margin: 10px 0; display: block; }";
  html += ".unit { font-size: 0.6em; color: #777; vertical-align: super; }";
  html += ".readings-list { list-style-type: none; padding: 0; margin-top: 15px; max-height: 150px; overflow-y: auto; border: 1px solid #ddd; border-radius: 5px; background-color: #fff; }";
  html += ".readings-list li { padding: 8px 15px; border-bottom: 1px dashed #eee; color: #555; font-size: 0.95em; display: flex; justify-content: space-between; align-items: center; }";
  html += ".readings-list li:last-child { border-bottom: none; }";
  html += ".timestamp { font-size: 0.8em; color: #999; }";
  html += "#averageReading { font-size: 2em; font-weight: bold; color: #27ae60; margin: 15px 0; display: block; }";
  html += "footer { margin-top: 50px; font-size: 0.8em; color: #999; }";
  html += "</style>";
  html += "</head>";
  html += "<body>";
  html += "<div class=\"container\">";
  html += "<h1>Monitor de Distância</h1>";
  html += "<div class=\"data-section\">";
  html += "<h2>Última Leitura</h2>";
  html += "<span id=\"lastReading\">-- <span class=\"unit\">cm</span></span>";
  html += "</div>";
  html += "<div class=\"data-section\">";
  html += "<h2>Últimas 5 Leituras</h2>";
  html += "<ul id=\"recentReadings\" class=\"readings-list\">";
  html += "<li>Aguardando leituras...</li>";
  html += "</ul>";
  html += "</div>";
  html += "<div class=\"data-section\">";
  html += "<h2>Média das Últimas 10 Leituras</h2>";
  html += "<span id=\"averageReading\">-- <span class=\"unit\">cm</span></span>";
  html += "</div>";
  html += "</div>";
  html += "<footer>Sensor Ultrassónico - Desenvolvido por Diogo Otero</footer>";
  html += "<script>";
  html += "const lastReadingSpan = document.getElementById('lastReading');";
  html += "const recentReadingsList = document.getElementById('recentReadings');";
  html += "const averageReadingSpan = document.getElementById('averageReading');";
  html += "const allReadings = [];";
  html += "const MAX_READINGS_FOR_AVERAGE = 10;";
  html += "const MAX_READINGS_FOR_DISPLAY = 5;";
  html += "async function fetchSensorData() {";
  html += "    try {";
  html += "        const response = await fetch('/sensor');"; // Requisição ao ESP32
  html += "        const data = await response.text();";
  html += "        const distance = parseFloat(data);";
  html += "        if (!isNaN(distance)) {";
  html += "            const timestamp = new Date().toLocaleTimeString();";
  html += "            allReadings.push({ value: distance, time: timestamp });";
  html += "            if (allReadings.length > MAX_READINGS_FOR_AVERAGE) {";
  html += "                allReadings.shift();";
  html += "            }";
  html += "            lastReadingSpan.innerHTML = `${distance} <span class=\"unit\">cm</span>`;";
  html += "            updateRecentReadingsDisplay();";
  html += "            updateAverageReadingDisplay();";
  html += "        } else {";
  html += "            console.error(\"Dados inválidos do sensor recebidos:\", data);";
  html += "            lastReadingSpan.innerHTML = \"Erro! <span class=\\\"unit\\\">cm</span>\";";
  html += "        }";
  html += "    } catch (error) {";
  html += "        console.error(\"Erro ao buscar dados do sensor:\", error);";
  html += "        lastReadingSpan.innerHTML = \"N/A <span class=\\\"unit\\\">cm</span>\";";
  html += "    }";
  html += "}";
  html += "function updateRecentReadingsDisplay() {";
  html += "    recentReadingsList.innerHTML = '';";
  html += "    const readingsToDisplay = allReadings.slice(-MAX_READINGS_FOR_DISPLAY).reverse();";
  html += "    if (readingsToDisplay.length === 0) {";
  html += "        recentReadingsList.innerHTML = '<li>Aguardando leituras...</li>';";
  html += "        return;";
  html += "    }";
  html += "    readingsToDisplay.forEach(reading => {";
  html += "        const listItem = document.createElement('li');";
  html += "        listItem.innerHTML = `Distância: <strong>${reading.value} <span class=\"unit\">cm</span></strong> <span class=\"timestamp\">(${reading.time})</span>`;";
  html += "        recentReadingsList.appendChild(listItem);";
  html += "    });";
  html += "}";
  html += "function updateAverageReadingDisplay() {";
  html += "    if (allReadings.length === 0) {";
  html += "        averageReadingSpan.innerHTML = `-- <span class=\"unit\">cm</span>`;";
  html += "        return;";
  html += "    }";
  html += "    const sum = allReadings.reduce((total, reading) => total + reading.value, 0);";
  html += "    const average = (sum / allReadings.length).toFixed(1);";
  html += "    averageReadingSpan.innerHTML = `${average} <span class=\"unit\">cm</span>`;";
  html += "}";
  html += "setInterval(fetchSensorData, 1000);"; // Atualiza a cada 1 segundo
  html += "fetchSensorData();";
  html += "</script>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);
  Serial.println("\nIniciando ESP32 Web Server com Sensor de Distância...");

  // Configura os pinos do sensor ultrassónico
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Conectar ao Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Conectando ao WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Conectado!");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());

  // Set up the web server to handle different routes
  server.on("/", handleRoot);
  server.on("/sensor", HTTP_GET, handleSensorData); // Rota para o JavaScript buscar a leitura do sensor

  // Start the web server
  server.begin();
  Serial.println("Servidor Web HTTP iniciado.");
}

void loop() {
  server.handleClient(); // Essencial: processa todas as requisições HTTP pendentes

  // Lógica para ler o sensor periodicamente e armazenar o valor
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillisSensor >= sensorReadInterval) {
    previousMillisSensor = currentMillis; // Atualiza o tempo da última execução
    currentSensorValue = readUltrasonicSensorCm(); // Realiza a leitura e armazena
    Serial.print("Leitura do sensor (loop periódico): ");
    Serial.print(currentSensorValue);
    Serial.println(" cm");
  }
}