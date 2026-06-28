#ifndef GPIO_HPP
#define GPIO_HPP

extern "C" {
#include "esp_common.h"
#include "gpio.h"

void gpio_config(GPIO_ConfigTypeDef *config);
}

class Gpio {
public:
    static void initInputPullup(uint8 pin);
    static void initOutput(uint8 pin, uint8 value);
    static uint8 read(uint8 pin);
    static void write(uint8 pin, uint8 value);

private:
    static bool isGpio16(uint8 pin);
};

#endif
