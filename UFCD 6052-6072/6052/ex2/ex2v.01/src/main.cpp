#include <Arduino.h>
#include <Wifi.h>
#include <WebServer.h>

//strings noome do router + password

typedef struct o_meu_wifi
{
  String ssid ;
  String password ;
};

o_meu_wifi o_meu_Wifi = 
{
  .ssid = "IEFP-Formacao",
  .password = ""
};

WebServer server(80); //criar um servidor na porta 80

void Root();



void setup ()
{
  //configure the serial port
  Serial.begin(115200);
  
  //iniciazizar dois perifericos como output
  pinMode(D11,OUTPUT);
  pinMode(D10,OUTPUT);

  //Inicializa oS Perifericos COMO LOW
  digitalWrite(D11,LOW);
  digitalWrite(D10,LOW);

  //conectar internet
  Serial.print("Connecting to WiFi...");
  Serial.println(o_meu_Wifi.ssid);
  WiFi.begin(o_meu_Wifi.ssid.c_str(), o_meu_Wifi.password.c_str());

  //testar 5 vezes ate a conexao ser efectuada e esperar 0.5segundos entre tentativas
  int tentativas= 0;
    while(WiFi.status() != WL_CONNECTED && tentativas < 5)
    {
      delay(500);
      Serial.print(".");
      tentativas++;
    }
    if(WiFi.status() != WL_CONNECTED)
    {
      Serial.println("nao conectou ao WIFI");
    }
    else
    {
      Serial.print("Conectou ao WIFI");
      Serial.println(o_meu_Wifi.ssid);
      Serial.println(WiFi.localIP());
    }
 
    server.on("/",Root);

//Conectar ao servidor
    server.begin();
}
  void Root()
  {
      String pagina = R"rawliteral(
      <!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Exercício</title>
    <style>
        html {
            font-family: Helvetica;
            display: center;
            margin: 30px auto;
            text-align: center;
        }
        body {
            background-image: url('https://wallpapers.com/images/featured-full/imagem-de-fundo-yeaxrij2aepc1xio.jpg'); /* Altere para o link real */
            background-size: cover;
            background-position: center;
            background-repeat: no-repeat;
            margin: 0;
            padding: 0;
        }
        .button {
            background-color: rgb(210, 8, 8);
            border: 3px solid black;
            color: white;
            padding: 16px 40px;
            text-decoration: none;
            font-size: 30px;
            margin: 2px;
            border-radius: 10px;
            cursor: pointer;
        }
        .button2 {
            background-color: rgb(54, 12, 205);
        }
    </style>
</head>
<body>
    <h1>Diogo Otero ------ ESP32 Web Server</h1>
    <p><a href="/26/on"><button class="button">ON</button></a></p>
    <p><a href="/27/on"><button class="button button2">ON</button></a></p>
</body>
</html>

  
      )rawliteral";
      server.send(200,"text/html", pagina);
  }

  

  

