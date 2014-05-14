#include "map.hxx"

namespace scene {

shared_ptr<Map> make_map() {
    shared_ptr<Map> res(new Map());
    for (int i = 0; i < 10; ++i) {
        res->floors.push_back(make_floor(i));
    }
    return res;
}

shared_ptr<Tile> Map::tile(const MapPos &p) const {
    return floor(p.floor)->tile(p.pos);
}
shared_ptr<Tile> Map::tile(int x, int y, int f) const {
    return floor(f)->tile(x, y);
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

} // Scene
