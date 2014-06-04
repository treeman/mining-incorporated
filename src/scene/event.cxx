#include "log.hxx"
#include "scene/event.hxx"
#include "scene/planningobject.hxx"
#include "scene/material.hxx"
#include "scene/task.hxx"
#include "scene/roomtype.hxx"
#include "scene/objecttype.hxx"
#include "scene/world.hxx"

namespace scene {

HandleEvent::HandleEvent(function<void(World *world)> handle, string to_string) :
    h(handle), str(to_string)
{

}

string HandleEvent::to_string() const {
    return str;
}
void HandleEvent::handle(World *world) {
    h(world);
}

} // scene

