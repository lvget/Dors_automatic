#include "VkBot.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include "globals.h"

VkBot::VkBot() {}

void VkBot::sendMessage(const String &messageText) {
  if (enqueue(messageText)) {
    Serial.println("VK message queued");
  } else {
    Serial.println("VK message queue is full");
  }
}

void VkBot::loop() {
  if (queueCount == 0 || millis() < nextAttemptMillis || mp3Player.isPlaying()) {
    return;
  }

  String messageText;
  if (dequeue(messageText)) {
    sendQueuedMessage(messageText);
  }
}

bool VkBot::enqueue(const String &messageText) {
  if (queueCount >= QUEUE_SIZE) {
    return false;
  }

  messages[queueTail] = messageText;
  queueTail = (queueTail + 1) % QUEUE_SIZE;
  queueCount++;
  return true;
}

bool VkBot::dequeue(String &messageText) {
  if (queueCount == 0) {
    return false;
  }

  messageText = messages[queueHead];
  messages[queueHead] = "";
  queueHead = (queueHead + 1) % QUEUE_SIZE;
  queueCount--;
  return true;
}

void VkBot::sendQueuedMessage(const String &messageText) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Error: Wi-Fi is not connected");
    enqueue(messageText);
    nextAttemptMillis = millis() + 5000;
    return;
  }

  WiFiClientSecure client;
  client.setInsecure();

  HTTPClient https;
  String url = "https://api.vk.com/method/messages.send?user_id=" + urlEncode(settings.vkUserId) +
               "&message=" + urlEncode(messageText) +
               "&access_token=" + urlEncode(settings.vkAccessToken) +
               "&v=5.131&random_id=" + String(random(1, 2147483647));

  Serial.print("[HTTP] Request to VK API...");
  https.begin(client, url);
  https.setTimeout(1000);

  int httpCode = https.GET();
  if (httpCode > 0) {
    Serial.printf(" [HTTP] GET... code: %d\n", httpCode);
    Serial.println("VK response: " + https.getString());
  } else {
    Serial.printf("[HTTP] Error: %s\n", https.errorToString(httpCode).c_str());
  }

  https.end();
}

String VkBot::urlEncode(const String &value) {
  const char hex[] = "0123456789ABCDEF";
  String encoded;
  encoded.reserve(value.length() * 3);

  for (size_t i = 0; i < value.length(); i++) {
    uint8_t c = static_cast<uint8_t>(value[i]);
    if ((c >= 'A' && c <= 'Z') ||
        (c >= 'a' && c <= 'z') ||
        (c >= '0' && c <= '9') ||
        c == '-' || c == '_' || c == '.' || c == '~') {
      encoded += static_cast<char>(c);
    } else {
      encoded += '%';
      encoded += hex[c >> 4];
      encoded += hex[c & 0x0F];
    }
  }

  return encoded;
}
