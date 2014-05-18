#pragma once

#include "pos.hxx"

namespace scene {

    class World;

    struct Path {
        void draw(sf::RenderWindow &w, World *world);
        Path &operator << (const MapPos &p);
        vector<MapPos> path;
    };

};

