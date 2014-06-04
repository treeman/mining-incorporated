#include "coord.hxx"
#include "locator.hxx"
#include "state/game.hxx"
#include "scene/world.hxx"

scene::World &get_world() {
    return Locator::get_game_state().get_world();
}

WorldPos map2world(const MapPos &p) {
    return get_world().map2world(p);
}
WorldPos window2world(const WindowPos &p, int floor) {
    return get_world().window2world(p, floor);
}
MapPos window2map(const WindowPos &p, int floor) {
    return get_world().window2map(p, floor);
}
MapPos world2map(const WorldPos &p) {
    return get_world().world2map(p);
}
WindowPos map2window(const MapPos &p) {
    return get_world().map2window(p);
}
WindowPos world2window(const WorldPos &p) {
    return get_world().world2window(p);
}

