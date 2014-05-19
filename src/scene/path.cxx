#include "locator.hxx"
#include "constants.hxx"
#include "util/ext.hxx"
#include "scene/path.hxx"
#include "scene/world.hxx"

namespace scene {

void Path::draw(sf::RenderWindow &w, World *world) {
    sf::VertexArray lines(sf::LinesStrip);
    for (auto &next : v) {
        // Draw at center
        auto p = world->map2world(next).pos;
        auto pos = FPoint(p.x + tile_width / 2, p.y + tile_width / 2);
        lines.append(sf::Vertex(pos, make_color(0x42F207)));
    }
    w.draw(lines);
}

void Path::print() {
    L_("path of size %d:\n", v.size());
    for (auto &p : v)
        L_("  %s\n", p.to_string());
}

bool Path::empty() const {
    return v.empty();
}
void Path::clear() {
    v.clear();
}
unsigned Path::size() const {
    return v.size();
}
MapPos &Path::operator[](unsigned i) {
    return v.at(i);
}
MapPos Path::operator[](unsigned i) const {
    return v.at(i);
}

MapPos Path::goal() const {
    assert(!v.empty());
    return v.back();
}

} // scene

