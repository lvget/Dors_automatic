#ifndef APP_CONFIG_H
#define APP_CONFIG_H

#define APP_VERSION "v1.2-rtos"

#define WIFI_SSID "kofein_wifi"
#define WIFI_PASS "K0255E1N"

#define OTA_USER "admin"
#define OTA_PASSWORD "admin"
#define WEB_SERVER_PORT 80

#define APP_CLOCK_TZ_OFFSET (5 * 60 * 60)
#define APP_CLOCK_NTP_SERVER "pool.ntp.org"
#define APP_CLOCK_SYNC_INTERVAL_SEC 3600

#define UART_BAUD_RATE 115200

#define INPUT_DEBOUNCE_DELAY_MS 1000 //50
#define IO_POLL_INTERVAL_MS 10
#define STATUS_LOG_INTERVAL_MS 5000
#define INNER_LED_BLINK_MS 1000

/* NodeMCU pin map from the Arduino project. */
#define PIN_SWITCH_LEFT 5      /* D1 */
#define PIN_SWITCH_RIGHT 4     /* D2 */
#define PIN_SWITCH_DOOR 0      /* D3 */
#define PIN_DOORBELL_BUTTON 16 /* D0 */
#define PIN_LAMP_LEFT 14       /* D5 */
#define PIN_LAMP_RIGHT 12      /* D6 */
#define PIN_LAMP_IN 13         /* D7 */
#define PIN_INNER_LED 2        /* D4 */

#define IO_NAME_SWITCH_LEFT "SwL"
#define IO_NAME_SWITCH_RIGHT "SwR"
#define IO_NAME_SWITCH_DOOR "SwDor"
#define IO_NAME_DOORBELL "Doorbell"
#define IO_NAME_LAMP_LEFT "LampL"
#define IO_NAME_LAMP_RIGHT "LampR"
#define IO_NAME_LAMP_IN "LampIn"

#endif
