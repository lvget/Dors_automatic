#include "globals.h"

Settings settings = Settings{};
AppClock appClock = AppClock(5*60*60, "pool.ntp.org", 3600);
WebServer webServer = WebServer{};
Mp3Player mp3Player = Mp3Player{};
IO io = IO{};

std::string appVersion = "v1.2";
