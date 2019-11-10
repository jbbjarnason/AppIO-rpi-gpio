#include "IO.hpp"
#include <AppIO/Timer.hpp>

using namespace std;
using namespace AppIO;

IO::IO(std::string pin, int direction) : _pin(pin), _direction(Direction(direction)) {
    _pinNr = stoi(_pin.substr(_pin.find_first_of("1234567890")));
    std::cout << "Creating pin " << pin << " which is parsed to " << _pinNr << std::endl;
    switch (_direction) {
        case Direction::INPUT: {
            setAsInput();
            break;
        }
        case Direction::OUTPUT: {
            setAsOutput();
            break;
        }
        default: {
            throw "Undefined IO pin direction " + to_string(direction);
        }
    }
}


IO::~IO() {
    _courier.reset();
}

void IO::setAsInput() {
    _pinNr = stoi(_pin.substr(_pin.find_first_of("1234567890")));

    std::cout << "Creating " << _pinNr << " as an " << directionToString.at(_direction);

    gpioSetMode(_pinNr, PI_INPUT);
    gpioSetPullUpDown(_pinNr, PI_PUD_UP);
    gpioSetAlertFuncEx(_pinNr, IO::staticOnChange, this);

    _courier = make_unique<Publisher<bool>>(_pin);
}

void IO::setAsOutput() {
    gpioSetMode(_pinNr, PI_OUTPUT);

    _courier = make_unique<Subscriber<bool>>(_pin);
    _courier->setCallback([this](bool newState){
        std::cout << "received new state " << newState << std::endl;
        gpioWrite(_pinNr, newState);
    });
}

void IO::staticOnChange(int gpio, int level, uint32_t tick, void *user) {
    /*
       Need a static callback to link with C.
    */

    std::cout << "woho" << std::endl;

    IO *mySelf = (IO *) user;

    mySelf->onChange(gpio, level, tick); /* Call the instance callback. */
}

/*
 * From pigpio
 *
Parameter   Value    Meaning

GPIO        0-31     The GPIO which has changed state

level       0-2      0 = change to low (a falling edge)
                     1 = change to high (a rising edge)
                     2 = no level change (a watchdog timeout)

tick        32 bit   The number of microseconds since boot
                     WARNING: this wraps around from
                     4294967295 to 0 roughly every 72 minutes
 *
 */

void IO::onChange(int gpio, int level, uint32_t tick) {
    if (gpio != _pinNr) throw "How did I get callback for " + to_string(gpio) + " in " + to_string(_pinNr) + " class";
    if (level == 2) return;
    _courier->send(level == 1);
}

