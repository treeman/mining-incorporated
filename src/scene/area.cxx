
#include "scene/area.hxx"
#include "scene/world.hxx"

namespace scene {

MapArea to_map(scene::World *world, WorldArea sel) {
    return MapArea(world->world2map(sel.first), world->world2map(sel.last));
}

} // scene

