#include "buttonlist.hxx"
#include "constants.hxx"

ButtonList::ButtonList(int _x, int _y) : x(_x), y(_y) {

}

void ButtonList::add(shared_ptr<Button> b) {
    if (buttons.empty()) {
        b->set_pos(x, y);
    }
    else {
        auto last_bound = buttons.back()->get_bounds();
        int next_x = last_bound.left + last_bound.width + 2 * button_pad + button_space;
        b->set_pos(next_x, y);
    }
    buttons.push_back(b);
}

void ButtonList::deselect_all() {
    for (auto b : buttons)
        b->deselect();
}

void ButtonList::check_hover(sf::Vector2i pos) {
    for (auto b : buttons) b->check_hover(pos);
}
void ButtonList::check_click(sf::Vector2i pos) {
    ButtonPtr click;
    for (auto b : buttons) {
        if (b->check_click(pos)) {
            click = b;
            break;
        }
    }
    if (click) {
        click->select();
        for (auto b : buttons) {
            if (b != click) b->deselect();
        }
    }
}
void ButtonList::update(const sf::Time &dt) {
    for (auto b : buttons) b->update(dt);
}
void ButtonList::draw(sf::RenderWindow &w) {
    for (auto b : buttons) b->draw(w);
}

