#ifndef __SYSTEMTIME_H
#define __SYSTEMTIME_H

#include <time.h>
#include <NTPClient.h>
#include "config.h"

NTPClient timeClient(ntpUDP, APP_CLOCK_NTP_SERVER, APP_CLOCK_TZ_OFFSET, 60000);

class SystemTime(){

  SystemTime(){
    configTime(APP_CLOCK_TZ_OFFSET, 0, APP_CLOCK_NTP_SERVER);
  }
  void init(){
    //timeClient.begin();              // Запуск клиента NTP
    

    while (time(nullptr) < 100000) {
      delay(100);
      //Serial.print(".");
    }
  }

  void sync(){
    timeClient.update();             // Обновление времени с сервера
  }

  char* currentTime(){
    time_t now = time(nullptr);
    struct tm *timeinfo = localtime(&now);

    char buffer[9]; // "HH:MM:SS"
    return strftime(buffer, sizeof(buffer), "%H:%M:%S", tm);
    return buffer;
  }
}

#endif
