#pragma once

#include "gui/state.hxx"

namespace Gui {
    class InfoState : public State {
    public:
        bool handle_input(const sf::Event &e) override;
        void update(const sf::Time &dt) override;
        void draw(sf::RenderWindow &w) override;
    };
}

