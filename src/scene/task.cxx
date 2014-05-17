#include "task.hxx"

namespace scene {

BuildGroundTask::BuildGroundTask(shared_ptr<const Ground> o, MapPos p) : ground(o), pos(p)
{ }

string BuildGroundTask::to_string() const {
    return "Task: build ground at " + pos.to_string();
}

} // Scene

