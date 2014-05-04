#include "guilist.hxx"
#include "constants.hxx"

GuiList::GuiList(int _x, int _y) : x(_x), y(_y), space(button_space) {

}

void GuiList::add(shared_ptr<GuiObject> o) {
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

sf::FloatRect GuiList::bounds() const {
    int w = 0, h = 0;
    for (auto o : objects) {
        const sf::FloatRect b = o->bounds();
        w += b.width + space;
        h = max(h, (int)b.height);
    }
    w += space;
    return sf::FloatRect(x, y, w, h);
}
bool GuiList::handle_input(const sf::Event &e) {
    switch (e.type) {
        case sf::Event::MouseMoved:
            for (auto o : objects) {
                if (o->is_over(e.mouseMove.x, e.mouseMove.y)) {
                    if (!o->handle_input(e)) return false;
                }
                else {
                }
            }
        case sf::Event::MouseButtonPressed:
        case sf::Event::MouseButtonReleased:
            for (auto o : objects) {
                if (o->is_over(e.mouseButton.x, e.mouseButton.y))
                    if (!o->handle_input(e)) return false;
            }
        default: break;
    }
    return true;
}

void GuiList::update(const sf::Time &dt) {
    for (auto o : objects)
        o->update(dt);
}
void GuiList::draw(sf::RenderWindow &w) {
    for (auto o : objects)
        o->draw(w);
}

