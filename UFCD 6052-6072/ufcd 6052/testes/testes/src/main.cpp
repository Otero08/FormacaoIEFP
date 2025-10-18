#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <DHT.h>

#define LDR_PIN 34
#define DHT_PIN 14
#define LED_PIN 25
#define FAN_PIN 26

#define DHTTYPE DHT22
DHT dht(DHT_PIN, DHTTYPE);

const char* ssid = "ESP32_AP";
const char* password = "12345678";

AsyncWebServer server(80);

String username = "admin";
String userpassword = "admin";

float ledIntensity = 128;
float fanSpeed = 128;

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <title>Monitorização ESP32</title>
  <style>
    body { font-family: Arial; padding: 20px; background: #f0f0f0; }
    h2 { color: #333; }
    .box { background: white; padding: 20px; border-radius: 10px; margin-bottom: 20px; }
  </style>
</head>
<body>
  <h2>Sistema de Monitorização ESP32</h2>
  <div class="box">
    <p><strong>Luz Ambiente (LDR):</strong> <span id="ldr">--</span></p>
    <p><strong>Temperatura (°C):</strong> <span id="temp">--</span></p>
    <p><strong>LED:</strong> <span id="led">--</span></p>
    <input type="range" min="0" max="255" value="128" id="ledControl">
    <p><strong>Ventoinha:</strong> <span id="fan">--</span></p>
    <input type="range" min="0" max="255" value="128" id="fanControl">
  </div>
<script>
function atualizar() {
  fetch('/dados')
    .then(res => res.json())
    .then(data => {
      document.getElementById("ldr").innerText = data.ldr;
      document.getElementById("temp").innerText = data.temp;
      document.getElementById("led").innerText = data.led;
      document.getElementById("fan").innerText = data.fan;
    });
}
setInterval(atualizar, 5000);
document.getElementById("ledControl").addEventListener("input", function() {
  fetch("/set_led", {
    method: "POST",
    headers: { "Content-Type": "application/x-www-form-urlencoded" },
    body: "value=" + this.value
  });
});
document.getElementById("fanControl").addEventListener("input", function() {
  fetch("/set_fan", {
    method: "POST",
    headers: { "Content-Type": "application/x-www-form-urlencoded" },
    body: "value=" + this.value
  });
});
atualizar();
</script>
</body>
</html>
)rawliteral";

String base64encode(const String& input) {
  const char* chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
  String encoded = "";
  int i = 0, j = 0;
  unsigned char char_array_3[3], char_array_4[4];

  int len = input.length();
  int pos = 0;
  while (len--) {
    char_array_3[i++] = input[pos++];
    if (i == 3) {
      char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
      char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
      char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
      char_array_4[3] = char_array_3[2] & 0x3f;

      for (i = 0; i < 4; i++)
        encoded += chars[char_array_4[i]];
      i = 0;
    }
  }

  if (i) {
    for (j = i; j < 3; j++) char_array_3[j] = '\0';

    char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
    char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
    char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
    char_array_4[3] = char_array_3[2] & 0x3f;

    for (j = 0; j < i + 1; j++) encoded += chars[char_array_4[j]];
    while ((i++ < 3)) encoded += '=';
  }

  return encoded;
}

bool isAuthenticated(AsyncWebServerRequest *request) {
  if (!request->hasHeader("Authorization")) return false;
  String auth = request->header("Authorization");
  auth.replace("Basic ", "");
  auth.trim();
  String expected = base64encode(username + ":" + userpassword);
  return auth == expected;
}

void notAuthorized(AsyncWebServerRequest *request) {
  request->send(401, "text/plain", "Not authorized");
}

void setup() {
  Serial.begin(115200);
  WiFi.softAP(ssid, password);
  Serial.println("Access Point Started");

  dht.begin();
  ledcSetup(0, 5000, 8);
  ledcAttachPin(LED_PIN, 0);
  ledcSetup(1, 5000, 8);
  ledcAttachPin(FAN_PIN, 1);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  server.on("/dados", HTTP_GET, [](AsyncWebServerRequest *request){
    if (!isAuthenticated(request)) {
      notAuthorized(request);
      return;
    }
    int ldrValue = analogRead(LDR_PIN);
    float temp = dht.readTemperature();
    String json = "{";
    json += "\"ldr\":" + String(ldrValue) + ",";
    json += "\"temp\":" + String(temp) + ",";
    json += "\"led\":" + String(ledIntensity) + ",";
    json += "\"fan\":" + String(fanSpeed);
    json += "}";
    request->send(200, "application/json", json);
  });

  server.on("/set_led", HTTP_POST, [](AsyncWebServerRequest *request){
    if (!isAuthenticated(request)) {
      notAuthorized(request);
      return;
    }
    if (request->hasParam("value", true)) {
      ledIntensity = request->getParam("value", true)->value().toFloat();
      ledcWrite(0, ledIntensity);
    }
    request->send(200, "text/plain", "OK");
  });

  server.on("/set_fan", HTTP_POST, [](AsyncWebServerRequest *request){
    if (!isAuthenticated(request)) {
      notAuthorized(request);
      return;
    }
    if (request->hasParam("value", true)) {
      fanSpeed = request->getParam("value", true)->value().toFloat();
      ledcWrite(1, fanSpeed);
    }
    request->send(200, "text/plain", "OK");
  });

  server.begin();
}

void loop() {}
