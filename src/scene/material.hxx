#pragma once

#include "scene/ground.hxx"

namespace scene {

    class Material {
    public:
        Material(shared_ptr<const Ground> ground, int cost);

        string to_string() const;

        shared_ptr<const Ground> ground;
        int cost;
    };

};

