
#include "IO.h"
#include <Arduino.h>
#include "globals.h"
//#include "VkBot.h"

void IO::init() {
  switchLeft.init();
  switchRight.init();
  switchDor.init();
  doorbellButton.init();
  lampLeft.init();
  lampRight.init();
  lampIn.init();

  innerLed.blink(settings.intervalLED);
}

void IO::loop() {
  switchLeft.read();
  switchRight.read();
  switchDor.read();
  doorbellButton.read();

  innerLed.update();

  if (doorbellButton.isChange() && doorbellButton.isOn()) {
    Serial.println("Doorbell pressed");
    mp3Player.playDoorbell(settings.mp3FileNumber);
  }

  if(switchLeft.isChange() || switchRight.isChange() || switchDor.isChange())
  {
    if(switchLeft.isOn()){
      lampLeft.on();
    }
    else{
      lampLeft.off();
    }
    

    if(switchRight.isOn()){
      lampRight.on();
    }
    else{
      lampRight.off();
    }
    
    if(switchDor.isOn()){
      lampIn.on();
    }
    else{
      lampIn.off();
    }
  }

  if( switchDor.isChange()){
    if(switchDor.isOn()){
      //sendVKMessage("Дверь открыта");
    }
    else{
      //sendVKMessage("Дверь закрыта");
    }
  }


}

void IO::setup(){
  innerLed.blink(settings.intervalLED);
  lampLeft.setMode(settings.modeLampL);
  lampRight.setMode(settings.modeLampR);
  lampIn.setMode(settings.modeLampIn);
  switchLeft.setMode(settings.modeSwL);
  switchRight.setMode(settings.modeSwR);
  switchDor.setMode(settings.modeSwDor);
}

void IO::restorePins(){
  innerLed.restorePin();
}

void IO::command(String id, int value){
  if(id == lampLeft.name)lampLeft.write(value);
  else if(id == lampRight.name)lampRight.write(value);
  else if(id == lampIn.name)lampIn.write(value);
}

String IO::values(){
  JsonDocument doc;
  doc[lampLeft.name] = lampLeft.getValue();
  doc[lampRight.name] = lampRight.getValue();
  doc[lampIn.name] = lampIn.getValue();
  doc[switchRight.name] = switchRight.getValue();
  doc[switchLeft.name] = switchLeft.getValue();
  doc[switchDor.name] = switchDor.getValue();
  doc[doorbellButton.name] = doorbellButton.getValue();

  String json;
  serializeJson(doc, json);
  return json;
}
