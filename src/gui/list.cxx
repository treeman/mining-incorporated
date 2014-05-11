#include "constants.hxx"
#include "locator.hxx"
#include "gui/list.hxx"

namespace Gui {

List::List(int _x, int _y) : x(_x), y(_y),
    space(Locator::get_settings().get_num("button_space")) // TODO make this general
{
}

void List::deselect() {
    for (auto o : objects) {
        o->deselect();
    }
}
void List::add(shared_ptr<Object> o) {
    if (objects.empty()) {
        o->set_pos(x, y);
    }
    else {
        auto last_bound = objects.back()->bounds();
        const int next_x = last_bound.left + last_bound.width + space;
        o->set_pos(next_x, y);
    }
    objects.push_back(o);
}

sf::FloatRect List::bounds() const {
    int w = 0, h = 0;
    for (auto o : objects) {
        const sf::FloatRect b = o->bounds();
        w += b.width + space;
        h = max(h, (int)b.height);
    }
    w += space;
    return sf::FloatRect(x, y, w, h);
}
bool List::handle_input(const sf::Event &e) {
    switch (e.type) {
        case sf::Event::MouseMoved:
            for (auto o : objects) {
                if (o->is_over(e.mouseMove.x, e.mouseMove.y)) {
                    o->handle_hover();
                }
                else {
                    o->handle_nonhover();
                }
            }
        case sf::Event::MouseButtonPressed:
            if (is_over(e.mouseButton.x, e.mouseButton.y))
                deselect();

            for (auto o : objects) {
                if (o->is_over(e.mouseButton.x, e.mouseButton.y)) {
                    o->handle_click(e.mouseButton.button);
                }
            }
        case sf::Event::MouseButtonReleased:
        default: break;
    }
    return true;
}

void List::update(const sf::Time &dt) {
    for (auto o : objects)
        o->update(dt);
}
void List::draw(sf::RenderWindow &w) {
    for (auto o : objects)
        o->draw(w);
}

}