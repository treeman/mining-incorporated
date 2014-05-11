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

    virtual bool handle_input(const sf::Event &e) = 0;
    virtual void update(const sf::Time &dt) = 0;
    virtual void draw(sf::RenderWindow &w) = 0;
protected:
    Interface *gui;
    World *world;
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

