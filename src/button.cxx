#include "button.hxx"
#include "butler.hxx"
#include "constants.hxx"

Button::Button(function<void()> f, string s) : on_click(f) {
    txt = create_txt("consola.ttf", 14);
    txt.setString(s);
    selected = false;
    hover = false;
}

void Button::set_pos(int x, int y) {
    txt.setPosition(x, y);

    auto txt_box = txt.getGlobalBounds();

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
void Button::update(const sf::Time &dt) {

}
void Button::draw(sf::RenderWindow &w) {
    if (selected) {
        txt.setColor(sf::Color::White);
        back.setFillColor(sf::Color::Blue);
    }
    else if (hover) {
        txt.setColor(sf::Color::Black);
        back.setFillColor(make_color(0xE0E0E0));
    }
    else {
        txt.setColor(sf::Color::Black);
        back.setFillColor(make_color(0x919191));
    }
    w.draw(back);
    w.draw(txt);
}

