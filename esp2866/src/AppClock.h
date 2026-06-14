#ifndef CLOCK_H
#define CLOCK_H

#include <Arduino.h>
#include <time.h>
#include "config.h"

class AppClock {
public:
    /**
     * Конструктор.
     * @param tzOffset Смещение от UTC в секундах (например, 10800 для UTC+3)
     * @param ntpServer Адрес NTP-сервера (по умолчанию "pool.ntp.org")
     * @param syncIntervalSec Интервал пересинхронизации времени в секундах (по умолчанию 3600)
     */
    AppClock (long tzOffset, const char* ntpServer = APP_CLOCK_NTP_SERVER, unsigned long syncIntervalSec = APP_CLOCK_SYNC_INTERVAL_SEC);

    /**
     * Инициализация: настраивает NTP и запускает синхронизацию.
     * Должен быть вызван в setup().
     */
    void begin();

    /**
     * Периодически вызывать в loop() для автоматического контроля синхронизации.
     * Обновляет статус и при необходимости перезапускает синхронизацию.
     */
    void update();

    /**
     * Возвращает true, если время успешно синхронизировано.
     */
    bool isSynced() const;

    /**
     * Возвращает отформатированную строку времени "ЧЧ:ММ:СС".
     * Если время не синхронизировано, возвращает "00:00:00".
     */
    String getFormattedTime();

    /**
     * Дополнительно: получить отдельные компоненты времени.
     * Возвращают -1, если время не синхронизировано.
     */
    int getHour() const;
    int getMinute() const;
    int getSecond() const;

private:
    long _tzOffset;                // смещение часового пояса (сек)
    const char* _ntpServer;       // адрес NTP сервера
    unsigned long _syncInterval;  // интервал пересинхронизации (сек)
    bool _synced;                 // флаг синхронизации
    unsigned long _lastSyncTime;  // метка последней синхронизации (millis)

    // Вспомогательный метод: проверяет, получено ли время от NTP
    bool checkSync();
    // Принудительно перезапускает синхронизацию
    void restartSync();
};

#endif // CLOCK_H
