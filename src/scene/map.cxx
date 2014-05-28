#include "map.hxx"

namespace scene {

shared_ptr<Tile> Map::tile(const MapPos &p) const {
    return floor(p.floor)->tile(p.pos);
}
shared_ptr<Floor> Map::floor(int floor) const {
    assert(0 <= floor && floor < (int)floors.size());
    return floors[floor];
}

int Map::num_floors() const { return floors.size(); }

void Map::update(const sf::Time &dt) {
    for (auto &x : floors)
        x->update(dt);
}
void Map::draw(sf::RenderWindow &w, int floor) {
    assert(0 <= floor && floor < (int)floors.size());
    floors[floor]->draw(w);
}

Map::Map() {

}

Path Map::pathfind(const MapPos &from, const MapPos &to) const {
    // TODO currently only pathfind inside one floor.
    assert(from.floor == to.floor);
    return floor(from.floor)->pathfind(from.pos, to.pos);
}

} // Scene

