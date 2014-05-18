#include "task.hxx"

namespace scene {

BuildGroundTask::BuildGroundTask(shared_ptr<const Ground> o, MapPos p) : ground(o), pos(p)
{ }

string BuildGroundTask::to_string() const {
    return "build ground " + pos.to_string();
}

} // Scene

