#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <SoftwareSerial.h>

SoftwareSerial s(3,1);
WiFiClient client;
HTTPClient http;

int grzanie = 19;
int chlodzenie = 25;
int dobratemperatura = 23;
int suszenie = 65;
int nawilzanie = 40;
int dobrawilgotnosc = 45;

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.print("ŁĄCZENIE Z SIECIĄ");
  WiFi.begin("nazwa", "haslo");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print("-");
  }
  Serial.println("");
  Serial.println("POŁĄCZONO");
  Serial.print(WiFi.localIP());
  delay(500);
  Serial.println("");
  Serial.println("ŁĄCZENIE Z SERWEREM");
}

void loop() {
     if (http.begin(client, "http://192.168.0.100/termohigrostat/progi/grzanie.txt"))
     {
       int kodHTTP = http.GET();
       if (kodHTTP == HTTP_CODE_OK) grzanie = http.getString().toInt();
       http.end();
     }

     if (http.begin(client, "http://192.168.0.100/termohigrostat/progi/chlodzenie.txt"))
     {
       int kodHTTP = http.GET();
       if (kodHTTP == HTTP_CODE_OK) chlodzenie = http.getString().toInt();
       http.end();
     }

     if (http.begin(client, "http://192.168.0.100/termohigrostat/progi/dobratemperatura.txt"))
     {
       int kodHTTP = http.GET();
       if (kodHTTP == HTTP_CODE_OK) dobratemperatura = http.getString().toInt();
       http.end();
     }

     if (http.begin(client, "http://192.168.0.100/termohigrostat/progi/suszenie.txt"))
     {
       int kodHTTP = http.GET();
       if (kodHTTP == HTTP_CODE_OK) suszenie = http.getString().toInt();
       http.end();
     }

     if (http.begin(client, "http://192.168.0.100/termohigrostat/progi/nawilzanie.txt"))
     {
       int kodHTTP = http.GET();
       if (kodHTTP == HTTP_CODE_OK) nawilzanie = http.getString().toInt();
       http.end();
     }

     if (http.begin(client, "http://192.168.0.100/termohigrostat/progi/dobrawilgotnosc.txt"))
     {
       int kodHTTP = http.GET();
       if (kodHTTP == HTTP_CODE_OK) dobrawilgotnosc = http.getString().toInt();
       http.end();
     }

    String grzanieS = String(grzanie);
    String chlodzenieS = String(chlodzenie);
    String dobratemperaturaS = String(dobratemperatura);
    String suszenieS = String(suszenie);
    String nawilzanieS = String(nawilzanie);
    String dobrawilgotnoscS = String(dobrawilgotnosc);
    String dowyslania = grzanieS + chlodzenieS + dobratemperaturaS + suszenieS + nawilzanieS + dobrawilgotnoscS;
    int dowyslaniaI;
    dowyslaniaI = dowyslania.toInt();
    
    s.write(dowyslaniaI);
    
    delay(3000);
}