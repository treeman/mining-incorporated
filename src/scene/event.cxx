#include "log.hxx"
#include "scene/event.hxx"
#include "scene/planningobject.hxx"
#include "scene/material.hxx"
#include "scene/task.hxx"
#include "scene/roomtype.hxx"
#include "scene/world.hxx"

namespace scene {

PlacePlanningEvent::PlacePlanningEvent(shared_ptr<PlanningObject> o, MapArea sel) :
    obj(o), area(sel)
{ }

string PlacePlanningEvent::to_string() const {
    return "Planning: " + obj->to_string() + " at " + area.to_string();
}
void PlacePlanningEvent::handle(World *world) {
    for (MapPos p : area) {
        shared_ptr<Tile> tile(world->get_tile(p));
        tile->set_preview(obj);
    }
}

RemovePlanningEvent::RemovePlanningEvent(MapArea sel) : area(sel) { }

string RemovePlanningEvent::to_string() const {
    return "Remove planning: " + area.to_string();
}
void RemovePlanningEvent::handle(World *world) {
    for (MapPos p : area) {
        shared_ptr<Tile> tile(world->get_tile(p));
        tile->remove_preview();
    }
}

BuildMaterialEvent::BuildMaterialEvent(shared_ptr<Material> o, MapArea sel) :
    material(o), area(sel)
{ }

string BuildMaterialEvent::to_string() const {
    return "Build " + material->to_string() + " at " + area.to_string();
}
void BuildMaterialEvent::handle(World *world) {
    for (MapPos p : area) {
        if (world->can_build(p, material)) {
            world->push_task(shared_ptr<Task>(new BuildGroundTask(material->ground, p)));
        }
    }
}

BuildRoomEvent::BuildRoomEvent(shared_ptr<RoomType> o, MapArea sel) :
    type(o), area(sel)
{ }

string BuildRoomEvent::to_string() const {
    return "Place " + type->to_string() + " at " + area.to_string();
}
void BuildRoomEvent::handle(World *world) {
    world->mark_room(type, area);
}

RemoveRoomEvent::RemoveRoomEvent(MapArea _area) : area(_area)
{ }

string RemoveRoomEvent::to_string() const {
    return "Remove rooms at " + area.to_string();
}
void RemoveRoomEvent::handle(World *world) {
    world->remove_room(area);
}

TaskDoneEvent::TaskDoneEvent(shared_ptr<Task> o) : task(o) { }

string TaskDoneEvent::to_string() const {
    return "Task done: " + task->to_string();
}
void TaskDoneEvent::handle(World *world) {
    world->task_done(task);
}

MineEvent::MineEvent(MapArea sel) : area(sel) { }

string MineEvent::to_string() const {
    return "Mine " + area.to_string();
}
void MineEvent::handle(World *world) {
    for (MapPos p : area) {
        if (world->can_mine(p)) {
            world->push_task(shared_ptr<Task>(new MineTask(p)));
        }
    }
}

} // scene

