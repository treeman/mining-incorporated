#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "settings.hxx"

class Console {
public:
    Console(sf::RenderWindow &w, Settings &settings);

    void activate();
    void deactivate();

    bool handle_input(const sf::Event &e);
    void update(const sf::Time &dt);
    void draw();
private:
    void new_setting(string key, string val);
    sf::RenderWindow &window;
    Settings &settings;
    bool is_active;
};

