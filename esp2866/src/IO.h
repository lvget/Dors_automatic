#ifndef IO_H_
#define IO_H_

#include <Arduino.h>

void IO_init();
void IO_loop();
void IO_setup();
void IO_command(String pin, int value);
String IO_values();
#endif