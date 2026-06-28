#include "DoorController.hpp"

#include <stdio.h>

void DoorController::init()
{
    xTaskCreate(ioTaskEntry, (const signed char *)"io_task", 512, this, 4, NULL);
    xTaskCreate(statusTaskEntry, (const signed char *)"status_task", 512, this, 2, NULL);
}

void DoorController::ioTaskEntry(void *param)
{
    static_cast<DoorController *>(param)->ioTask();
}

void DoorController::statusTaskEntry(void *param)
{
    static_cast<DoorController *>(param)->statusTask();
}

void DoorController::ioTask()
{
    const uint32 delayTicks = msToTicks(IO_POLL_INTERVAL_MS);

    initIo();
    printf("IO task started\n");

    while (true) {
        handleInputs();
        innerLed_.update();
        vTaskDelay(delayTicks);
    }
}

void DoorController::statusTask()
{
    const uint32 delayTicks = msToTicks(STATUS_LOG_INTERVAL_MS);

    while (true) {
        printStatus();
        vTaskDelay(delayTicks);
    }
}

void DoorController::initIo()
{
    switchLeft_.init();
    switchRight_.init();
    switchDoor_.init();
    doorbellButton_.init();

    lampLeft_.init();
    lampRight_.init();
    lampIn_.init();

    lampLeft_.setMode(ModeAuto);
    lampRight_.setMode(ModeAuto);
    lampIn_.setMode(ModeAuto);

    innerLed_.init();
}

void DoorController::handleInputs()
{
    switchLeft_.read();
    switchRight_.read();
    switchDoor_.read();
    doorbellButton_.read();

    if (doorbellButton_.isChanged() && doorbellButton_.isOn()) {
        printf("Doorbell pressed; MP3/VK handlers are not ported from Arduino yet\n");
    }

    if (switchLeft_.isChanged() || switchRight_.isChanged() || switchDoor_.isChanged()) {
        switchLeft_.isOn() ? lampLeft_.on() : lampLeft_.off();
        switchRight_.isOn() ? lampRight_.on() : lampRight_.off();
        switchDoor_.isOn() ? lampIn_.on() : lampIn_.off();
    }
}

void DoorController::printStatus() const
{
    printf("values:{\"%s\":%u,\"%s\":%u,\"%s\":%u,\"%s\":%u,\"%s\":%u,\"%s\":%u,\"%s\":%u}\n",
           lampLeft_.name(), lampLeft_.value(),
           lampRight_.name(), lampRight_.value(),
           lampIn_.name(), lampIn_.value(),
           switchRight_.name(), switchRight_.value(),
           switchLeft_.name(), switchLeft_.value(),
           switchDoor_.name(), switchDoor_.value(),
           doorbellButton_.name(), doorbellButton_.value());
}
