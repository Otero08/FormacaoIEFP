
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
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

bool isAuthenticated(AsyncWebServerRequest *request) {
  if (!request->hasHeader("Authorization")) return false;
  String auth = request->header("Authorization");
  auth.replace("Basic ", "");
  auth.trim();
  String expected = base64::encode(username + ":" + userpassword);
  return auth.equals(expected);
}

void notAuthorized(AsyncWebServerRequest *request) {
  request->send(401, "text/plain", "Not authorized");
}

void setup() {
  Serial.begin(115200);
  WiFi.softAP(ssid, password);
  Serial.println("Access Point Started");

  if (!SPIFFS.begin(true)) {
    Serial.println("Erro ao montar SPIFFS");
    return;
  }

  dht.begin();
  ledcSetup(0, 5000, 8); // Canal 0 para LED
  ledcAttachPin(LED_PIN, 0);
  ledcSetup(1, 5000, 8); // Canal 1 para ventoinha
  ledcAttachPin(FAN_PIN, 1);

  server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");

  server.on("/dados", HTTP_GET, [](AsyncWebServerRequest *request){
    if (!isAuthenticated(request)) {
      notAuthorized(request);
      return;
    }
    int ldrValue = analogRead(LDR_PIN);
    float temp = dht.readTemperature();
    String json = "{";
    json += ""ldr":" + String(ldrValue) + ",";
    json += ""temp":" + String(temp) + ",";
    json += ""led":" + String(ledIntensity) + ",";
    json += ""fan":" + String(fanSpeed);
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
