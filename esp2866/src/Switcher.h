#ifndef SWITCHER_H
#define SWITCHER_H

#include <Arduino.h>

enum SwitchChange
{
  NONE = 0,

};

class Switcher {
  public: 
    uint8_t pin;
    uint8_t value;
    SwitchChange change = NONE;
    unsigned long lastChange = 0;
    
    Switcher() {
    }

   void init(uint8_t pin){
      this->pin = pin;
      pinMode(pin, INPUT_PULLUP);
      value = digitalRead(pin);
    }

    void update() {
      bool v = digitalRead(pin);
      if (v != value) {
        value = v;
        lastChange = millis();
      }
    }

    bool isOn() {
      return value;
    }
};

#endif