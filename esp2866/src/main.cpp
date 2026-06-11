#include <Arduino.h>
#include "globals.h"

void setup() {
  Serial.begin(115200);
  
  settings.begin();

  if (!LittleFS.begin()) {
    Serial.println("LittleFS Mount Failed");
    return;
  }

  WiFiInit();
  appClock.begin();
  webServer.begin();

  IO_init();
  IO_setup();
}

void loop() {
   // Обновляем статус синхронизации (можно вызывать и реже, например, раз в 100 мс)
  appClock.update();

  IO_loop();
  mp3Player.loop();

  webServer.loop();
}
