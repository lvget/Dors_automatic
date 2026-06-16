#ifndef GLOBALS_H
#define GLOBALS_H

#include "WiFi.h"
#include "AppClock.h"
#include "Settings.h"
#include "WebServer.h"
#include <LittleFS.h>
#include "IO.h"
#include "Mp3Player.h"
#include "VkBot.h"
#include "NonBlockingHTTPClient.h"

extern Settings settings;
extern AppClock appClock;
extern WebServer webServer;
extern Mp3Player mp3Player;
extern VkBot vkBot;
extern IO io;
extern NonBlockingHTTPClient httpClient;

#endif
