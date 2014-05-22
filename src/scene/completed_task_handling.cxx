#include "log.hxx"
#include "scene/world.hxx"

namespace scene {

void World::task_done(shared_ptr<Task> task) {
    if (auto t = dynamic_cast<BuildGroundTask*>(task.get())) {
        auto tile = get_tile(t->pos);
        assert(tile != nullptr);
        tile->set_ground(t->ground.get());
    }
    else {
        L_("unknown task done: %s\n", task->to_string());
    }
}

} // scene

