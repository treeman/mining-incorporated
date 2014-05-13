#include "butler.hxx"
#include "gui/picbutton.hxx"
#include "util/ext.hxx"

namespace Gui {

PicButton::PicButton(function<void(BaseButton&)> f, string s) : BaseButton(f) {
    bound.left = bound.top = 0;
    bound.width = 60;
    bound.height = 60;
    back = make_rect(bound);

    txt = create_txt("consola.ttf", 11);
    txt.setString(s);
}

sf::FloatRect PicButton::bounds() const {
    return bound;
}

// Position should specify bottom left corner
void PicButton::set_pos(const WindowPos &p) {
    bound.left = p.x;
    bound.top = p.y;
    const int top_y = p.y - bound.height;
    const int txt_w = txt.getLocalBounds().width;
    const int txt_h = txt.getLocalBounds().height;
    back.setPosition(p.x, top_y);
    txt.setPosition(p.x + (bound.width - txt_w) / 2, p.y - 15);
}

void PicButton::draw(sf::RenderWindow &w) {
    back.setFillColor(sf::Color::White);
    txt.setColor(sf::Color::Red);
    w.draw(back);
    w.draw(txt);
}

}

