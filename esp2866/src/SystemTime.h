#ifndef __SYSTEMTIME_H
#define __SYSTEMTIME_H

#include <time.h>
#include <NTPClient.h>

#define TIME_ZONE 5*60*60   // смещение от UTC в секундах
#define daylightOffset_sec 0 // смещение на летнее время в секундах
#define NTP_SERVER "pool.ntp.org"
NTPClient timeClient(ntpUDP, "pool.ntp.org", 5*60*60, 60000);

class SystemTime(){

  SystemTime(){
    configTime(TIME_ZONE, 0, NTP_SERVER);
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