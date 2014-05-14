#include "locator.hxx"
#include "gui/event.hxx"

namespace gui {

PlanningObjectEvent::PlanningObjectEvent(shared_ptr<scene::PlanningObject> o) : obj(o) {
}

string PlanningObjectEvent::to_string() const {
    return obj->to_string() + " Planning";
}

} // Gui
