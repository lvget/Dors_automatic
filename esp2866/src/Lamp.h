#ifndef LAMP_H
#define LAMP_H

#include <Arduino.h>


class Lamp {
  public: 
    uint8_t pin;

    uint8_t value;

    unsigned long prevMillis = 0;
    unsigned long period = 0;

    Lamp(uint8_t pin) {
      init(pin);
    }
    
    void init(uint8_t pin){
      this->pin = pin;
      pinMode(pin, OUTPUT);
      set(LOW);
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
      digitalWrite(pin, value);
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

