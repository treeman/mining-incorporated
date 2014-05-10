#pragma once

#include "roomtype.hxx"
#include "object.hxx"

class Ground;

class Tile {
public:
    void set_pos(int x, int y);

    void draw(sf::RenderWindow &w);

    void set_room_preview();
    void set_object_preview();
    void clear_preview();

    void set_room_build_pending();
    void set_object_build_pending();

    bool is_walkable();

    bool has_object() const;
    void set_object(ObjectPtr obj);
    void remove_object();
    ObjectPtr get_object();
private:
    sf::Sprite spr;
    sf::Vector2i pos;
    bool room_preview, object_preview;
    sf::Sprite room_preview_spr, object_preview_spr;
    ObjectPtr obj;
    RoomType room_type;
    bool room_build_pending, object_build_pending;

    // TODO should be able to change ground
    Tile(const Ground *ground);
    const Ground *ground;

    friend class Ground;
    friend class Ore;
};
