#pragma once

#include "util.hxx"
#include "buildtype.hxx"

class Tile {
public:
    Tile(BuildType type, int x, int y);

    void draw(sf::RenderWindow &w);

    void set_room_preview();
    void set_object_preview();
    void clear_preview();

    void set_type(BuildType type);

    void set_sprite(sf::Sprite spr);
    void mark(); // TODO remove
    void unmark();
    bool is_walkable();
private:
    sf::Sprite spr;
    sf::Vector2i pos;
    bool is_marked, room_preview, object_preview;
    sf::Sprite room_preview_spr, object_preview_spr;
};

typedef shared_ptr<Tile> TilePtr;
TilePtr create_tile(BuildType type, int x, int y);
