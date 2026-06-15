#ifndef IO_H_
#define IO_H_

#include <Arduino.h>
#include "InnerLed.h"
#include "IoPin.h"
#include "config.h"

class IO {
  friend class Settings;

public:
  void init();
  void loop();
  void setup();
  void restorePins();
  void command(String pin, int value);
  String values();

private:
  Input switchLeft = Input(PIN_SWITCH_LEFT, IO_NAME_SWITCH_LEFT);
  Input switchRight = Input(PIN_SWITCH_RIGHT, IO_NAME_SWITCH_RIGHT);
  Input switchDor = Input(PIN_SWITCH_DOOR, IO_NAME_SWITCH_DOOR);
  Input doorbellButton = Input(PIN_DOORBELL_BUTTON, IO_NAME_DOORBELL);

  Output lampLeft = Output(PIN_LAMP_LEFT, IO_NAME_LAMP_LEFT);
  Output lampRight = Output(PIN_LAMP_RIGHT, IO_NAME_LAMP_RIGHT);
  Output lampIn = Output(PIN_LAMP_IN, IO_NAME_LAMP_IN);

  InnerLed innerLed = InnerLed{};
};

#endif
