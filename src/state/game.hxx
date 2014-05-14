#pragma once

#include "state/state.hxx"
#include "scene/world.hxx"
#include "gui/interface.hxx"

namespace state {

    class GameState : public State {
    public:
        GameState(sf::RenderWindow &w);

        string id() const { return "game"; }

        void handle_input(const sf::Event &e);
        void update(const sf::Time &dt);
        void draw();
    private:
        sf::Text txt;
        scene::World world;
        gui::Interface gui;
    };

}

