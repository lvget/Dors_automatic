#ifndef DOOR_CONTROLLER_HPP
#define DOOR_CONTROLLER_HPP

#include "IoPin.hpp"

class DoorController {
public:
    void init();

private:
    static void ioTaskEntry(void *param);
    static void statusTaskEntry(void *param);

    void ioTask();
    void statusTask();
    void initIo();
    void handleInputs();
    void printStatus() const;

    InputPin switchLeft_{PIN_SWITCH_LEFT, IO_NAME_SWITCH_LEFT};
    InputPin switchRight_{PIN_SWITCH_RIGHT, IO_NAME_SWITCH_RIGHT};
    InputPin switchDoor_{PIN_SWITCH_DOOR, IO_NAME_SWITCH_DOOR};
    InputPin doorbellButton_{PIN_DOORBELL_BUTTON, IO_NAME_DOORBELL};

    OutputPin lampLeft_{PIN_LAMP_LEFT, IO_NAME_LAMP_LEFT};
    OutputPin lampRight_{PIN_LAMP_RIGHT, IO_NAME_LAMP_RIGHT};
    OutputPin lampIn_{PIN_LAMP_IN, IO_NAME_LAMP_IN};

    BlinkLed innerLed_{PIN_INNER_LED, INNER_LED_BLINK_MS};
};

#endif
