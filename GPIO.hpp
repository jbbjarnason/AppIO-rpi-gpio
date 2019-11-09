#pragma once

#include <AppIO/AppIO.hpp>
#include <AppIO/Config.hpp>
#include <pigpio.h>
#include "IO.hpp"

class GPIO {
public:
    GPIO();
    ~GPIO();
private:
    void createDefaultConfigOnNoConfig();
    std::shared_ptr<AppIO::AppIO> _app;
    std::map<std::string, std::unique_ptr<IO>> _ios;
    std::shared_ptr<AppIO::Config> _config;

    void createIOS();
};
