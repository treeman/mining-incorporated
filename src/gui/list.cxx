#include "constants.hxx"
#include "locator.hxx"
#include "gui/list.hxx"

namespace gui {

List::List(int _x, int _y) : pos(_x, _y),
    space(Locator::get_settings().get_num("button_space")) // TODO make this general
{
}

void List::deselect() {
    for (auto o : objects) {
        o->deselect();
    }
}
void List::add(shared_ptr<BoundedObject> o) {
    if (objects.empty()) {
        o->set_pos(pos);
    }
    else {
        auto last_bound = objects.back()->bounds();
        const int next_x = last_bound.left + last_bound.width + space;
        o->set_pos(WindowPos(next_x, pos.y));
    }
    objects.push_back(o);
}

bool List::is_over(const WindowPos &p) const {
    for (auto &o : objects)
        if (o->is_over(p)) return true;
    return false;
}
bool List::handle_input(const sf::Event &e) {
    switch (e.type) {
        case sf::Event::MouseMoved:
            for (auto o : objects) {
                if (o->is_over(WindowPos(e.mouseMove.x, e.mouseMove.y))) {
                    o->set_mouse_over(true);
                }
                else {
                    o->set_mouse_over(false);
                }
            }
            break;
        case sf::Event::MouseButtonPressed:
            //if (o->is_mouse_over())
                //deselect();

            for (auto o : objects) {
                if (o->is_over(WindowPos(e.mouseButton.x, e.mouseButton.y))) {
                    o->handle_click(e.mouseButton.button);
                }
            }
            break;
        case sf::Event::MouseButtonReleased:
            for (auto o : objects) {
                if (o->is_over(WindowPos(e.mouseButton.x, e.mouseButton.y))) {
                    o->handle_release(e.mouseButton.button);
                }
            }
            break;
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
