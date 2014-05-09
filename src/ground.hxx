#pragma once

#include <memory>
#include <string>
using namespace std;

#include "tile.hxx"

void load_ground_definitions(string lua_file);

class Ground {
public:
    unique_ptr<Tile> create_tile(int x, int y) const;

    bool is_walkable;
    float remove_time;
    float build_time;
    string spr;
private:
    Ground();
    bool is_valid();
    friend void load_ground_definitions(string);
};

shared_ptr<const Ground> get_ground(string key);

