#pragma once

#include "std.hxx"
#include "settings.hxx"
#include "gui/historybox.hxx"
#include "gui/inputbox.hxx"
#include "input/inputhandler.hxx"

class Console : public InputHandler {
public:
    Console(sf::RenderWindow &w);

    void activate();
    void deactivate();

    bool handle_input(const sf::Event &e);
    void update(const sf::Time &dt);
    void draw();
private:
    void new_setting(string key, string val);
    sf::RenderWindow &window;
    bool is_active;

    gui::HistoryBox history;
    gui::InputBox input;
    void execute_cmd();
};

