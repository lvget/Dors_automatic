#include "globals.h"
#include "config.h"

Settings settings = Settings{};
AppClock appClock = AppClock(APP_CLOCK_TZ_OFFSET, APP_CLOCK_NTP_SERVER, APP_CLOCK_SYNC_INTERVAL_SEC);
WebServer webServer = WebServer{};
Mp3Player mp3Player = Mp3Player{};
VkNotify vkBot = VkNotify{};
IO io = IO{};

std::string appVersion = APP_VERSION;
