#include "Gpio.hpp"

bool Gpio::isGpio16(uint8 pin)
{
    return pin == 16;
}

void Gpio::initInputPullup(uint8 pin)
{
    if (isGpio16(pin)) {
        gpio16_input_conf();
        return;
    }

    GPIO_ConfigTypeDef config;
    config.GPIO_Pin = static_cast<uint16>(1 << pin);
    config.GPIO_Mode = GPIO_Mode_Input;
    config.GPIO_Pullup = GPIO_PullUp_EN;
    config.GPIO_IntrType = GPIO_PIN_INTR_DISABLE;
    gpio_config(&config);
}

void Gpio::initOutput(uint8 pin, uint8 value)
{
    if (isGpio16(pin)) {
        gpio16_output_conf();
        gpio16_output_set(value);
        return;
    }

    GPIO_ConfigTypeDef config;
    config.GPIO_Pin = static_cast<uint16>(1 << pin);
    config.GPIO_Mode = GPIO_Mode_Output;
    config.GPIO_Pullup = GPIO_PullUp_DIS;
    config.GPIO_IntrType = GPIO_PIN_INTR_DISABLE;
    gpio_config(&config);
    GPIO_OUTPUT_SET(pin, value);
}

uint8 Gpio::read(uint8 pin)
{
    if (isGpio16(pin)) {
        return gpio16_input_get() ? 1 : 0;
    }

    return GPIO_INPUT_GET(pin) ? 1 : 0;
}

void Gpio::write(uint8 pin, uint8 value)
{
    if (isGpio16(pin)) {
        gpio16_output_set(value);
        return;
    }

    GPIO_OUTPUT_SET(pin, value);
}
