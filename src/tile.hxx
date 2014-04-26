#pragma once

#include "util.hxx"

enum TileType {
    StoneTile,
};

class Tile {
public:
    Tile(sf::Sprite spr, int x, int y);

    void set_type(TileType tile);
    void draw(sf::RenderWindow &w);
    bool is_marked;

private:
    sf::Sprite spr;
    sf::Vector2i pos;
};

typedef shared_ptr<Tile> TilePtr;

TilePtr create_tile(TileType, int x, int y);

