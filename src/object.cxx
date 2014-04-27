#include "object.hxx"

Object::Object(ObjectType _type) : type(_type) {
    spr = create_object_sprite(type);
}

ObjectType Object::get_type() {
    return type;
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
