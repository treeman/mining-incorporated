#include "butler.hxx"
#include "gui/picbutton.hxx"
#include "util/ext.hxx"

namespace Gui {

PicButton::PicButton(function<void(BaseButton&)> f, string s) : BaseButton(f) {
    bound.left = bound.top = 0;
    bound.width = 50;
    bound.height = 50;
    back = make_rect(bound);

    txt = create_txt("consola.ttf", 12);
    txt.setString(s);
}

sf::FloatRect PicButton::bounds() const {
    return bound;
}

void PicButton::set_pos(const WindowPos &p) {
    bound.left = p.x;
    bound.top = p.y;
    back.setPosition(p);
    txt.setPosition(p);
}

void PicButton::draw(sf::RenderWindow &w) {
    back.setFillColor(sf::Color::White);
    txt.setColor(sf::Color::Red);
    w.draw(back);
    w.draw(txt);
}

}

