#ifndef GLOBALS_H
#define GLOBALS_H

#include "WiFi.h"
#include "AppClock.h"
#include "Settings.h"
#include "WebServer.h"
#include <LittleFS.h>
#include "IO.h"

extern Settings settings;
extern AppClock appClock;
extern WebServer webServer;

#endif