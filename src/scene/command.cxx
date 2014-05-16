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

BuildMaterialCommand::BuildMaterialCommand(shared_ptr<Material> o, gui::MapSelection sel) :
    material(o), area(sel)
{ }

string BuildMaterialCommand::to_string() const {
    return "Build " + material->to_string() + " at " + area.to_string();
}

} // scene

