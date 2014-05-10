#pragma once

#include <SFML/Graphics.hpp>

class InputHandler {
public:
    virtual ~InputHandler() { }

    // Return true if we want allow the event to be handled futher down.
    // Return false if we want to block it.
    virtual bool handle_input(const sf::Event &) { return true; }
};

