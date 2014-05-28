#include <cassert>
#include "log.hxx"
#include "lua.hxx"
#include "scene/ore.hxx"

namespace scene {

Ore::Ore() { }

unique_ptr<Tile> Ore::create_tile(int x, int y) const {
    // TODO refactor Tile
    unique_ptr<Tile> tile(new Tile(this));
    tile->set_pos(x, y);
    return move(tile);
}

} // Scene

