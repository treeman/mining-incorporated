#pragma once

#include "std.hxx"
#include "scene/tile.hxx"

namespace scene {
    // TODO change to GroundType
    class Ground {
    public:
        virtual ~Ground() { }
        virtual unique_ptr<Tile> create_tile(const WorldPos &p) const;

        string key;
        bool is_walkable;
        float remove_time;
        float build_time;
        string spr;
    protected:
        Ground();
        friend class ObjectFactory;
    };
};

