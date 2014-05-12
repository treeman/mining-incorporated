#include "butler.hxx"
#include "gui/picbutton.hxx"
#include "util/ext.hxx"

namespace Gui {

PicButton::PicButton(function<void()> f, string s) : Button(f, s) {
    bound.left = bound.top = 0;
    bound.width = 50;
    bound.height = 50;
    back = make_rect(bound);

    txt = create_txt("consola.ttf", 12);
    txt.setString(s);
    selected = hover = false;
}

void PicButton::set_pos(int x, int y) {
    bound.left = x;
    bound.top = y;
    back.setPosition(x, y);
    txt.setPosition(x, y);
}

void PicButton::draw(sf::RenderWindow &w) {
    back.setFillColor(sf::Color::White);
    txt.setColor(sf::Color::Red);
    w.draw(back);
    w.draw(txt);
}

}

