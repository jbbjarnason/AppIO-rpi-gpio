#pragma once

#include <AppIO/AppIO.hpp>
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
    std::shared_ptr<nlohmann::json> _config;

    void createIOS();
};
