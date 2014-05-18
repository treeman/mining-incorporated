#pragma once

#include "pos.hxx"

namespace scene {

    class World;

    class Path {
    public:
        void draw(sf::RenderWindow &w, World *world);
        void print();
        bool empty() const;

        unsigned size() const;
        MapPos &operator[](unsigned i);
        MapPos operator[](unsigned i) const;

        MapPos goal() const;
    private:
        vector<MapPos> v;
        friend class Floor;
    };

};

