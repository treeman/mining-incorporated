#pragma once

#include "settings.hxx"
#include "butler.hxx"
#include "logger.hxx"

#define L_ (Locator::get_logger())

class Locator {
public:
    static void init();

    // TODO make a butler class?
    //static Butler &get_butler();
    //static void provide_butler(unique_ptr<Butler> butler);
    static Settings &get_settings();

    static Logger &get_logger();
    static void provide_logger(unique_ptr<Logger> logger);
private:
    //static unique_ptr<Butler> butler;
    static unique_ptr<Settings> settings;
    static unique_ptr<Logger> logger;
};

