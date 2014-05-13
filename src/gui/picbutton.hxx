#pragma once

#include "gui/button.hxx"

namespace Gui {

    class PicButton : public BaseButton {
    public:
        PicButton(function<void(BaseButton&)> f, string s);

        sf::FloatRect bounds() const override;

        void set_pos(const WindowPos &p) override;
        void draw(sf::RenderWindow &w) override;
    protected:
        // TODO sprite
        sf::ConvexShape back;
        sf::Text txt;
        sf::FloatRect bound;
    };

}

