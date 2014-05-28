#pragma once

#include "scene/ground.hxx"

namespace scene {

    class Material {
    public:
        Material(const Ground *ground, int cost);

        string to_string() const;

        const Ground *ground;
        int cost;
    };

};

