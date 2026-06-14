#ifndef SETTINGS_H
#define SETTINGS_H

#include "ArduinoJson-v7.4.3.h"
#include "IoPin.h"

class Settings {

public:
  int ver = 5;
  unsigned long intervalLED = 1000;
  uint8_t nightBegin = 20;
  uint8_t nightEnd = 7;
  uint8_t autoOffMinute = 5;
  uint16_t mp3FileNumber = 0;

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
