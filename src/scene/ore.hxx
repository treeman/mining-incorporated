#pragma once

#include <memory>
#include <string>
using namespace std;

#include "ground.hxx"

namespace scene {
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
        friend class ObjectFactory;
    };
}

