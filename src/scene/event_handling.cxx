#include "log.hxx"
#include "scene/world.hxx"
#include "scene/material.hxx"

namespace scene {

void World::push_event(unique_ptr<Event> e) {
    assert(e != nullptr);
    if (auto c = dynamic_cast<PlacePlanningEvent*>(e.get())) {
        for (int x = c->area.start.pos.x; x <= c->area.end.pos.x; ++x) {
            for (int y = c->area.start.pos.y; y <= c->area.end.pos.y; ++y) {
                shared_ptr<Tile> tile(map->tile(MapPos(x, y, c->area.start.floor)));
                tile->set_preview(c->obj);
            }
        }
    }
    else if (auto c = dynamic_cast<RemovePlanningEvent*>(e.get())) {
        for (int x = c->area.start.pos.x; x <= c->area.end.pos.x; ++x) {
            for (int y = c->area.start.pos.y; y <= c->area.end.pos.y; ++y) {
                shared_ptr<Tile> tile(map->tile(MapPos(x, y, c->area.start.floor)));
                tile->remove_preview();
            }
        }
    }
    else if (auto c = dynamic_cast<BuildMaterialEvent*>(e.get())) {
        for (int x = c->area.start.pos.x; x <= c->area.end.pos.x; ++x) {
            for (int y = c->area.start.pos.y; y <= c->area.end.pos.y; ++y) {
                // TODO some kind of check for possibility?
                push_task(shared_ptr<Task>(new BuildGroundTask(c->material->ground,
                                MapPos(x, y, c->area.start.floor))));
            }
        }
    }
    else if (auto c = dynamic_cast<TaskDoneEvent*>(e.get())) {
        task_done(c->task);
    }
    else if (auto c = dynamic_cast<MineEvent*>(e.get())) {
        for (int x = c->area.start.pos.x; x <= c->area.end.pos.x; ++x) {
            for (int y = c->area.start.pos.y; y <= c->area.end.pos.y; ++y) {
                // TODO some kind of check for possibility?
                push_task(shared_ptr<Task>(new MineTask(MapPos(x, y, c->area.start.floor))));
            }
        }
    }
    else {
        L_("unknown command in world: %s\n", e->to_string());
    }
}

} // scene

