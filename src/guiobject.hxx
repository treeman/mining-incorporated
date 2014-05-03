#pragma once

#include "inputhandler.hxx"

// Base class for gui things
class GuiObject : public InputHandler {
public:
    virtual ~GuiObject() { }

    virtual void select() { }
    virtual void deselect() { }

    virtual bool is_over(sf::Vector2i pos) { return is_over(pos.x, pos.y); }
    virtual bool is_over(int x, int y) = 0;
    bool handle_input(const sf::Event &e);

    // Will get called by handle_input
    virtual void handle_hover() { }
    virtual void handle_nonhover() { }
    virtual void handle_click(int button) { }
    virtual void handle_release(int button) { }

    virtual void update(const sf::Time &dt) { }
    virtual void draw(sf::RenderWindow &w) = 0;
};

