#pragma once

#include <SFML/Graphics.hpp>

#include "gui/event.hxx"

class World;

namespace Gui {

    class Interface;

    class State {
    public:
        State();
        virtual ~State() noexcept = default;

        void init(Interface *gui, World *world);
        virtual void reset() = 0;

        virtual void handle_event(const Gui::Event &) { }
        virtual bool handle_input(const sf::Event &e) = 0;
        virtual void update(const sf::Time &dt) = 0;
        virtual void draw(sf::RenderWindow &w) = 0;
    protected:
        Interface *gui;
        World *world;
    };

    enum class GuiState : unsigned {
        INFO,
        PLANNING,

        NUM_STATES,
    };

    string type2string(GuiState type);

    class InfoState : public State {
    public:
        void reset() override;

        bool handle_input(const sf::Event &e) override;
        void update(const sf::Time &dt) override;
        void draw(sf::RenderWindow &w) override;
    };

    class PlanningState : public State {
    public:
        void reset() override;

        void handle_event(const Gui::Event &) override;
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

