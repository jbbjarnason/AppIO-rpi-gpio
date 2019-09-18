#include "GPIO.hpp"

using namespace std;

GPIO::GPIO() :
        _app(AppIO::AppIO::instance()),
        _ios(),
        _config(_app->getConfig()) {
    createDefaultConfigOnNoConfig();
    if ( gpioInitialise() < 0 ) throw "Unable to initialize gpio";
    createIOS();

}

GPIO::~GPIO() {
    gpioTerminate();
}

void GPIO::createDefaultConfigOnNoConfig() {
    if (_config->find("ios") == _config->end()) {
        (*_config)["ios"] = {
            //  BCM         BOARD
                {"GPIO4",   7},
                {"GPIO17",  11},
                {"GPIO27",  13},
                {"GPIO22",  15},
                {"GPIO23",  16},
                {"GPIO24",  18},
                {"GPIO25",  22},
                {"GPIO5",   29},
                {"GPIO6",   31},
                {"GPIO12",  32},
                {"GPIO13",  33},
                {"GPIO19",  35},
                {"GPIO16",  36},
                {"GPIO26",  37},
                {"GPIO20",  38},
                {"GPIO21",  40},
        };
        _app->updateConfigFile();
    }

}

void GPIO::createIOS() {
    for (auto& [key, value] : (*_config)["ios"].items())
        _ios[key] = make_unique<IO>(value);
}
