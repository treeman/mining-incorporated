#include "butler.hxx"
#include "constants.hxx"
#include "locator.hxx"
#include "util/ext.hxx"
#include "gui/button.hxx"

namespace gui {

BaseButton::BaseButton(function<void(BaseButton&)> f) : on_click(f)
{

}

void BaseButton::handle_click(int button) {
    if (button == sf::Mouse::Button::Left) {
        on_click(*this);
    }
}

Button::Button(function<void(BaseButton&)> f, string s) : BaseButton(f) {
    txt = create_txt("consola.ttf", 14);
    txt.setString(s);
    set_pos(WindowPos(0, 0)); // TODO ugly!
}

sf::FloatRect Button::bounds() const {
    return bound;
}
void Button::set_pos(const WindowPos &p) {
    txt.setPosition(p);

    auto txt_box = txt.getGlobalBounds();

    const int button_pad = (int)Locator::get_settings().get_num("button_pad");
    bound.left = txt_box.left - button_pad;
    bound.top = txt_box.top - button_pad;
    bound.width = txt_box.width + 2 * button_pad;
    bound.height = txt_box.height + 2 * button_pad;

    back = make_rect(bound);
}

void Button::draw(sf::RenderWindow &w) {
    if (is_selected()) {
        txt.setColor(make_color(0x303030));
        back.setFillColor(make_color(0xD4D4D4));
    }
    else if (is_mouse_over()) {
        txt.setColor(sf::Color::Black);
        back.setFillColor(make_color(0xE0E0E0));
    }
    else {
        txt.setColor(sf::Color::Black);
        back.setFillColor(make_color(0xA4A4A4));
    }
    w.draw(back);
    w.draw(txt);
}

ClickButton::ClickButton(function<void(BaseButton&)> f, string s) : Button(f, s) {

}
// Cannot be selected :)
void ClickButton::select() { selected = false; }

}

