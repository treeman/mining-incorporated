#pragma once

#include "scene/ground.hxx"
#include "pos.hxx"

// A task is something for workers to do,
// verified by the world so it works.
namespace scene {
    class Task {
    public:
        virtual ~Task() = default;

        virtual string to_string() const = 0;
    };

    class BuildGroundTask : public Task {
    public:
        BuildGroundTask(shared_ptr<const Ground> o, MapPos pos);

        string to_string() const override;

        shared_ptr<const Ground> ground;
        MapPos pos;
    };

} // Scene

