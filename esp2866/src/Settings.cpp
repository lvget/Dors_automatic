#include "Settings.h"
#include "globals.h"
#include <Arduino.h>
#include <EEPROM.h>
#include "ArduinoJson-v7.4.3.h"


void Settings::begin(){
  EEPROM.begin(sizeof(Settings));
  int _ver = 0;
  EEPROM.get(0, _ver);
  Serial.print("ver: "); Serial.println(_ver);

  if(_ver == ver){
    EEPROM.get(0, *this); // Читаем данные из адреса 0
  }
  else{
    // ver = 1;
    // intervalLED = 1000;
    // modeLampL = AUTO;
    // modeLampR = AUTO;
    // modeLampIn = AUTO;
    // modeSwL = AUTO;
    // modeSwR = AUTO;
    // modeSwDor = AUTO;
    save();
  }

}

void Settings::save(){
  EEPROM.put(0, *this);
  EEPROM.commit(); // Сохраняем во Flash-память
  //if (isSaved) {
    Serial.println("Данные успешно сохранены!");
  //}
}

String Settings::toJson(){
  JsonDocument doc;
  doc["intervalLED"] = intervalLED;
  doc["nightBegin"] = nightBegin;
  doc["nightEnd"] = nightEnd;
  doc["autoOffMinute"] = autoOffMinute;
  doc["mp3FileNumber"] = mp3FileNumber;

  doc["LampL"] = modeLampL;
  doc["LampR"] = modeLampR;
  doc["LampIn"] = modeLampIn;
  doc["SwR"] = modeSwR;
  doc["SwL"] = modeSwL;
  doc["SwDor"] = modeSwDor;
  
  doc["time"] = appClock.getFormattedTime();
  doc["ver"] = ver;
  
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

    intervalLED = doc["intervalLED"]|SETTINGS_INTERVAL_LED_DEFAULT;
    modeLampL = doc["LampL"]|modeLampL;
    modeLampR = doc["LampR"]|modeLampR;
    modeLampIn = doc["LampIn"]|modeLampIn;
    modeSwR = doc["SwR"]|modeSwR;
    modeSwL = doc["SwL"]|modeSwL;
    modeSwDor = doc["SwDor"]|modeSwDor;
    nightBegin = doc["nightBegin"]|nightBegin;
    nightEnd = doc["nightEnd"]|nightEnd;
    autoOffMinute = doc["autoOffMinute"]|autoOffMinute;
    mp3FileNumber = doc["mp3FileNumber"]|mp3FileNumber;

    save();
    io.setup();
    return true;
}
