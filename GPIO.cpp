#include "GPIO.hpp"
#include <AppIO/Config.hpp>

using namespace std;
using namespace AppIO;

GPIO::GPIO() :
        _app(AppIO::AppIO::instance()),
        _ios(),
        _config(Config::get()) {
    createDefaultConfigOnNoConfig();
    if ( gpioInitialise() < 0 ) throw "Unable to initialize gpio";
    createIOS();

    gpioSetSignalFuncEx(SIGINT, GPIO::staticOnTerminate, this);
    gpioSetSignalFuncEx(SIGTERM, GPIO::staticOnTerminate, this);
}

GPIO::~GPIO() {
    std::cout << "AppIO is now destructing GPIO" << std::endl;
    gpioTerminate();
    _config.reset();
    _app.reset();
    for (auto& [key, io] : _ios) {
        io.reset();
    }
}

void GPIO::createDefaultConfigOnNoConfig() {
    int defaultDirection = int(Direction::INPUT);
    if (_config->find("ios") == _config->end()) {
        (*_config)["ios"] = {
                //  BCM   direction
                {"GPIO4",  defaultDirection},
                {"GPIO17", defaultDirection},
                {"GPIO27", defaultDirection},
                {"GPIO22", defaultDirection},
                {"GPIO23", defaultDirection},
                {"GPIO24", defaultDirection},
                {"GPIO25", defaultDirection},
                {"GPIO5",  defaultDirection},
                {"GPIO6",  defaultDirection},
                {"GPIO12", defaultDirection},
                {"GPIO13", defaultDirection},
                {"GPIO19", defaultDirection},
                {"GPIO16", defaultDirection},
                {"GPIO26", defaultDirection},
                {"GPIO20", defaultDirection},
                {"GPIO21", defaultDirection},
        };
        _config->update();
    }

}

void GPIO::createIOS() {
    std::cout << "io dump " << (*_config)["ios"].dump() << std::endl;
    for (auto&[key, value] : (*_config)["ios"].items()) {
        std::cout << "creating io "<< key << " with direction " << int(value) << std::endl;
        try {
            _ios[key] = make_unique<IO>(key, value);
        }
        catch (const std::exception& exception) {
            std::cout << "Got throw from IO" << exception.what() << std::endl;
        }

    }
}

void GPIO::staticOnTerminate(int signal, void *user) {
    GPIO *mySelf = (GPIO *) user;

    mySelf->onTerminate(signal); /* Call the instance callback. */
}

void GPIO::onTerminate(int signal) {
    std::cout << "Received terminate from pigpio signal: " << signal << std::endl;
    _app->getContext()->stop();
}
