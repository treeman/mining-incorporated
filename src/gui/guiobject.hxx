#pragma once

#include "input/inputhandler.hxx"

// Base class for gui things
class GuiObject : public InputHandler {
public:
    virtual ~GuiObject() { }

    virtual void select() { }
    virtual void deselect() { }

    virtual sf::FloatRect bounds() const = 0;
    bool is_over(int x, int y) const;

    virtual void set_pos(int x, int y) = 0;

    virtual bool handle_input(const sf::Event &e);

    // Will get called by handle_input
    virtual void handle_hover() { }
    virtual void handle_nonhover() { }
    virtual void handle_click(int button) { }
    virtual void handle_release(int button) { }

    virtual void update(const sf::Time &dt) { }
    virtual void draw(sf::RenderWindow &w) = 0;
};

