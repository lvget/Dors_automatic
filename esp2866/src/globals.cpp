#include "globals.h"

Settings settings = Settings{};
AppClock appClock = AppClock(5*60*60, "pool.ntp.org", 3600);
WebServer webServer = WebServer{};

std::string appVersion = "v1.2";