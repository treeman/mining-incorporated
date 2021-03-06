#include "locator.hxx"
#include "util/ext.hxx"
#include "gui/selection.hxx"
#include "gui/interface.hxx"
#include "scene/world.hxx"

namespace gui {

Selection::Selection(
    scene::World *_world,
    Interface *_gui,
    function<void(scene::WorldArea)> build,
    function<void(scene::WorldArea)> remove
) : active(false), remove(false), world(_world), gui(_gui), on_build(build), on_remove(remove)
{ }

scene::WorldArea Selection::get_area() const {
    return scene::WorldArea(area);
}
WindowPos Selection::get_outside_txt_pos() const {
    auto area = get_area();
    WindowPos mpos = get_mpos();
    WindowPos top_left = world->world2window(area.first);
    WindowPos res;
    res.x = min(top_left.x, mpos.x) + 20;
    res.y = min(top_left.y, mpos.y) - 30;
    return res;
}

string Selection::to_string() const {
    if (!is_active()) return "inactive";
    return get_area().to_string();
}
void Selection::show_debug() const {
    D_.tmp("world sel: " + to_string());
    if (is_active()) {
        scene::MapArea sel = to_map(world, get_area());
        D_.tmp("map sel: " + sel.to_string());
    }
}
void Selection::begin(const WorldPos &first) {
    active = true;
    area.first = first;
    area.last = first;
}
void Selection::extend(const WorldPos &last) {
    area.last = last;
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
    return is_active() && area.first == area.last;
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
    if (world->in_world(p, gui->current_floor()))
        extend(world->window2world(p, gui->current_floor()));
}
void Selection::left_click(const WindowPos &p) {
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Right)
        && world->in_world(p, gui->current_floor()))
    {
        begin(world->window2world(p, gui->current_floor()));
        remove = false;
    }
}
void Selection::right_click(const WindowPos &p) {
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)
        && world->in_world(p, gui->current_floor()))
    {
        begin(world->window2world(p, gui->current_floor()));
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

