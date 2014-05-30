#include <cassert>
#include "log.hxx"
#include "lua.hxx"
#include "scene/ore.hxx"

namespace scene {

Ore::Ore() { }

unique_ptr<Tile> Ore::create_tile(const WorldPos &p) const {
    unique_ptr<Tile> tile(new Tile(this));
    tile->set_pos(p);
    return move(tile);
}

} // Scene

