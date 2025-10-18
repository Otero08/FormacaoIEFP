#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <PID_v1.h>

// --- Configurações de Rede ---
const char* ssid = "Vodafone-ACD044";
const char* password = "";

// --- Configurações de Pinos ---
#define LED_PIN  12   // Pino PWM para LED
#define LDR_PIN  39   // Pino ADC para LDR
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 10; // 10 bits (0–1023)

// --- Limite máximo real do LDR ---
const double LDR_MAX = 930.0;

// --- Variáveis de Controle PID ---
double Setpoint = 500;   // Valor inicial desejado de luminosidade
double Input;            // Leitura atual do LDR
double Output;           // Saída PWM para o LED
double Kp = 0.7, Ki = 0.05, Kd = 0.1;
double deadband = 20;    // Zona de tolerância

PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

// --- Web Server e WebSocket ---
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

// --- Dados para gráfico ---
const int MAX_DATA_POINTS = 50;
String chartDataLDR = "[]";
String chartDataSP = "[]";
String chartDataPWM = "[]";

// Protótipo do HTML
const char* HTML_PAGE_CODE_P();

// --- WebSocket Handler ---
void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo*)arg;

  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;
    String msg = (char*)data;

    if (msg.startsWith("SP:")) {
      double novoSetpoint = msg.substring(3).toDouble();
      if (novoSetpoint > LDR_MAX) novoSetpoint = LDR_MAX;
      if (novoSetpoint < 0) novoSetpoint = 0;
      Setpoint = novoSetpoint;
      Serial.printf("Novo SetPoint: %.1f\n", Setpoint);
    } else if (msg.startsWith("Kp:")) {
      Kp = msg.substring(3).toDouble();
      myPID.SetTunings(Kp, Ki, Kd);
      Serial.printf("Novo Kp: %.3f\n", Kp);
    } else if (msg.startsWith("Ki:")) {
      Ki = msg.substring(3).toDouble();
      myPID.SetTunings(Kp, Ki, Kd);
      Serial.printf("Novo Ki: %.3f\n", Ki);
    } else if (msg.startsWith("Kd:")) {
      Kd = msg.substring(3).toDouble();
      myPID.SetTunings(Kp, Ki, Kd);
      Serial.printf("Novo Kd: %.3f\n", Kd);
    }
  }
}

// --- Eventos do WebSocket ---
void onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
               void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("Cliente WS conectado #%u\n", client->id());
      client->text(String("DATA:") + chartDataLDR + "|" + chartDataSP + "|" + chartDataPWM);
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("Cliente WS desconectado #%u\n", client->id());
      break;
    case WS_EVT_DATA:
      handleWebSocketMessage(arg, data, len);
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }
}

// --- Atualiza gráfico e envia dados ---
void notifyClients(double ldr, double sp, double pwm) {
  String message = String("NEW_DATA:") + ldr + "|" + sp + "|" + pwm;
  ws.textAll(message);
}

void updateChartData(double ldr, double sp, double pwm) {
  if (chartDataLDR.length() > 2000) {
    chartDataLDR = "[]";
    chartDataSP = "[]";
    chartDataPWM = "[]";
  }

  if (chartDataLDR.endsWith("]")) chartDataLDR.remove(chartDataLDR.length() - 1);
  if (chartDataSP.endsWith("]")) chartDataSP.remove(chartDataSP.length() - 1);
  if (chartDataPWM.endsWith("]")) chartDataPWM.remove(chartDataPWM.length() - 1);

  if (chartDataLDR.length() > 1) chartDataLDR += ",";
  if (chartDataSP.length() > 1) chartDataSP += ",";
  if (chartDataPWM.length() > 1) chartDataPWM += ",";

  chartDataLDR += String(ldr);
  chartDataSP += String(sp);
  chartDataPWM += String(pwm);

  chartDataLDR += "]";
  chartDataSP += "]";
  chartDataPWM += "]";
}

// --- SETUP ---
void setup() {
  Serial.begin(115200);

  // PWM
  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(LED_PIN, ledChannel);
  ledcWrite(ledChannel, 0);

  // PID
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(0, 1023);

  // WiFi
  WiFi.begin(ssid, password);
  Serial.print("Conectando ao WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("WiFi conectado! IP: ");
  Serial.println(WiFi.localIP());

  // WebSocket + Servidor
  ws.onEvent(onWsEvent);
  server.addHandler(&ws);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", HTML_PAGE_CODE_P());
  });

  server.begin();
  Serial.println("Servidor Web iniciado.");
}

// --- LOOP ---
void loop() {
  static unsigned long lastTime = 0;
  const long sampleTime = 100; // ms

  if (millis() - lastTime >= sampleTime) {
    lastTime = millis();

    Input = analogRead(LDR_PIN);

    // --- Controle direto para extremos ---
    if (Setpoint <= 0) {
      Output = 0;  // LED desligado
      myPID.SetMode(MANUAL);
    } else if (Setpoint >= LDR_MAX) {
      Output = 1023;  // LED no máximo
      myPID.SetMode(MANUAL);
    } else {
      // PID para valores intermédios
      myPID.SetMode(AUTOMATIC);
      myPID.Compute();
    }

    // Atualiza LED
    ledcWrite(ledChannel, (int)Output);

    // Atualiza gráfico e envia dados
    updateChartData(Input, Setpoint, Output);
    notifyClients(Input, Setpoint, Output);

    Serial.printf("LDR: %.0f | SP: %.0f | PWM: %.0f\n", Input, Setpoint, Output);
  }

  ws.cleanupClients();
}

