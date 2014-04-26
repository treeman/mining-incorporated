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
Tile::Tile(sf::Sprite s, int x, int y) : spr(s), pos(x, y) {
    spr.setPosition(pos.x, pos.y);
}
void Tile::draw(sf::RenderWindow &w) {
    w.draw(spr);
}

void Tile::set_type(TileType tile) {

}

