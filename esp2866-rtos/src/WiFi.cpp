#include <stdio.h>
#include <string.h>
#include "esp_common.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_wifi.h"
#include "esp_sta.h"
#include "WiFi.h"
#include "config.h"

void wifi_monitor_task(void *pvParameters) {
    printf("Настройка Wi-Fi в режиме STA...\n");
    
    wifi_set_opmode(STATION_MODE); // Установка режима Станции

    struct station_config config;
    memset(&config, 0, sizeof(config));
    memcpy(config.ssid, WIFI_SSID, strlen(WIFI_SSID));
    memcpy(config.password, WIFI_PASS, strlen(WIFI_PASS));
    
    wifi_station_set_config(&config); // Запись конфига
    wifi_station_connect();           // Подключение

    while (1) {
        uint8 status = wifi_station_get_connect_status(); // Проверка статуса
        
        if (status == STATION_GOT_IP) {
            struct ip_info ip_config;
            wifi_get_ip_info(STATION_IF, &ip_config); // Получение IP адреса
            printf("Успешно подключено! IP: %s\n", ipaddr_ntoa(&ip_config.ip));
        } else {
            printf("Ожидание подключения к Wi-Fi... Статус: %d\n", status);
        }
        
        // В старом SDK макрос pdMS_TO_TICKS не работает
        vTaskDelay(3000 / portTICK_RATE_MS); 
    }
}

void WiFi_init(){
  xTaskCreate(wifi_monitor_task, (const signed char *)"wifi_task", 512, NULL, 2, NULL);
}