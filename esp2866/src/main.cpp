#include <Arduino.h>
#include "globals.h"

void setup() {
  Serial.begin(115200);
  Serial.print("Reset reason: ");
  Serial.println(ESP.getResetReason());
  
  settings.begin();

  if (!LittleFS.begin()) {
    Serial.println("LittleFS Mount Failed");
    return;
  }

  WiFiInit();
  appClock.begin();
  webServer.begin();

  io.init();
  io.setup();
}

void loop() {
   // Обновляем статус синхронизации (можно вызывать и реже, например, раз в 100 мс)
  mp3Player.loop();
  appClock.update();

  io.loop();
  mp3Player.loop();

  vkBot.loop();
  webServer.loop();
  httpClient.update();
}
