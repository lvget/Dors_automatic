#ifndef IO_PIN_H_
#define IO_PIN_H_

#include <Arduino.h>
#include "config.h"

#define OFF 1
#define ON 0
#define AUTO 2

#define UP 1
#define DOWN 0
#define NONE 2 
// enum INPUT_E : uint8_t  {
//   OFF = 0,
//   ON,
//   AUTO
// };

class IoPin{
  protected:
    uint8_t mode;
    uint8_t pin;
    uint8_t value;
  public:
    IoPin(uint8_t pin, const char* name){
      this->pin = pin;
      this->name = name;
      this->mode = AUTO;
      this->value = OFF;
    };
    uint8_t getValue(){ return mode==AUTO? value : mode; }; //return value;
    String name;
};

class Input: public IoPin{
  uint8_t change = NONE;
  uint8_t lastRawValue = OFF;
  unsigned long lastDebounceTime = 0;
  static const unsigned long debounceDelay = INPUT_DEBOUNCE_DELAY_MS;
  public:
    Input(uint8_t pin, const char* name): IoPin(pin, name){};
    void init();
    void read();
    void setMode(uint8_t mode);
    inline bool isOn(){return mode==AUTO? value == ON : mode == ON; };
    inline bool isChange() { return mode==AUTO? change != NONE : false; };
};

class Output: public IoPin{

  public:
  Output(uint8_t pin, const char* name): IoPin(pin, name){};
    void init();
    void write(int v);
    void setMode(uint8_t mode);
    inline void on(){ write(ON); }
    inline void off(){ write(OFF); }
};

#endif
