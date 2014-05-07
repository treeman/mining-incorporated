#pragma once

#include <SFML/Graphics.hpp>
#include "settings.hxx"
#include "butler.hxx"
#include "logger.hxx"
#include "debug.hxx"

#define L_ (Locator::get_logger())
#define D_ (Locator::get_debug())

class Locator {
public:
    static void init();

    // TODO make a butler class?
    //static Butler &get_butler();
    //static void provide_butler(unique_ptr<Butler> butler);
    static Settings &get_settings();

    static Logger &get_logger();
    static void provide_logger(unique_ptr<Logger> logger);

    static Debug &get_debug();
    static void provide_debug(unique_ptr<Debug> debug);

    static sf::RenderWindow &get_window();
    static void provide_window(sf::RenderWindow *window);
private:
    //static unique_ptr<Butler> butler;
    static unique_ptr<Settings> settings;
    static unique_ptr<Logger> logger;
    static unique_ptr<Debug> debug;
    static sf::RenderWindow *window;
};

