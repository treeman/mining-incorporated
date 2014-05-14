#pragma once

#include "pos.hxx"
#include "input/inputhandler.hxx"

namespace gui {

    // Base class for gui things
    class Object : public InputHandler {
    public:
        Object() : selected(false), mouse_over(false) { }
        virtual ~Object() = default;

        virtual bool is_over(const WindowPos &p) const = 0;

        virtual void set_pos(const WindowPos &p) = 0;

        virtual void select();
        virtual void deselect();
        virtual void toggle_selection();
        bool is_selected() const;

        virtual void set_mouse_over(bool is_over);
        virtual bool is_mouse_over() const;

        virtual void handle_click(int button);
        virtual void handle_release(int button);

        virtual void update(const sf::Time &dt);
        virtual void draw(sf::RenderWindow &w) = 0;
    protected:
        bool selected;
        bool mouse_over;
    };

    class BoundedObject : public Object {
    public:
        virtual sf::FloatRect bounds() const = 0;
        bool is_over(const WindowPos &p) const override;
    };

}
