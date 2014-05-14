#pragma once

#include <memory>
#include <string>
using namespace std;

#include "ground.hxx"

namespace scene {

    void load_ore_definitions(string lua_file);

    class Ore : public Ground {
    public:
        virtual ~Ore() { }
        virtual unique_ptr<Tile> create_tile(int x, int y) const override;

        float mine_time;
        int min_ores, max_ores;

        // TODO collect ores instead.
        int money_per_ore;
    private:
        Ore();
        friend void load_ore_definitions(string);
    };

    shared_ptr<const Ore> get_ore(string key);

}

