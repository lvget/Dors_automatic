#ifndef GLOBALS_H
#define GLOBALS_H

#include "WiFi.h"
#include "AppClock.h"
#include "Settings.h"
#include "WebServer.h"
#include <LittleFS.h>
#include "IO.h"
#include "Mp3Player.h"
#include "VkNotify.h"

extern Settings settings;
extern AppClock appClock;
extern WebServer webServer;
extern Mp3Player mp3Player;
extern VkNotify vkBot;
extern IO io;

#endif
