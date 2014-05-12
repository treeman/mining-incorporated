#pragma once

#include "gui/button.hxx"

namespace Gui {

    class PicButton : public Button {
    public:
        PicButton(function<void()> f, string s);

        void set_pos(int x, int y) override;
        void draw(sf::RenderWindow &w) override;
    protected:
        // TODO sprite
        sf::ConvexShape back;
    };

}

