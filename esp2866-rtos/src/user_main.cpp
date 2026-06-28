#include <stdio.h>
#include "esp_common.h"
#include "uart.h"
// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"
// #include "freertos/queue.h"
// #include "gpio.h"
#include "wifi.h"
#include "DoorController.hpp"
#include "config.h"

static DoorController controller;

extern "C" uint32 user_rf_cal_sector_set(void)
{
    const flash_size_map sizeMap = system_get_flash_size_map();

    switch (sizeMap) {
    case FLASH_SIZE_4M_MAP_256_256:
        return 128 - 5;
    case FLASH_SIZE_8M_MAP_512_512:
        return 256 - 5;
    case FLASH_SIZE_16M_MAP_512_512:
    case FLASH_SIZE_16M_MAP_1024_1024:
        return 512 - 5;
    case FLASH_SIZE_32M_MAP_512_512:
    case FLASH_SIZE_32M_MAP_1024_1024:
        return 1024 - 5;
    case FLASH_SIZE_64M_MAP_1024_1024:
        return 2048 - 5;
    case FLASH_SIZE_128M_MAP_1024_1024:
        return 4096 - 5;
    default:
        return 0;
    }
}


extern "C" void user_init(void)
{
    UART_SetBaudrate(UART0, UART_BAUD_RATE);
    //printf("\nDors automatic %s, ESP8266 RTOS SDK %s\n", APP_VERSION, system_get_sdk_version());

    WiFi_init();
    controller.init();

}
