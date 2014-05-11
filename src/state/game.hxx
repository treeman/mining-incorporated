#pragma once

#include "state/state.hxx"
#include "world/world.hxx"
#include "gui/interface.hxx"

class GameState : public State {
public:
    GameState(sf::RenderWindow &w);

    string id() const { return "game"; }

    void handle_input(const sf::Event &e);
    void update(const sf::Time &dt);
    void draw();
private:
    sf::Text txt;
    World world;

    Gui::Interface gui;
};

