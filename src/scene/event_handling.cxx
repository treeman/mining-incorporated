#include "log.hxx"
#include "scene/world.hxx"
#include "scene/material.hxx"

namespace scene {

void World::push_event(unique_ptr<Event> e) {
    assert(e != nullptr);
    if (auto c = dynamic_cast<PlacePlanningEvent*>(e.get())) {
        for (MapPos p : c->area) {
            shared_ptr<Tile> tile(map->tile(p));
            tile->set_preview(c->obj);
        }
    }
    else if (auto c = dynamic_cast<RemovePlanningEvent*>(e.get())) {
        for (MapPos p : c->area) {
            shared_ptr<Tile> tile(map->tile(p));
            tile->remove_preview();
        }
    }
    else if (auto c = dynamic_cast<BuildMaterialEvent*>(e.get())) {
        for (MapPos p : c->area) {
            if (can_build(p, c->material)) {
                push_task(shared_ptr<Task>(new BuildGroundTask(c->material->ground, p)));
            }
        }
    }
    else if (auto c = dynamic_cast<TaskDoneEvent*>(e.get())) {
        task_done(c->task);
    }
    else if (auto c = dynamic_cast<MineEvent*>(e.get())) {
        for (MapPos p : c->area) {
            if (can_mine(p)) {
                push_task(shared_ptr<Task>(new MineTask(p)));
            }
        }
    }
    else {
        L_("unknown command in world: %s\n", e->to_string());
    }
}

} // scene

