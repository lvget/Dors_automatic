
#ifndef __VK_BOT_H
#define __VK_BOT_H

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include "config.h"


// ================= НАСТРОЙКИ VK =================
String access_token = VK_ACCESS_TOKEN;
String user_id = VK_USER_ID;         // ID пользователя, который получит сообщение

// ================= ФУНКЦИЯ ОТПРАВКИ СООБЩЕНИЯ =================
void sendVKMessage(String messageText) {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClientSecure client;
    client.setInsecure(); // Отключаем проверку сертификата для упрощения (для продакшена так делать не стоит)

    HTTPClient https;
    String url = "https://api.vk.com/method/messages.send?user_id=" + user_id +
                  "&message=" + messageText +
                  "&access_token=" + access_token +
                  "&v=5.131&random_id=" + String(random(999999));

    Serial.print("[HTTP] Запрос к VK API...");
    https.begin(client, url);

    int httpCode = https.GET();
    if (httpCode > 0) {
      Serial.printf(" [HTTP] GET... код: %d\n", httpCode);
      if (httpCode == HTTP_CODE_OK) {
        String payload = https.getString();
        Serial.println("Ответ сервера: " + payload);
      }
    } else {
      Serial.printf("[HTTP] Ошибка: %s\n", https.errorToString(httpCode).c_str());
    }
    https.end();
  } else {
    Serial.println("Ошибка: нет подключения к Wi-Fi");
  }
}

#endif
