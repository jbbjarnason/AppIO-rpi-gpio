#pragma once

#include <AppIO/AppIO.hpp>
#include <AppIO/Config.hpp>
#include <pigpio.h>
#include "IO.hpp"

namespace AppIO {

class GPIO {
public:
    GPIO();
    ~GPIO();
private:
    static void staticOnTerminate(int signal, void *user);
    void onTerminate(int signal);

    void createDefaultConfigOnNoConfig();
    std::shared_ptr<AppIO> _app;
    std::map<std::string, std::unique_ptr<IO>> _ios;
    std::shared_ptr<Config> _config;

    void createIOS();
};

}

