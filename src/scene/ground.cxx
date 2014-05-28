#include <cassert>
#include "log.hxx"
#include "lua.hxx"
#include "abort.hxx"
#include "scene/ground.hxx"

namespace scene {

Ground::Ground() : is_walkable(false), remove_time(0), build_time(0)
{ }

unique_ptr<Tile> Ground::create_tile(int x, int y) const {
    // TODO refactor Tile
    unique_ptr<Tile> tile(new Tile(this));
    tile->set_pos(x, y);
    return move(tile);
}

} // Scene

