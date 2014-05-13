#include "butler.hxx"
#include "gui/picbutton.hxx"
#include "util/ext.hxx"

namespace Gui {

PicButton::PicButton(function<void(BaseButton&)> f, string s) : BaseButton(f) {
    // TODO parameters?
    bound.left = bound.top = 0;
    bound.width = 55;
    bound.height = 40;
    set_pos(WindowPos(0, 0));

    txt = create_txt("consola.ttf", 11);
    txt.setString(s);
}

sf::FloatRect PicButton::bounds() const {
    return bound;
}

// Position should specify bottom left corner
void PicButton::set_pos(const WindowPos &p) {
    const int txt_y_off = 5;
    const int txt_w = txt.getLocalBounds().width;
    const int txt_h = txt.getLocalBounds().height;
    const int top_y = p.y - bound.height - txt_y_off;
    bound.left = p.x;
    bound.top = top_y;
    back = make_rect(bound);
    const int x = (int)p.x + (bound.width - txt_w) / 2;
    const int y = (int)p.y - txt_y_off;
    txt.setPosition(x, y);
}

void PicButton::draw(sf::RenderWindow &w) {
    back.setFillColor(make_color(0x3d3d3d));
    txt.setColor(sf::Color::White);
    w.draw(back);
    w.draw(txt);
}

}

