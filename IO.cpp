#include "IO.hpp"

using namespace std;

IO::IO(uint pinOnBoard): _pinNr(pinOnBoard) {
    // Todo: implement onConnected callback to describe if in or out
    setAsInput();
}

void IO::setAsInput() {
    gpioSetMode(_pinNr, PI_INPUT);
    gpioSetPullUpDown(_pinNr, PI_PUD_UP);
    gpioSetAlertFuncEx(_pinNr, IO::staticOnChange, this);

//    auto cour = make_unique<AppIO::MessageCourier<bool>>;
//
//    auto subber = make_unique<AppIO::Subscriber<bool>>("name");

//    cour.reset();
//    cour = move(subber);

}

void IO::setAsOutput() {

}

void IO::staticOnChange(int gpio, int level, uint32_t tick, void *user) {
    /*
       Need a static callback to link with C.
    */

    IO *mySelf = (IO *) user;

    mySelf->onChange(gpio, level, tick); /* Call the instance callback. */
}

void IO::onChange(int gpio, int level, uint32_t tick) {
    if (gpio != _pinNr) throw "How did I get callback for " + to_string(gpio) + " in " + to_string(_pinNr) + " class";

}
