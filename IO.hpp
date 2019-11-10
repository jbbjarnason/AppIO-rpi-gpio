#pragma once

#include <AppIO/Publisher.hpp>
#include <AppIO/Subscriber.hpp>
#include <AppIO/MessageCourier.hpp>
#include <pigpio.h>

namespace AppIO {

enum class Direction {
    OUTPUT=0,
    INPUT=1
};

const std::map<Direction, std::string> directionToString = {
    {Direction::OUTPUT, "Output"},
    {Direction::INPUT, "Input"}
};

class IO {
public:
    IO(std::string pin, int direction);
    ~IO();
private:
    void setAsInput();
    void setAsOutput();

    /* Need a static callback to link with C. */
    static void staticOnChange(int gpio, int level, uint32_t tick, void *user);
    void onChange(int gpio, int level, uint32_t tick);

    std::string _pin;
    int _pinNr;
    Direction _direction;
    std::unique_ptr<MessageCourier<bool>> _courier;
};

}
