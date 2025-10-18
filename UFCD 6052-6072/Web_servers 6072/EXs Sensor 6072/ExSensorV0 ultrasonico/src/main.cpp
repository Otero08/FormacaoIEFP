#include <WiFi.h>
#include <WebServer.h>

// Substitua pelas suas credenciais de rede Wi-Fi
const char* ssid = "Vodafone-ACD044"; // <<<<<<<<<<<<< Mude para o nome da sua rede WiFi
const char* password = "nopass"; // <<<<<<<<<<<<< Mude para a senha da sua rede WiFi (deixe vazio "" se não tiver senha)

// --- Pinos GPIO para o Sensor Ultrassónico HC-SR04 ---
// Com base no seu diagrama de pinos que você enviou anteriormente:
// GPIO 4 é o pino "4" no lado direito.
// GPIO 12 é o pino "12" no lado direito.
const int TRIG_PIN = 4;   // Pino TRIG do sensor HC-SR04 -> GPIO 4 do ESP32
const int ECHO_PIN = 12;  // Pino ECHO do sensor HC-SR04 -> GPIO 12 do ESP32 (ATENÇÃO: COM DIVISOR DE TENSÃO!)

// Variável para armazenar o valor atual do sensor (distância)
int valordosensor = 0; // Usaremos esta variável para a distância em cm

// Variáveis para controlar o tempo da atualização do sensor e da página
unsigned long update_sensor_timer = 0; // Usado para controlar a leitura e a atualização da página
const long updateInterval = 2000;      // Intervalo de 2 segundos (2000 milissegundos) para atualizar a página

// Cria o objeto do servidor web na porta 80
WebServer server(80);

// --- Declaração de funções (Forward declarations) ---
void handleRoot();

// --- Funções de Leitura do Sensor HC-SR04 ---

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

// --- Handler para a URL raiz ("/") ---
// Esta função irá gerar e enviar a página web com o valor atual do sensor.
void handleRoot() {
  // --- HTML dentro de um Raw String Literal ---
  // A tag <meta charset="UTF-8"> é crucial para exibir caracteres especiais corretamente.
  const char* htmlTemplate = R"raw_html(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<meta charset="UTF-8">  <title>ESP32 Sensor de Distância</title>
<style>
  html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}
  h1 { color: #007bff; padding: 2vh;}
  p { font-size: 24px; margin-top: 20px; }
  strong { color: #e74c3c; font-size: 48px; display: block; margin-top: 10px;}
</style>
<script>
  // JavaScript para forçar a recarga da página a cada 2 segundos
  // ISSO É ESSENCIAL PARA O NAVEGADOR PEDIR A PÁGINA NOVAMENTE E VER A ATUALIZAÇÃO
  setTimeout(function(){ location.reload(); }, 2000); 
</script>
</head>
<body>
<h1>Diogo Otero ------- ESP32 Sensor de Distância</h1>
<p>Distância: <strong>%SENSOR_VALUE% cm</strong></p>
</body>
</html>
)raw_html"; // Fim do raw string literal, com o mesmo delimitador

  // Copia o template para um objeto String para poder fazer a substituição
  String finalHtml = String(htmlTemplate);

  // Substitui o placeholder pelo valor atual do sensor (distância)
  finalHtml.replace("%SENSOR_VALUE%", String(valordosensor));

  // Envia a página HTML para o navegador
  server.send(200, "text/html", finalHtml);
}

void setup() {
  Serial.begin(115200);
  Serial.println("\nIniciando ESP32 Web Server com Sensor de Distância HC-SR04...");

  // Inicializa os pinos do sensor ultrassónico
  // TRIG_PIN como SAÍDA (para enviar o pulso)
  // ECHO_PIN como ENTRADA (para receber o pulso de retorno)
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

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
  Serial.println("Servidor Web HTTP iniciado");

  // Força uma primeira leitura do sensor no início
  valordosensor = readUltrasonicSensorCm();
  Serial.print("Distância inicial: ");
  Serial.print(valordosensor);
  Serial.println(" cm");
}

void loop() {
  // Lida com as requisições HTTP recebidas do cliente (navegador)
  server.handleClient();

  // Controla o tempo para ler o sensor e ATUALIZAR A PÁGINA no navegador
  unsigned long currentMillis = millis();
  if (currentMillis - update_sensor_timer >= updateInterval) {
    update_sensor_timer = currentMillis; // Reseta o timer

    // Lê o novo valor do sensor HC-SR04
    valordosensor = readUltrasonicSensorCm();

    // Imprime no Serial Monitor para depuração
    Serial.print("Nova Distância (ESP32): ");
    Serial.print(valordosensor);
    Serial.println(" cm");

    // handleRoot(); // Esta linha pode ser mantida, mas a recarga VISUAL
                    // da página é impulsionada pelo JavaScript no cliente.
                    // Ela fará o ESP32 gerar a página com o novo valor,
                    // mas o navegador só a exibirá se o JS pedir.
  }
}