#include "planningobject.hxx"
#include "butler.hxx"
#include "util/fmt.hxx"

string type2string(PlanningType type) {
    switch (type) {
        case PlanningType::ROOM: return "Room";
        case PlanningType::OBJECT: return "Object";
        default: return "Invalid";
    }
}

PlanningObject::PlanningObject(string path, PlanningType t) : type(t) {
    spr = create_sprite(path);
}

string PlanningObject::to_string() const {
    return type2string(type);
}
PlanningType PlanningObject::get_type() const {
    return type;
}

void PlanningObject::set_pos(int x, int y) {
    spr.setPosition(x, y);
}
void PlanningObject::draw(sf::RenderWindow &w) {
    w.draw(spr);
}

