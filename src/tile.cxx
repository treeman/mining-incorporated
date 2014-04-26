#include "tile.hxx"
#include "butler.hxx"

map<TileType, string> tiles = {
    {StoneTile, "stone.png"},
};

sf::Sprite get_sprite(TileType type) {
    auto it = tiles.find(type);
    if (it == tiles.end()) {
        printf("Error type %d not found in tiles!\n", type);
        exit(-1);
    }
    return create_sprite(it->second);
}

TilePtr create_tile(TileType type, int x, int y) {
    return TilePtr(new Tile(get_sprite(type), x, y));
}

// Tile class
Tile::Tile(sf::Sprite s, int x, int y) : spr(s), pos(x, y), is_marked(false) {
    spr.setPosition(pos.x, pos.y);
}
Tile::Tile(const Tile &t) : spr(t.spr), pos(t.pos), is_marked(t.is_marked) {

}
Tile &Tile::operator = (const Tile &t) {
    spr = t.spr;
    pos = t.pos;
    is_marked = t.is_marked;
    return *this;
}
void Tile::draw(sf::RenderWindow &w) {
    if (is_marked) {
        spr.setColor(make_color(0xFF367C));
    }
    else {
        spr.setColor(sf::Color::White);
    }
    w.draw(spr);
}

void Tile::mark() {
    is_marked = true;
}
bool Tile::is_walkable() {
    return !is_marked;
}

void Tile::set_type(TileType type) {
    spr = get_sprite(type);
    spr.setPosition(pos.x, pos.y);
}

