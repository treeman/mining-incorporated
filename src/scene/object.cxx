#include "butler.hxx"
#include "scene/object.hxx"

namespace scene {

Object::Object(const ObjectType *_type, World *_world) : world(_world), type(_type),
    pos(-1, -1, -1)
{
    spr = create_sprite(type->spr);
}

string Object::to_string() const {
    return "Object of type " + type->to_string();
}

const ObjectType *Object::get_type() const {
    return type;
}

void Object::set_pos(const WorldPos &p) {
    pos = p;
    spr.setPosition(pos.pos);
}

void Object::draw(sf::RenderWindow &w) {
    w.draw(spr);
}

} // scene

