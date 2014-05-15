#include "scene/command.hxx"

namespace scene {

PlacePlanningCommand::PlacePlanningCommand(shared_ptr<PlanningObject> o, gui::MapSelection sel) :
    obj(o), area(sel)
{ }

string PlacePlanningCommand::to_string() const {
    return "Planning: " + obj->to_string() + " at " + area.to_string();
}

RemovePlanningCommand::RemovePlanningCommand(gui::MapSelection sel) : area(sel){ }

string RemovePlanningCommand::to_string() const {
    return "Remove planning: " + area.to_string();
}

} // scene

