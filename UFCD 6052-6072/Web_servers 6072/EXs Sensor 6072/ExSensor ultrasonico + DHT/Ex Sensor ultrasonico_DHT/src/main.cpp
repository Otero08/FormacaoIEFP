#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>       // Inclui a biblioteca do sensor DHT
#include <DHT_U.h>     // Inclui a parte unificada do DHT (para Adafruit), necessário para DHT.h

// Substitua pelas suas credenciais de rede Wi-Fi
const char* ssid = "Vodafone-ACD044"; // <<<<<<<<<<<<< Mude para o nome da sua rede WiFi
const char* password = "b9uJnxdvxJVugnCy"; // <<<<<<<<<<<<< Mude para a senha da sua rede WiFi (deixe vazio "" se não tiver senha)

// --- Pinos GPIO para o Sensor Ultrassónico HC-SR04 ---
// Conforme o seu diagrama de pinos:
// GPIO 4 é o pino "4" no lado direito.
// GPIO 12 é o pino "12" no lado direito.
const int TRIG_PIN = 4;   // Pino TRIG do sensor HC-SR04 -> GPIO 4 do ESP32
const int ECHO_PIN = 12;  // Pino ECHO do sensor HC-SR04 -> GPIO 12 do ESP32 (ATENÇÃO: COM DIVISOR DE TENSÃO!)

// --- Pinos GPIO para o Sensor de Temperatura e Humidade DHT11 ---
// GPIO 2 é um pino de uso geral comum no ESP32.
const int DHT_PIN = 2;    // Pino de Dados do DHT11 -> GPIO 2 do ESP32
#define DHTTYPE DHT11     // Define o tipo de sensor DHT (DHT11 ou DHT22). Usamos DHT11.

// Inicializa o objeto DHT com o pino e o tipo definidos
DHT dht(DHT_PIN, DHTTYPE);

// Variáveis globais para armazenar os valores dos sensores
int distanceCm = 0;      // Distância em centímetros (HC-SR04)
float temperatureC = 0.0; // Temperatura em Celsius (DHT11)
float humidity = 0.0;     // Humidade relativa (DHT11)

// Variáveis para controlar o tempo da atualização do sensor e da página
unsigned long update_sensor_timer = 0; // Usado para controlar a leitura e a atualização da página
const long updateInterval = 2000;      // Intervalo de 2 segundos (2000 milissegundos) para atualizar a página

// Cria o objeto do servidor web na porta 80
WebServer server(80);

// --- Declaração de funções (Forward declarations) ---
void handleRoot(); // Necessário porque handleRoot() é chamada em setup/loop e definida depois.

// --- Funções de Leitura dos Sensores ---

// Função para ler o sensor ultrassónico HC-SR04 e retornar a distância em cm
long readUltrasonicSensorCm() {
  // Limpa o TRIG_PIN para garantir um estado LOW
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2); // Pequeno atraso

  // Envia um pulso de 10us no TRIG_PIN para iniciar a medição
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Lê a duração do pulso no ECHO_PIN (tempo que o som levou para ir e voltar)
  // pulseIn() retorna 0 se não houver pulso dentro do timeout (20000 microsegundos = 20ms)
  long duration = pulseIn(ECHO_PIN, HIGH, 20000); // Variável local para duration

  // Se o pulso não for recebido (duração 0) ou for muito alto (fora do alcance),
  // retorna um valor máximo ou um valor de erro (e.g., 400cm, limite do HC-SR04).
  if (duration == 0 || duration > 23529) { // 23529us corresponde a ~400cm (limite teórico do HC-SR04)
      return 400; // Retorna 400cm como "fora de alcance" ou erro
  }

  // Calcula a distância: (duração do pulso em microssegundos * velocidade do som em cm/us) / 2 (ida e volta)
  // Velocidade do som no ar é aproximadamente 0.034 cm/us (ou 340 m/s)
  int calculatedDistance = duration * 0.034 / 2; // Variável local para a distância

  // Garante que a distância não seja menor que 2cm (limite mínimo do HC-SR04)
  if (calculatedDistance < 2) {
      return 2;
  }
  return calculatedDistance;
}

