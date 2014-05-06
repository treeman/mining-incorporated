#pragma once

#include "settings.hxx"
#include "butler.hxx"

class Locator {
public:
    static void init();

    // TODO make a butler class?
    //static Butler &get_butler();
    //static void provide_butler(unique_ptr<Butler> butler);
    static Settings &get_settings();
private:
    //static unique_ptr<Butler> butler;
    static unique_ptr<Settings> settings;
};

