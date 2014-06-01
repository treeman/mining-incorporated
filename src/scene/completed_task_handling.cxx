#include "log.hxx"
#include "locator.hxx"
#include "scene/world.hxx"

namespace scene {

void World::task_done(shared_ptr<Task> task) {
    // TODO move to dynamic dispatch.
    if (auto t = dynamic_cast<BuildGroundTask*>(task.get())) {
        auto tile = get_tile(t->pos);
        assert(tile != nullptr);
        tile->set_ground(t->ground);
    }
    else if (auto t = dynamic_cast<MineTask*>(task.get())) {
        auto tile = get_tile(t->pos);
        assert(tile != nullptr);
        tile->set_ground(Locator::get_object_factory().get_ground("stone"));
    }
    else if (auto t = dynamic_cast<BuildObjectTask*>(task.get())) {
        L_("TODO object built: %s\n", t->to_string());
        L_("In completed_task_handling\n");
        L_("Maybe refactor whole thing...\n");
        //auto tile = get_tile(t->pos);
        //assert(tile != nullptr);
        //tile->set_ground(Locator::get_object_factory().get_ground("stone"));
    }
    else {
        L_("unknown task done: %s\n", task->to_string());
    }
}

} // scene

