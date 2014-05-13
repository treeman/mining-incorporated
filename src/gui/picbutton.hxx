#pragma once

#include "gui/button.hxx"

namespace Gui {

    // TODO sprite based
    class PicButton : public BaseButton {
    public:
        PicButton(function<void(BaseButton&)> f, string s);

        sf::FloatRect bounds() const override;

        void set_pos(const WindowPos &p) override;
        void draw(sf::RenderWindow &w) override;
    protected:
        sf::ConvexShape back;
        sf::Text txt;
        sf::FloatRect bound;
    };

}

