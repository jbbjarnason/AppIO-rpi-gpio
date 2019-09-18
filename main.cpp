#include <AppIO/AppIO.hpp>
#include "GPIO.hpp"

int main(int argc, char **argv) {
    auto app = AppIO::AppIO::instance();
    app->initialize(argc, argv);
    auto rpi_gpio = GPIO();
    app->run();
//    std::cout << "Hello, World!" << std::endl;
    return 0;
}