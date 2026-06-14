#ifndef INNER_LED_H
#define INNER_LED_H

#include <Arduino.h>
#include "config.h"

class InnerLed {
  public: 
    uint8_t value = HIGH;
    unsigned long prevMillis = 0;
    unsigned long period = 0;

    InnerLed() {
      restorePin();
    }

    void restorePin() {
      pinMode(PIN_INNER_LED, OUTPUT);
      digitalWrite(PIN_INNER_LED, value);
    }
    
    void on(){
      set(HIGH);
      this->period = 0;
    }

    void off(){
      set(LOW);
      this->period = 0;
    }

    void set(int v){
      value = v;
      //Serial.print("InnerLed = ");
      //Serial.println(value);
      digitalWrite(PIN_INNER_LED, value);
    }

    void blink(unsigned long period){
      this->period = period;
    }

    void update() {
      if(period!=0){
        unsigned long currentMillis = millis();
        if (currentMillis - prevMillis >= period) {
          prevMillis = currentMillis;
          set(!value);
        }
      }
    }

};  

#endif

