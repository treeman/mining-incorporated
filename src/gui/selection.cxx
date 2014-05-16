#include "locator.hxx"
#include "gui/selection.hxx"
#include "scene/world.hxx"

namespace gui {

MapSelection to_map(scene::World *world, WorldSelection sel) {
    return MapSelection(world->world2map(sel.start), world->world2map(sel.end));
}

Selection::Selection(
    scene::World *_world,
    function<void(WorldSelection)> build,
    function<void(WorldSelection)> remove
) : active(false), remove(false), world(_world), on_build(build), on_remove(remove)
{ }

WorldSelection Selection::get_area() const {
    return WorldSelection(area);
}

string Selection::to_string() const {
    if (!is_active()) return "inactive";
    return get_area().to_string();
}
void Selection::show_debug() const {
    D_.tmp("world sel: " + to_string());
    if (is_active()) {
        MapSelection sel = to_map(world, get_area());
        D_.tmp("map sel: " + sel.to_string());
    }
}

void Selection::begin(const WorldPos &start) {
    active = true;
    area.start = start;
    area.end = start;
}
void Selection::extend(const WorldPos &end) {
    area.end = end;
}
void Selection::clear() {
    active = false;
}
bool Selection::is_active() const {
    return active;
}
bool Selection::want_remove() const {
    return remove;
}
bool Selection::is_point() const {
    return is_active() && area.start == area.end;
}

bool Selection::handle_input(const sf::Event &e) {
    switch (e.type) {
        case sf::Event::MouseMoved:
            move(WindowPos(e.mouseMove.x, e.mouseMove.y));
            break;
        case sf::Event::MouseButtonPressed:
            if (e.mouseButton.button == sf::Mouse::Button::Left) {
                left_click(WindowPos(e.mouseButton.x, e.mouseButton.y));
            }
            else if (e.mouseButton.button == sf::Mouse::Button::Right) {
                right_click(WindowPos(e.mouseButton.x, e.mouseButton.y));
            }
            break;
        case sf::Event::MouseButtonReleased:
            if (e.mouseButton.button == sf::Mouse::Button::Left) {
                left_release(WindowPos(e.mouseButton.x, e.mouseButton.y));
            }
            else if (e.mouseButton.button == sf::Mouse::Button::Right) {
                right_release(WindowPos(e.mouseButton.x, e.mouseButton.y));
            }
            break;
        default: break;
    }
    return true;
}

void Selection::move(const WindowPos &p) {
    if (world->in_world(p))
        extend(world->window2world(p));
}
void Selection::left_click(const WindowPos &p) {
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Right) && world->in_world(p)) {
        begin(world->window2world(p));
        remove = false;
    }
}
void Selection::right_click(const WindowPos &p) {
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && world->in_world(p)) {
        begin(world->window2world(p));
        remove = true;
    }
}
void Selection::left_release(const WindowPos &p) {
    if (!remove) {
        // Can cancel selection by holding right and releasing
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            clear();
        }
        else if (is_active()) {
            on_build(get_area());
            clear();
        }
    }
}
void Selection::right_release(const WindowPos &p) {
    if (remove) {
        // Can cancel erase selection by holding left and releasing
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            clear();
        }
        else if (is_active()) {
            on_remove(get_area());
            clear();
        }
    }
}

} // gui

