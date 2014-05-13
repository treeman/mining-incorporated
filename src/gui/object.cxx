#include "gui/object.hxx"

namespace Gui {

void Object::select() {
    selected = true;
}
void Object::deselect() {
    selected = false;
}
void Object::toggle_selection() {
    if (is_selected()) deselect();
    else select();
}
bool Object::is_selected() const {
    return selected;
}

void Object::set_mouse_over(bool is_over) {
    mouse_over = is_over;
}
bool Object::is_mouse_over() const {
    return mouse_over;
}

void Object::handle_click(int button) { }
void Object::handle_release(int button) { }

void Object::update(const sf::Time &dt) { }

bool BoundedObject::is_over(const WindowPos &p) const {
    return bounds().contains(p);
}

}

