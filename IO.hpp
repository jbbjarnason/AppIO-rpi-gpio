#pragma once

#include <AppIO/Publisher.hpp>
#include <AppIO/Subscriber.hpp>
#include <AppIO/MessageCourier.hpp>
#include <pigpio.h>

class IO {
public:
    IO(uint pinOnBoard);

private:
    void setAsInput();
    void setAsOutput();

    /* Need a static callback to link with C. */
    static void staticOnChange(int gpio, int level, uint32_t tick, void *user);
    void onChange(int gpio, int level, uint32_t tick);

    uint _pinNr;
    std::unique_ptr<AppIO::MessageCourier<bool>> _courier;
};
