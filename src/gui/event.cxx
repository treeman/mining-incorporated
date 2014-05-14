#include "locator.hxx"
#include "gui/event.hxx"

namespace Gui {

PlanningObjectEvent::PlanningObjectEvent(shared_ptr<PlanningObject> o) : obj(o) {
}

string PlanningObjectEvent::to_string() const {
    return obj->to_string() + " Planning";
}

} // Gui
