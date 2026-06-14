#ifndef INNER_LED_H
#define INNER_LED_H

#include <Arduino.h>
#define INNER_LED_PIN D4

class InnerLed {
  public: 
    uint8_t value = HIGH;
    unsigned long prevMillis = 0;
    unsigned long period = 0;

    InnerLed() {
      restorePin();
    }

    void restorePin() {
      pinMode(INNER_LED_PIN, OUTPUT);
      digitalWrite(INNER_LED_PIN, value);
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
      digitalWrite(INNER_LED_PIN, value);
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

