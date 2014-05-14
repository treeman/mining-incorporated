#pragma once

#include "basicincludes.hxx"
#include "pos.hxx"
#include "gui/object.hxx"

namespace gui {

    // TODO on_click and on_release
    class BaseButton : public BoundedObject {
    public:
        BaseButton(function<void(BaseButton&)> f);
        virtual ~BaseButton() = default;

        void handle_click(int button) override;
    protected:
        function<void(BaseButton&)> on_click;
    };

    class Button : public BaseButton {
    public:
        Button(function<void(BaseButton&)> f, string s);
        virtual ~Button() = default;

        sf::FloatRect bounds() const override;
        void set_pos(const WindowPos &p) override;
        void draw(sf::RenderWindow &w) override;
    protected:
        sf::Text txt;
        sf::ConvexShape back;
        sf::FloatRect bound;
    };

    // Deselects itself when clicked on.
    class ClickButton : public Button {
    public:
        ClickButton(function<void(BaseButton&)> f, string s);

        void select() override;
    };

}

