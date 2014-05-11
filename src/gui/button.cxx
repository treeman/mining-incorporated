#include "butler.hxx"
#include "constants.hxx"
#include "locator.hxx"
#include "util/ext.hxx"
#include "gui/button.hxx"

namespace Gui {

Button::Button(function<void()> f, string s) : on_click(f) {
    txt = create_txt("consola.ttf", 14);
    txt.setString(s);
    selected = false;
    hover = false;
}

void Button::set_pos(int x, int y) {
    txt.setPosition(x, y);

    auto txt_box = txt.getGlobalBounds();

    const int button_pad = (int)Locator::get_settings().get_num("button_pad");
    bound.left = txt_box.left - button_pad;
    bound.top = txt_box.top - button_pad;
    bound.width = txt_box.width + 2 * button_pad;
    bound.height = txt_box.height + 2 * button_pad;

    back = make_rect(bound);
    /*back.setPointCount(4);
    back.setPoint(0, sf::Vector2f(bound.left, bound.top));
    back.setPoint(1, sf::Vector2f(bound.left, bound.top + bound.height));
    back.setPoint(2, sf::Vector2f(bound.left + bound.width, bound.top + bound.height));
    back.setPoint(3, sf::Vector2f(bound.left + bound.width, bound.top));*/
}

void Button::select() {
    selected = true;
}
void Button::deselect() {
    selected = false;
}

/*
void Button::check_hover(sf::Vector2i pos) {
    hover = bound.contains(sf::Vector2f(pos));
}
bool Button::check_click(sf::Vector2i pos) {
    if (bound.contains(sf::Vector2f(pos))) {
        on_click();
        return true;
    }
    return false;
}
*/
void Button::handle_hover() { hover = true; }
void Button::handle_nonhover() { hover = false; }
void Button::handle_click(int button) {
    selected = true;
    on_click();
}

void Button::update(const sf::Time &dt) {

}
void Button::draw(sf::RenderWindow &w) {
    if (selected) {
        txt.setColor(make_color(0x303030));
        back.setFillColor(make_color(0xD4D4D4));
    }
    else if (hover) {
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

ClickButton::ClickButton(function<void()> f, string s) : Button(f, s) {

}
// Cannot be selected :)
void ClickButton::select() { selected = false; }

}

