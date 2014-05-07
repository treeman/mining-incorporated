#include "buttonlist.hxx"
#include "constants.hxx"

ButtonList::ButtonList(int _x, int _y) : x(_x), y(_y) {

}

void ButtonList::add(shared_ptr<Button> b) {
    if (buttons.empty()) {
        b->set_pos(x, y);
    }
    else {
        auto last_bound = buttons.back()->bounds();
        // TODO this doesn't do anything!
        //int next_x = last_bound.left + last_bound.width + 2 * button_pad + button_space;
        int next_x = 0;
        b->set_pos(next_x, y);
    }
    buttons.push_back(b);
}

void ButtonList::deselect() {
    for (auto b : buttons)
        b->deselect();
}

void ButtonList::set_pos(int x, int y) {
    printf("nope\n");
}

sf::FloatRect ButtonList::bounds() const { return sf::FloatRect(0, 0, 1, 1); }
/*
void ButtonList::check_hover(sf::Vector2i pos) {
    //for (auto b : buttons) b->check_hover(pos);
}
void ButtonList::check_click(sf::Vector2i pos) {
    ButtonPtr click;
    for (auto b : buttons) {
        //if (b->check_click(pos)) {
            //click = b;
            //break;
        //}
    }
    if (click) {
        click->select();
        for (auto b : buttons) {
            if (b != click) b->deselect();
        }
    }
}
*/
// TODO nope nope nope
/*
bool ButtonList::is_over(int x, int y) {
    for (auto b : buttons)
        if (b->is_over(x, y)) return true;
    return false;
}
*/
void ButtonList::handle_hover() {
    for (auto b : buttons)
        b->handle_hover();
}
void ButtonList::handle_nonhover() {
    for (auto b : buttons)
        b->handle_nonhover();
}
void ButtonList::handle_click(int button) {
    for (auto b : buttons)
        b->handle_nonhover();
}
void ButtonList::handle_release(int button) {

}

void ButtonList::update(const sf::Time &dt) {
    for (auto b : buttons) b->update(dt);
}
void ButtonList::draw(sf::RenderWindow &w) {
    for (auto b : buttons) b->draw(w);
}

