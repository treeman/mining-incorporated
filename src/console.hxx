#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "settings.hxx"
#include "historybox.hxx"
#include "inputbox.hxx"
#include "inputhandler.hxx"

class Console : public InputHandler {
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

    HistoryBox history;
    InputBox input;
    void execute_cmd();
};

