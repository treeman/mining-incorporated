#pragma once

#include "state.hxx"
#include "world.hxx"
#include "gui.hxx"

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

    // TODO move away
    map<string, int> collected;
    //vector<Button> gui;
    //vector<Button> rooms;

    Gui gui;
};

