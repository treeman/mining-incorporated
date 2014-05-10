#include "dimension.hxx"

shared_ptr<Dimension> make_dimension() {
    shared_ptr<Dimension> res(new Dimension());
    for (int i = 0; i < 5; ++i) {
        res->levels.push_back(make_level(i));
    }
    return res;
}

shared_ptr<Tile> Dimension::tile(int x, int y, int lvl) {
    return level(lvl)->tile(x, y);
}
shared_ptr<Level> Dimension::level(int lvl) {
    assert(0 <= lvl && lvl < (int)levels.size());
    return levels[lvl];
}

void Dimension::update(const sf::Time &dt) {
    for (auto &x : levels)
        x->update(dt);
}
void Dimension::draw(sf::RenderWindow &w, int lvl) {
    assert(0 <= lvl && lvl < (int)levels.size());
    levels[lvl]->draw(w);
}

Dimension::Dimension() {

}

