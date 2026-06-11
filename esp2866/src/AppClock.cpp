#include "AppClock.h"

AppClock::AppClock(long tzOffset, const char* ntpServer, unsigned long syncIntervalSec)
    : _tzOffset(tzOffset)
    , _ntpServer(ntpServer)
    , _syncInterval(syncIntervalSec * 1000)  // переводим в миллисекунды
    , _synced(false)
    , _lastSyncTime(0)
{}

void AppClock::begin() {
    restartSync();
}

void AppClock::update() {
    // Если время ещё не синхронизировано, пытаемся получить
    if (!_synced) {
        if (checkSync()) {
            _synced = true;
            _lastSyncTime = millis();
        }
        return;
    }

    // Если синхронизировано, но прошёл интервал пересинхронизации — обновляем
    if (millis() - _lastSyncTime >= _syncInterval) {
        restartSync();
        _synced = false; // сбросим флаг до следующей проверки
    }
}

bool AppClock::isSynced() const {
    return _synced;
}

String AppClock::getFormattedTime()  {
    if (!_synced) {
        return "00:00:00";
    }

    time_t now = time(nullptr);
    struct tm* timeinfo = localtime(&now);
    char buffer[9];  // "HH:MM:SS" + null
    sprintf(buffer, "%02d:%02d:%02d", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
    return String(buffer);
}

int AppClock::getHour() const {
    if (!_synced) return -1;
    time_t now = time(nullptr);
    struct tm* timeinfo = localtime(&now);
    return timeinfo->tm_hour;
}

int AppClock::getMinute() const {
    if (!_synced) return -1;
    time_t now = time(nullptr);
    struct tm* timeinfo = localtime(&now);
    return timeinfo->tm_min;
}

int AppClock::getSecond() const {
    if (!_synced) return -1;
    time_t now = time(nullptr);
    struct tm* timeinfo = localtime(&now);
    return timeinfo->tm_sec;
}

bool AppClock::checkSync() {
    // time(nullptr) возвращает небольшое значение (обычно < 100000), если время не синхронизировано
    return time(nullptr) > 100000;
}

void AppClock::restartSync() {
    configTime(_tzOffset, 0, _ntpServer);
    // Даём системе шанс начать синхронизацию
    delay(100);
}