#include <cassert>
#include "objectfactory.hxx"

namespace scene {

ObjectFactory::ObjectFactory() {
    // TODO load from lua
    // Maybe cleanup?
    auto col = sf::Color(255, 255, 255, 100);
    planning_objects.resize(static_cast<unsigned>(PlanningType::NUM_OBJECTS));
    planning_objects[static_cast<unsigned>(PlanningType::ROOM)].reset(
        new PlanningObject("room_preview.png", PlanningType::ROOM, col));
    planning_objects[static_cast<unsigned>(PlanningType::OBJECT)].reset(
        new PlanningObject("object_preview.png", PlanningType::OBJECT, col));
}

shared_ptr<PlanningObject> ObjectFactory::create_planning_object(PlanningType o) const {
    unsigned x = static_cast<unsigned>(o);
    assert(x < planning_objects.size());
    assert(planning_objects[x] != nullptr);
    shared_ptr<PlanningObject> res(new PlanningObject(*planning_objects[x].get()));
    return move(res);
}

};

