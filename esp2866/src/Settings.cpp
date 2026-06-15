#include "Settings.h"
#include "globals.h"
#include <Arduino.h>
#include <EEPROM.h>
#include <string.h>
#include "ArduinoJson-v7.4.3.h"

const char Settings::JSON_INTERVAL_LED[] = "intervalLED";
const char Settings::JSON_NIGHT_BEGIN[] = "nightBegin";
const char Settings::JSON_NIGHT_END[] = "nightEnd";
const char Settings::JSON_AUTO_OFF_MINUTE[] = "autoOffMinute";
const char Settings::JSON_MP3_FILE_NUMBER[] = "mp3FileNumber";
const char Settings::JSON_VK_ACCESS_TOKEN[] = "vkAccessToken";
const char Settings::JSON_VK_USER_ID[] = "vkUserId";

static void copySettingString(char *target, size_t targetSize, const char *value) {
  if (value == nullptr || targetSize == 0) {
    return;
  }

  strncpy(target, value, targetSize - 1);
  target[targetSize - 1] = '\0';
}


void Settings::begin(){
  EEPROM.begin(sizeof(Settings));
  int _ver = 0;
  EEPROM.get(0, _ver);
  //Serial.print("ver: "); Serial.println(_ver);

  if(_ver == SETTINGS_VERSION){
    EEPROM.get(0, *this); // Читаем данные из адреса 0
  }
  else{
    save();
  }

}

void Settings::save(){
  EEPROM.put(0, *this);
  EEPROM.commit(); // Сохраняем во Flash-память
  //if (isSaved) {
    Serial.println("Settings saved!");
  //}
}

String Settings::toJson(){
  JsonDocument doc;
  doc[JSON_NIGHT_BEGIN] = nightBegin;
  doc[JSON_NIGHT_END] = nightEnd;
  doc[JSON_AUTO_OFF_MINUTE] = autoOffMinute;
  doc[JSON_MP3_FILE_NUMBER] = mp3FileNumber;
  doc[JSON_VK_ACCESS_TOKEN] = vkAccessToken;
  doc[JSON_VK_USER_ID] = vkUserId;

  doc[io.lampLeft.name] = modeLampL;
  doc[io.lampRight.name] = modeLampR;
  doc[io.lampIn.name] = modeLampIn;
  doc[io.switchRight.name] = modeSwR;
  doc[io.switchLeft.name] = modeSwL;
  doc[io.switchDor.name] = modeSwDor;

  
  String json;
  serializeJson(doc, json);
  return json;
}

bool Settings::fromJson(String& json){
    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, json);

    if (error) {
        return false;
    }
    modeLampL = doc[io.lampLeft.name]|modeLampL;
    modeLampR = doc[io.lampRight.name]|modeLampR;
    modeLampIn = doc[io.lampIn.name]|modeLampIn;
    modeSwR = doc[io.switchRight.name]|modeSwR;
    modeSwL = doc[io.switchLeft.name]|modeSwL;
    modeSwDor = doc[io.switchDor.name]|modeSwDor;

    nightEnd = doc[JSON_NIGHT_END]|nightEnd;
    autoOffMinute = doc[JSON_AUTO_OFF_MINUTE]|autoOffMinute;
    nightBegin = doc[JSON_NIGHT_BEGIN]|nightBegin;
    mp3FileNumber = doc[JSON_MP3_FILE_NUMBER]|mp3FileNumber;

    const char *vkAccessTokenValue = doc[JSON_VK_ACCESS_TOKEN];
    const char *vkUserIdValue = doc[JSON_VK_USER_ID];
    copySettingString(vkAccessToken, sizeof(vkAccessToken), vkAccessTokenValue);
    copySettingString(vkUserId, sizeof(vkUserId), vkUserIdValue);

    save();
    io.setup();
    return true;
}
