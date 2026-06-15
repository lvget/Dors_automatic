#ifndef SETTINGS_H
#define SETTINGS_H

#include "ArduinoJson-v7.4.3.h"
#include "IoPin.h"
#include "config.h"
#define SETTINGS_VERSION 7

class Settings {

public:
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
  char vkAccessToken[SETTINGS_VK_ACCESS_TOKEN_SIZE] = VK_ACCESS_TOKEN;
  char vkUserId[SETTINGS_VK_USER_ID_SIZE] = VK_USER_ID;

public:
  void begin();
  void save();
  String toJson();
  bool fromJson(String& json);

private:
  static const char JSON_INTERVAL_LED[];
  static const char JSON_NIGHT_BEGIN[];
  static const char JSON_NIGHT_END[];
  static const char JSON_AUTO_OFF_MINUTE[];
  static const char JSON_MP3_FILE_NUMBER[];
  static const char JSON_VK_ACCESS_TOKEN[];
  static const char JSON_VK_USER_ID[];
};



#endif
