#pragma once

#include "util.hxx"
#include "roomtype.hxx"
#include "object.hxx"

class Tile {
public:
    Tile(RoomType type, int x, int y);

    void draw(sf::RenderWindow &w);

    void set_room_preview();
    void set_object_preview();
    void clear_preview();

    void set_room_build_pending();
    void set_object_build_pending();

    void set_type(RoomType type);
    RoomType get_type();

    void set_sprite(sf::Sprite spr);
    void mark(); // TODO remove
    void unmark();
    bool is_walkable();

    bool has_object() const;
    void set_object(ObjectPtr obj);
    void remove_object();
    ObjectPtr get_object();
private:
    sf::Sprite spr;
    sf::Vector2i pos;
    bool is_marked, room_preview, object_preview;
    sf::Sprite room_preview_spr, object_preview_spr;
    ObjectPtr obj;
    RoomType room_type;
    bool room_build_pending, object_build_pending;
};

typedef shared_ptr<Tile> TilePtr;
TilePtr create_tile(RoomType type, int x, int y);

