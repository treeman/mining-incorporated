#pragma once

#include <SFML/Graphics.hpp>

class World;

namespace Gui {

    class Interface;

    class State {
    public:
        State();
        virtual ~State() noexcept = default;

        void init(Interface *gui, World *world);
        virtual void reset() = 0;

        virtual bool handle_input(const sf::Event &e) = 0;
        virtual void update(const sf::Time &dt) = 0;
        virtual void draw(sf::RenderWindow &w) = 0;
    protected:
        Interface *gui;
        World *world;
    };

    enum class GuiStates : unsigned {
        INFO,

        NUM_STATES,
    };

    class InfoState : public State {
    public:
        void reset() override;

        bool handle_input(const sf::Event &e) override;
        void update(const sf::Time &dt) override;
        void draw(sf::RenderWindow &w) override;
    };

// States:
// Info
// Build room
// (Demolish)
// Build object -or- room selection!
// (Sell object)
// Mine (?)
// Nothing special

}

