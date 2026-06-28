#include "IoPin.hpp"

#include <stdio.h>

#include "Gpio.hpp"

uint32 msToTicks(uint32 ms)
{
    uint32 ticks = ms / portTICK_RATE_MS;
    return ticks == 0 ? 1 : ticks;
}

InputPin::InputPin(uint8 pin, const char *name)
    : pin_(pin), name_(name)
{
}

void InputPin::init()
{
    Gpio::initInputPullup(pin_);
    value_ = Gpio::read(pin_);
    lastRawValue_ = value_;
    lastDebounceTick_ = xTaskGetTickCount();
    change_ = ChangeNone;
}

void InputPin::read()
{
    const uint8 rawValue = Gpio::read(pin_);
    const uint32 now = xTaskGetTickCount();

    if (rawValue != lastRawValue_) {
        lastRawValue_ = rawValue;
        lastDebounceTick_ = now;
    }

    if ((now - lastDebounceTick_) >= msToTicks(INPUT_DEBOUNCE_DELAY_MS) &&
        lastRawValue_ != value_) {
        value_ = lastRawValue_;
        change_ = value_ == PinOn ? ChangeUp : ChangeDown;
        printf("%s GPIO%u = %u\n", name_, pin_, value_);
    } else {
        change_ = ChangeNone;
    }
}

void InputPin::setMode(PinMode mode)
{
    if (mode != ModeAuto) {
        change_ = value_ == PinOn ? ChangeUp : ChangeDown;
    }

    mode_ = mode;
}

bool InputPin::isOn() const
{
    return mode_ == ModeAuto ? value_ == PinOn : mode_ == ModeOn;
}

bool InputPin::isChanged() const
{
    return mode_ == ModeAuto && change_ != ChangeNone;
}

uint8 InputPin::value() const
{
    return value_;
}

uint8 InputPin::pin() const
{
    return pin_;
}

const char *InputPin::name() const
{
    return name_;
}

OutputPin::OutputPin(uint8 pin, const char *name)
    : pin_(pin), name_(name)
{
}

void OutputPin::init()
{
    value_ = PinOff;
    Gpio::initOutput(pin_, value_);
}

void OutputPin::write(uint8 value)
{
    value_ = value;

    if (mode_ == ModeAuto) {
        Gpio::write(pin_, value_);
    }
}

void OutputPin::setMode(PinMode mode)
{
    mode_ = mode;
    Gpio::write(pin_, mode == ModeAuto ? value_ : mode);
}

void OutputPin::on()
{
    write(PinOn);
}

void OutputPin::off()
{
    write(PinOff);
}

uint8 OutputPin::value() const
{
    return value_;
}

const char *OutputPin::name() const
{
    return name_;
}

BlinkLed::BlinkLed(uint8 pin, uint32 periodMs, uint8 initialValue)
    : pin_(pin), value_(initialValue), periodTicks_(msToTicks(periodMs))
{
}

void BlinkLed::init()
{
    Gpio::initOutput(pin_, value_);
    lastToggleTick_ = xTaskGetTickCount();
}

void BlinkLed::update()
{
    const uint32 now = xTaskGetTickCount();

    if (periodTicks_ == 0) {
        return;
    }

    if ((now - lastToggleTick_) >= periodTicks_) {
        lastToggleTick_ = now;
        value_ = value_ ? 0 : 1;
        Gpio::write(pin_, value_);
    }
}
