#pragma once

#include <memory>
#include <string>
using namespace std;

struct Ore {
    float mine_time;
    int min_ores, max_ores;

    // TODO collect ores instead.
    int money_per_ore;
};

shared_ptr<const Ground> get_ground(string key);

