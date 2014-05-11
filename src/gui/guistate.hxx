#pragma once

#include <SFML/Graphics.hpp>

class Gui;
class World;

class GuiState {
public:
    GuiState();
    virtual ~GuiState() noexcept = default;

    void init(Gui *gui, World *world);

    bool handle_input(const sf::Event &e) = 0;
    void update(const sf::Time &dt) = 0;
    void draw(sf::RenderWindow &w) = 0;
protected:
    Gui *gui;
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

