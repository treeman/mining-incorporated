#include "gui/selection.hxx"
#include "scene/world.hxx"

namespace gui {

MapSelection to_map(scene::World *world, WorldSelection sel) {
    return MapSelection(world->world2map(sel.start), world->world2map(sel.end));
}

Selection::Selection() : active(false) {

}

WorldSelection Selection::get_area() const {
    return WorldSelection(area);
}

string Selection::to_string() const {
    if (!is_active()) return "inactive";
    return get_area().to_string();
}

void Selection::begin(const WorldPos &start) {
    active = true;
    area.start = start;
    area.end = start;
}
void Selection::extend(const WorldPos &end) {
    area.end = end;
}
void Selection::clear() {
    active = false;
}
bool Selection::is_active() const {
    return active;
}
bool Selection::is_point() const {
    return is_active() && area.start == area.end;
}

} // gui
