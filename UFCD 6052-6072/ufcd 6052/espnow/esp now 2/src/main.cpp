//remetente 

#include <esp_now.h>
#include <WiFi.h>
#include <WebServer.h> // Para criar o servidor web
#include <Preferences.h> // Para salvar o MAC Address de forma persistente

// --- Configurações da Rede Wi-Fi (AP do ESP32) ---
const char *ssid = "ESP32_Config_MAC"; // Nome da rede Wi-Fi que o ESP32 criará
const char *password = "config123"; // Senha da rede

WebServer server(80); // Objeto servidor web na porta 80

// --- Variáveis para ESP-NOW ---
uint8_t receiverMacAddress[6]; // Endereço MAC do receptor (será configurado pela web)

// Estrutura para enviar dados (DEVE ser idêntica à do receptor)
typedef struct struct_message {
  char a[32];
  int b;
  float c;
  bool d;
} struct_message;

// Criar uma variável da estrutura
struct_message myData;

// Objeto para armazenar configurações persistentes (como o MAC do receptor)
Preferences preferences;

// --- Funções de Callback ESP-NOW ---
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

// --- Funções do Servidor Web ---

// Página HTML para entrada do MAC
const char* htmlForm = R"RAW(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>Configurar MAC do Receptor</title>
<style>
body { font-family: Arial, sans-serif; text-align: center; margin-top: 50px; }
input[type="text"] { width: 300px; padding: 10px; margin: 10px 0; border: 1px solid #ccc; border-radius: 4px; }
input[type="submit"] { background-color: #4CAF50; color: white; padding: 10px 20px; border: none; border-radius: 4px; cursor: pointer; }
input[type="submit"]:hover { background-color: #45a049; }
</style>
</head>
<body>
<h1>Configurar MAC do Receptor ESP-NOW</h1>
<form action="/submit_mac" method="post">
  <label for="macAddress">Endereço MAC do Receptor (XX:XX:XX:XX:XX:XX):</label><br>
  <input type="text" id="macAddress" name="macAddress" pattern="^([0-9A-Fa-f]{2}:){5}[0-9A-Fa-f]{2}$" required><br>
  <input type="submit" value="Salvar MAC e Reiniciar">
</form>
</body>
</html>
)RAW";

// Handler para a página principal
void handleRoot() {
  server.send(200, "text/html", htmlForm);
}

// Handler para processar o MAC enviado
void handleSubmitMac() {
  if (server.hasArg("macAddress")) {
    String macStr = server.arg("macAddress");
    Serial.print("MAC recebido pela web: ");
    Serial.println(macStr);

    // Converte a string do MAC para um array de bytes
    sscanf(macStr.c_str(), "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
           &receiverMacAddress[0], &receiverMacAddress[1], &receiverMacAddress[2],
           &receiverMacAddress[3], &receiverMacAddress[4], &receiverMacAddress[5]);

    // Salva o MAC no NVS (Non-Volatile Storage)
    preferences.begin("esp-now-config", false); // 'false' para modo leitura/escrita
    preferences.putBytes("receiver_mac", receiverMacAddress, 6);
    preferences.end();
    Serial.println("MAC salvo no armazenamento persistente.");

    server.send(200, "text/plain", "MAC Address salvo com sucesso. Reiniciando o ESP32...");
    delay(1000);
    ESP.restart(); // Reinicia o ESP32 para aplicar o novo MAC
  } else {
    server.send(400, "text/plain", "Nenhum MAC Address fornecido.");
  }
}

// --- Setup ---
void setup() {
  Serial.begin(115200);

  // --- Carregar MAC do armazenamento persistente ---
  preferences.begin("esp-now-config", false);
  size_t macSize = preferences.getBytesLength("receiver_mac");
  if (macSize == 6) {
    preferences.getBytes("receiver_mac", receiverMacAddress, 6);
    Serial.print("MAC do receptor carregado do armazenamento: ");
    for (int i = 0; i < 6; i++) {
      Serial.printf("%02X%s", receiverMacAddress[i], (i < 5 ? ":" : ""));
    }
    Serial.println();
  } else {
    Serial.println("Nenhum MAC do receptor salvo. Iniciando o modo de configuração...");
    // Se não há MAC salvo, defina um MAC de broadcast temporário para o primeiro envio
    // Assim, podemos entrar no modo de configuração web.
    memset(receiverMacAddress, 0xFF, 6); // MAC de broadcast inicial
  }
  preferences.end();

  // --- Configurar Wi-Fi como Access Point ---
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  Serial.print("AP SSID: ");
  Serial.println(ssid);
  Serial.print("AP IP Address: ");
  Serial.println(WiFi.softAPIP());

  // --- Configurar rotas do Servidor Web ---
  server.on("/", HTTP_GET, handleRoot);
  server.on("/submit_mac", HTTP_POST, handleSubmitMac);
  server.begin();
  Serial.println("Servidor HTTP iniciado.");

  // --- Inicializar ESP-NOW ---
  // Apenas inicializa ESP-NOW se um MAC válido (não de broadcast) foi carregado OU se vamos configurar
  // Se o MAC ainda for broadcast, o ESP-NOW só começará a enviar após a configuração.
  if (esp_now_init() != ESP_OK) {
    Serial.println("Erro ao inicializar ESP-NOW");
    return;
  }
  esp_now_register_send_cb(OnDataSent);

  // Adicionar par (o receptor)
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, receiverMacAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Falha ao adicionar par (pode ser porque o MAC ainda é broadcast)");
    // Se falhar porque é broadcast, o envio não acontecerá até que o MAC seja configurado
    // Isso é esperado antes da primeira configuração.
  } else {
    Serial.println("Par ESP-NOW adicionado com sucesso.");
  }
}

// --- Loop Principal ---
void loop() {
  server.handleClient(); // Lida com requisições do cliente web

  // Apenas envia dados se um MAC Address válido foi configurado
  // Verifica se o MAC não é o de broadcast (0xFF:FF:FF:FF:FF:FF)
  bool isMacBroadcast = true;
  for (int i = 0; i < 6; i++) {
    if (receiverMacAddress[i] != 0xFF) {
      isMacBroadcast = false;
      break;
    }
  }

  if (!isMacBroadcast) {
    // Set values to send
    strcpy(myData.a, "Ola do ESP32 Remetente");
    myData.b = random(1, 100);
    myData.c = 1.23;
    myData.d = false;

    // Send message via ESP-NOW
    esp_err_t result = esp_now_send(receiverMacAddress, (uint8_t *) &myData, sizeof(myData));

    if (result == ESP_OK) {
      Serial.println("Dados enviados com sucesso");
    } else {
      Serial.println("Erro ao enviar dados");
    }
  } else {
    Serial.println("Aguardando configuração do MAC do receptor via interface web...");
  }
  delay(2000); // Envia a cada 2 segundos, ou espera a cada 2 segundos
}


///receptor 

#include <esp_now.h>
#include <WiFi.h>

// Estrutura para receber dados (DEVE ser idêntica à do remetente)
// É crucial que esta estrutura seja exatamente igual à estrutura no código do remetente.
typedef struct struct_message {
  char a[32];
  int b;
  float c;
  bool d;
} struct_message;

// Criar uma variável da estrutura para armazenar os dados recebidos
struct_message receivedData;

// --- Funções de Callback ESP-NOW ---

// Callback chamada quando um pacote de dados é recebido
void OnDataRecv(const uint8_t * mac_addr, const uint8_t *incomingData, int len) {
  // Copia os dados recebidos para a nossa estrutura
  // O 'len' (tamanho do pacote) deve ser igual ao 'sizeof(struct_message)'
  memcpy(&receivedData, incomingData, sizeof(receivedData));

  Serial.print("--------------------------------------------------");
  Serial.print("\r\nPacote recebido do MAC: ");
  // Imprime o endereço MAC do remetente
  for (int i = 0; i < 6; i++) {
    Serial.printf("%02X%s", mac_addr[i], (i < 5 ? ":" : ""));
  }
  Serial.println();

  Serial.print("Tamanho dos Bytes Recebidos: ");
  Serial.println(len); // Deverá ser o mesmo que sizeof(struct_message)

  // Imprime os dados contidos na estrutura
  Serial.print("String (a): ");
  Serial.println(receivedData.a);
  Serial.print("Inteiro (b): ");
  Serial.println(receivedData.b);
  Serial.print("Float (c): ");
  Serial.println(receivedData.c);
  Serial.print("Booleano (d): ");
  Serial.println(receivedData.d ? "True" : "False"); // Imprime "True" ou "False"
  Serial.println("--------------------------------------------------\r\n");
}

// --- Setup ---
void setup() {
  Serial.begin(115200); // Inicia a comunicação serial para debug

  // Configurar o Wi-Fi do ESP32 no modo Station (Estação)
  // O ESP-NOW pode funcionar em modo Station ou AP. Station é o mais comum.
  WiFi.mode(WIFI_STA);

  // Imprime o MAC Address deste ESP32. Você precisará deste MAC para o ESP32 Remetente!
  Serial.print("MAC Address deste ESP32 Receptor: ");
  Serial.println(WiFi.macAddress());

  // Inicializa o ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Erro ao inicializar ESP-NOW");
    return; // Para a execução se houver erro
  }

  // Registra a função de callback que será chamada quando dados ESP-NOW forem recebidos
  esp_now_register_recv_cb(OnDataRecv);
  Serial.println("ESP-NOW inicializado e esperando por pacotes...");
}

// --- Loop Principal ---
void loop() {
  // No loop do receptor, geralmente não há muito a fazer,
  // pois o recebimento de dados é tratado pela função de callback (OnDataRecv)
  delay(100); // Pequeno atraso para evitar um loop muito intenso, embora não estritamente necessário aqui
}