// Função para ler o sensor DHT11
void readDHT11Sensor() {
  // Lê a humidade e a temperatura do sensor DHT11
  humidity = dht.readHumidity();
  temperatureC = dht.readTemperature();

  // Verifica se a leitura foi bem-sucedida (o DHT pode falhar às vezes)
  if (isnan(humidity) || isnan(temperatureC)) {
    Serial.println("Erro ao ler do sensor DHT!");
    // Atribui um valor padrão em caso de erro para evitar NaN na página web
    humidity = 0.0;
    temperatureC = 0.0;
  }
}

// --- Handler para a URL raiz ("/") ---
// Esta função irá gerar e enviar a página web com os valores atuais dos sensores.
void handleRoot() {
  // --- HTML dentro de um Raw String Literal ---
  // A tag <meta charset="UTF-8"> é crucial para exibir caracteres especiais corretamente.
  const char* htmlTemplate = R"raw_html(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<meta charset="UTF-8">  <title>ESP32 Multi-Sensor Dashboard</title>
<style>
  html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}
  h1 { color: #007bff; padding: 2vh;}
  /* Estilo para os parágrafos de valor, ajustado para caber mais informação sem quebrar muito o layout */
  p { font-size: 24px; margin-top: 10px; margin-bottom: 5px; } 
  strong { color: #e74c3c; font-size: 36px; display: block; margin-top: 5px;}
</style>
</head>
<body>
<h1>Diogo Otero ------- ESP32 Multi-Sensor Dashboard</h1>

<p>Distância: <strong>%DISTANCE_VALUE% cm</strong></p>
<p>Temperatura: <strong>%TEMP_VALUE% &deg;C</strong></p>
<p>Humidade: <strong>%HUM_VALUE% %</strong></p>

</body>
</html>
)raw_html"; // Fim do raw string literal, com o mesmo delimitador

  // Copia o template para um objeto String para poder fazer as substituições
  String finalHtml = String(htmlTemplate);

  // Substitui os placeholders pelos valores reais dos sensores
  finalHtml.replace("%DISTANCE_VALUE%", String(distanceCm));
  finalHtml.replace("%TEMP_VALUE%", String(temperatureC, 1)); // 1 casa decimal para temperatura
  finalHtml.replace("%HUM_VALUE%", String(humidity, 1));    // 1 casa decimal para humidade

  // Envia a página HTML para o navegador
  server.send(200, "text/html", finalHtml);
}

void setup() {
  Serial.begin(115200);
  Serial.println("\nIniciando ESP32 Web Server com Multi-Sensores...");

  // Inicializa os pinos do sensor ultrassónico
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Inicializa o sensor DHT11
  dht.begin();
  Serial.println("Sensor DHT11 inicializado.");

  // Conecta ao Wi-Fi
  Serial.print("Conectando ao WiFi ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Conectado!");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());

  // Configura o servidor web para lidar com a rota raiz
  server.on("/", handleRoot);

  // Inicia o servidor web
  server.begin();
  Serial.println("Servidor Web HTTP iniciado.");

  // Força uma primeira leitura de todos os sensores no início
  distanceCm = readUltrasonicSensorCm();
  readDHT11Sensor(); // Atualiza temperatureC e humidity
  Serial.print("Valores iniciais: Distância = "); Serial.print(distanceCm);
  Serial.print("cm, Temp = "); Serial.print(temperatureC);
  Serial.print("°C, Hum = "); Serial.print(humidity); Serial.println("%");
}

void loop() {
  // Lida com as requisições HTTP recebidas do cliente (navegador)
  server.handleClient();

  // Controla o tempo para ler os sensores e ATUALIZAR A PÁGINA no navegador
  unsigned long currentMillis = millis();
  if (currentMillis - update_sensor_timer >= updateInterval) {
    update_sensor_timer = currentMillis; // Reseta o timer

    // Lê os novos valores de ambos os sensores
    distanceCm = readUltrasonicSensorCm();
    readDHT11Sensor(); // Atualiza temperatureC e humidity

    // Imprime no Serial Monitor para depuração
    Serial.print("Nova leitura: Distância = "); Serial.print(distanceCm);
    Serial.print("cm, Temp = "); Serial.print(temperatureC);
    Serial.print("°C, Hum = "); Serial.print(humidity); Serial.println("%");

    // CHAMA handleRoot() para RE-ENVIAR a página HTML com os novos valores.
    // Lembre-se: isso fará a página no navegador recarregar completamente ("piscar").
    handleRoot();
  }
}
