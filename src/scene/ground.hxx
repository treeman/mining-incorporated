#pragma once

#include "std.hxx"
#include "scene/tile.hxx"

namespace scene {

    // TODO encapsulate
    void load_ground_definitions(string lua_file);

    class Ground {
    public:
        virtual ~Ground() { }
        virtual unique_ptr<Tile> create_tile(int x, int y) const;

        string key;
        bool is_walkable;
        float remove_time;
        float build_time;
        string spr;
    protected:
        Ground();
        friend void load_ground_definitions(string);
    };

    // TODO merge with ore?
    // TODO change from shared to strict pointer
    shared_ptr<const Ground> get_ground(string key);
};

