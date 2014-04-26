#pragma once

#include "state.hxx"

class GameState : public State {
public:
    GameState(sf::RenderWindow &w) : State(w) { }

    string id() const { return "game"; }
};