// --- PÁGINA HTML ---
const char* HTML_PAGE_CODE_P() {
  const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>ESP32 PID Control LDR/LED</title>
    <script src="https://cdn.jsdelivr.net/npm/chart.js@3.7.1/dist/chart.min.js"></script>
    <style>
        body { font-family: Arial, sans-serif; text-align: center; background-color: #f4f4f9; }
        .container { max-width: 900px; margin: auto; padding: 20px; background-color: #fff;
                     border-radius: 8px; box-shadow: 0 2px 4px rgba(0,0,0,0.1); }
        h1 { color: #333; }
        .data-display { display: flex; justify-content: space-around; margin: 20px 0; }
        .data-box { padding: 10px; border: 1px solid #ccc; border-radius: 4px; flex-basis: 30%; background-color: #e9e9e9; }
        .data-box h3 { margin: 5px 0; font-size: 1.2em; color: #555; }
        .data-box p { font-size: 1.8em; font-weight: bold; margin: 0; }
        .control-group { margin-bottom: 20px; padding: 15px; border: 1px solid #ddd; border-radius: 6px; }
        .chart-container { margin-top: 30px; border: 1px solid #ddd; padding: 10px; border-radius: 6px; background-color: #fafafa; }
    </style>
</head>
<body>
    <div class="container">
        <h1>Controlo de Luminosidade PID (LDR/LED)</h1>
        <div class="data-display">
            <div class="data-box"><h3>LDR Atual (PV)</h3><p id="pvValue">0</p></div>
            <div class="data-box"><h3>SetPoint (SP)</h3><p id="spValue">0</p></div>
            <div class="data-box"><h3>PWM (Output)</h3><p id="pwmValue">0</p></div>
        </div>

        <div class="control-group">
            <label>SetPoint de Luz (0–930):</label>
            <input type="range" id="setpoint" min="0" max="930" step="5" value="%SETPOINT_VAL%" onchange="updateSP(this.value)">
            <input type="number" id="setpoint-num" min="0" max="930" step="5" value="%SETPOINT_VAL%" onchange="updateSP(this.value)">
        </div>

        <div class="control-group">
            <label>Kp:</label><input type="number" id="kp" step="0.01" value="%KP_VAL%" onchange="updatePID('Kp', this.value)">
            <label>Ki:</label><input type="number" id="ki" step="0.001" value="%KI_VAL%" onchange="updatePID('Ki', this.value)">
            <label>Kd:</label><input type="number" id="kd" step="0.01" value="%KD_VAL%" onchange="updatePID('Kd', this.value)">
        </div>

        <div class="chart-container">
            <h2>Monitorização em Tempo Real</h2>
            <canvas id="pidChart" height="150"></canvas>
        </div>
    </div>

    <script>
        var ws;
        var maxDataPoints = %MAX_DATA_POINTS%;
        var chartDataLDR = [], chartDataSP = [], chartDataPWM = [];
        var pidChart;

        window.onload = function() {
            initWebSocket();
            initChart();
        }

        function initWebSocket() {
            ws = new WebSocket('ws://' + window.location.host + '/ws');
            ws.onopen = () => console.log('WebSocket conectado');
            ws.onclose = () => setTimeout(initWebSocket, 2000);
            ws.onmessage = (evt) => {
                if (evt.data.startsWith("NEW_DATA:")) updateRealtimeData(evt.data.substring(9));
            };
        }

        function initChart() {
            const ctx = document.getElementById('pidChart').getContext('2d');
            pidChart = new Chart(ctx, {
                type: 'line',
                data: { labels: [], datasets: [
                    { label: 'LDR (PV)', data: chartDataLDR, borderColor: 'rgb(75,192,192)', fill: false },
                    { label: 'SetPoint (SP)', data: chartDataSP, borderColor: 'rgb(255,99,132)', fill: false },
                    { label: 'PWM (Output)', data: chartDataPWM, borderColor: 'rgb(54,162,235)', fill: false, hidden: true }
                ]},
                options: { animation: false, responsive: true, scales: { y: { beginAtZero: true, max: 930 } } }
            });
        }

        function updateRealtimeData(data) {
            var [ldr, sp, pwm] = data.split('|').map(parseFloat);
            document.getElementById('pvValue').innerHTML = ldr.toFixed(0);
            document.getElementById('spValue').innerHTML = sp.toFixed(0);
            document.getElementById('pwmValue').innerHTML = pwm.toFixed(0);

            chartDataLDR.push(ldr);
            chartDataSP.push(sp);
            chartDataPWM.push(pwm);

            if (chartDataLDR.length > maxDataPoints) {
                chartDataLDR.shift(); chartDataSP.shift(); chartDataPWM.shift();
                pidChart.data.labels.shift();
            }
            pidChart.data.labels.push(pidChart.data.labels.length);
            pidChart.update();
        }

        function updateSP(value) {
            document.getElementById('setpoint').value = value;
            document.getElementById('setpoint-num').value = value;
            if (ws.readyState === WebSocket.OPEN) ws.send('SP:' + value);
        }

        function updatePID(param, value) {
            if (ws.readyState === WebSocket.OPEN) ws.send(param + ':' + value);
        }
    </script>
</body>
</html>
)rawliteral";

  static String html_buffer;
  html_buffer = index_html;
  html_buffer.replace("%SETPOINT_VAL%", String(Setpoint));
  html_buffer.replace("%KP_VAL%", String(Kp));
  html_buffer.replace("%KI_VAL%", String(Ki));
  html_buffer.replace("%KD_VAL%", String(Kd));
  html_buffer.replace("%MAX_DATA_POINTS%", String(MAX_DATA_POINTS));

  return html_buffer.c_str();
}
