#ifndef IO_PIN_HPP
#define IO_PIN_HPP

extern "C" {
#include "esp_common.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
}

#include "config.h"

enum PinLevel : uint8 {
    PinOn = 0,
    PinOff = 1,
};

enum PinMode : uint8 {
    ModeOn = PinOn,
    ModeOff = PinOff,
    ModeAuto = 2,
};

enum PinChange : uint8 {
    ChangeDown = 0,
    ChangeUp = 1,
    ChangeNone = 2,
};

uint32 msToTicks(uint32 ms);

class InputPin {
public:
    InputPin(uint8 pin, const char *name);

    void init();
    void read();
    void setMode(PinMode mode);

    bool isOn() const;
    bool isChanged() const;
    uint8 value() const;
    uint8 pin() const;
    const char *name() const;

private:
    uint8 pin_;
    const char *name_;
    PinMode mode_ = ModeAuto;
    uint8 value_ = PinOff;
    uint8 lastRawValue_ = PinOff;
    PinChange change_ = ChangeNone;
    uint32 lastDebounceTick_ = 0;
};

class OutputPin {
public:
    OutputPin(uint8 pin, const char *name);

    void init();
    void write(uint8 value);
    void setMode(PinMode mode);
    void on();
    void off();

    uint8 value() const;
    const char *name() const;

private:
    uint8 pin_;
    const char *name_;
    PinMode mode_ = ModeAuto;
    uint8 value_ = PinOff;
};

class BlinkLed {
public:
    BlinkLed(uint8 pin, uint32 periodMs, uint8 initialValue = PinOff);

    void init();
    void update();

private:
    uint8 pin_;
    uint8 value_;
    uint32 periodTicks_;
    uint32 lastToggleTick_ = 0;
};

#endif
