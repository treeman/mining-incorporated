#include "object.hxx"

Object::Object(ObjectType type) {
    spr = create_object_sprite(type);
}

void Object::set_pos(int x, int y) {
    spr.setPosition(x, y);
}
void Object::draw(sf::RenderWindow &w) {
    w.draw(spr);
}

ObjectPtr make_object(ObjectType type) {
    return ObjectPtr(new Object(type));
}
