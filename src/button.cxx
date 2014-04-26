#include "button.hxx"
#include "constants.hxx"

Button::Button(function<void()> f, int x, int y, string s) : on_click(f) {
    printf("at %d %d\n", x, y);
    txt.setPosition(x, y);
    txt.setString(s);
    auto txt_box = txt.getLocalBounds();
    bound.left = x + txt_box.left - button_pad;
    bound.top = x + txt_box.top + button_pad;
    bound.width = x + txt_box.width + 2 * button_pad;
    bound.height = x + txt_box.height + 2 * button_pad;
}

void Button::check_click(sf::Vector2i pos) {
    printf("? %d %d\n", pos.x, pos.y);
    printf("- %f %f %f %f\n", bound.left, bound.top, bound.left + bound.width, bound.top + bound.height);
    if (bound.contains(sf::Vector2f(pos)))
        on_click();
    on_click();
}
void Button::update(const sf::Time &dt) {

}
void Button::draw(sf::RenderWindow &w) {
    w.draw(txt);
}

