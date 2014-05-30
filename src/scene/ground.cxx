#include <cassert>
#include "log.hxx"
#include "lua.hxx"
#include "abort.hxx"
#include "scene/ground.hxx"

namespace scene {

Ground::Ground() : is_walkable(false), remove_time(0), build_time(0)
{ }

unique_ptr<Tile> Ground::create_tile(const WorldPos &p) const {
    unique_ptr<Tile> tile(new Tile(this));
    tile->set_pos(p);
    return move(tile);
}

} // Scene

