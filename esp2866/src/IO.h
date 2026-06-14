#ifndef IO_H_
#define IO_H_

#include <Arduino.h>
#include "InnerLed.h"
#include "IoPin.h"

class IO {
public:
  void init();
  void loop();
  void setup();
  void restorePins();
  void command(String pin, int value);
  String values();

private:
  Input switchLeft = Input(D1, "SwL");
  Input switchRight = Input(D2, "SwR");
  Input switchDor = Input(D3, "SwDor");
  Input doorbellButton = Input(D0, "Doorbell");

  Output lampLeft = Output(D5, "LampL");
  Output lampRight = Output(D6, "LampR");
  Output lampIn = Output(D7, "LampIn");

  InnerLed innerLed = InnerLed{};
};

#endif
