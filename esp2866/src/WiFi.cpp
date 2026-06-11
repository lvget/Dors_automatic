#include "globals.h"
#include "WiFi.h"
#include <ESP8266WiFi.h>

//const char* ssid =     "kofein_wifi";     //  SSID wi-fi роутера
//const char* password = "K0255E1N"; // Пароль от wi-fi
#define ssid "kofein_wifi"     //  SSID wi-fi роутера
#define password "K0255E1N" // Пароль от wi-fi

void WiFiInit(){
  Serial.println("WiFi Init");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }
}