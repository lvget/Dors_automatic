# Dors automatic ESP8266 RTOS port

This PlatformIO project is a FreeRTOS/ESP8266 RTOS SDK port of the Arduino
project from `D:\MyProject\Arduino\Dors_automatic\esp2866`.

Implemented:

- C++ controller and pin classes over ESP8266 RTOS SDK APIs.
- GPIO automation for the three switches and three lamps.
- Debounced inputs with the original active-low logic.
- Doorbell button detection.
- Inner LED heartbeat task.
- Periodic JSON-like status log over UART.
- Original `data` directory copied for UI and MP3 assets.

Not ported yet:

- Arduino `LittleFS`, `ESP8266WebServer`, OTA, `ESP8266Audio`, VK bot and
  non-blocking HTTP client layers. These need native RTOS SDK replacements.

## Pin Map

| Original pin | GPIO | Purpose |
| --- | ---: | --- |
| D1 | 5 | Left switch |
| D2 | 4 | Right switch |
| D3 | 0 | Door switch |
| D0 | 16 | Doorbell button |
| D5 | 14 | Left lamp |
| D6 | 12 | Right lamp |
| D7 | 13 | Inner lamp |
| D4 | 2 | Built-in LED |

Build:

```sh
pio run
```
