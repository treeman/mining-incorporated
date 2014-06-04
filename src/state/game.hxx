#pragma once

#include "state/state.hxx"
#include "scene/world.hxx"
#include "gui/interface.hxx"

namespace state {

    class GameState : public State {
    public:
        GameState(sf::RenderWindow &w);

        string id() const override { return "game"; }

        void handle_input(const sf::Event &e) override;
        void update(const sf::Time &dt) override;
        void draw() override;
    private:
        sf::Text txt;
        scene::World world;
        gui::Interface gui;
    public:
        scene::World &get_world() const;
    };

}

