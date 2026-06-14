#ifndef SETTINGS_H
#define SETTINGS_H

#include "ArduinoJson-v7.4.3.h"
#include "IoPin.h"
#include "config.h"

class Settings {

public:
  int ver = SETTINGS_VERSION;
  unsigned long intervalLED = SETTINGS_INTERVAL_LED_DEFAULT;
  uint8_t nightBegin = SETTINGS_NIGHT_BEGIN_DEFAULT;
  uint8_t nightEnd = SETTINGS_NIGHT_END_DEFAULT;
  uint8_t autoOffMinute = SETTINGS_AUTO_OFF_MINUTE_DEFAULT;
  uint16_t mp3FileNumber = SETTINGS_MP3_FILE_NUMBER_DEFAULT;

  uint8_t modeLampL = AUTO;
  uint8_t modeLampR = AUTO;
  uint8_t modeLampIn = AUTO;
  uint8_t modeSwL = AUTO;
  uint8_t modeSwR = AUTO;
  uint8_t modeSwDor = AUTO;

public:
  void begin();
  void save();
  String toJson();
  bool fromJson(String& json);
};



#endif
