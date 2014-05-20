#include "scene/event.hxx"
#include "scene/planningobject.hxx"
#include "scene/material.hxx"
#include "scene/task.hxx"

namespace scene {

PlacePlanningEvent::PlacePlanningEvent(shared_ptr<PlanningObject> o, gui::MapSelection sel) :
    obj(o), area(sel)
{ }

string PlacePlanningEvent::to_string() const {
    return "Planning: " + obj->to_string() + " at " + area.to_string();
}

RemovePlanningEvent::RemovePlanningEvent(gui::MapSelection sel) : area(sel){ }

string RemovePlanningEvent::to_string() const {
    return "Remove planning: " + area.to_string();
}

BuildMaterialEvent::BuildMaterialEvent(shared_ptr<Material> o, gui::MapSelection sel) :
    material(o), area(sel)
{ }

string BuildMaterialEvent::to_string() const {
    return "Build " + material->to_string() + " at " + area.to_string();
}

TaskDoneEvent::TaskDoneEvent(shared_ptr<Task> o) : task(o) { }

string TaskDoneEvent::to_string() const {
    return "Task done: " + task->to_string();
}

} // scene
