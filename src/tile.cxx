#include "tile.hxx"
#include "butler.hxx"

TilePtr create_tile(BuildType type, int x, int y) {
    return TilePtr(new Tile(type, x, y));
}


// Tile class
Tile::Tile(BuildType type, int x, int y) : pos(x, y) {
    set_type(type);
    is_marked = room_preview = object_preview = false;

    room_preview_spr = create_sprite("room_preview.png");
    room_preview_spr.setColor(sf::Color(255, 255, 255, 100));
    room_preview_spr.setPosition(x, y);
    object_preview_spr = create_sprite("object_preview.png");
    object_preview_spr.setColor(sf::Color(255, 255, 255, 150));
    object_preview_spr.setPosition(x, y);
}
void Tile::draw(sf::RenderWindow &w) {
    // TODO different tiles for different rooms
    if (is_marked)
        spr.setColor(sf::Color(240, 0, 100));
    else
        spr.setColor(sf::Color::White);
    w.draw(spr);

    if (room_preview) {
        w.draw(room_preview_spr);
    }
    else if (object_preview) {
        w.draw(object_preview_spr);
    }
}

void Tile::set_room_preview() { room_preview = true; object_preview = false; }
void Tile::set_object_preview() { room_preview = false; object_preview = true; }
void Tile::clear_preview() { room_preview = object_preview = false; }

void Tile::set_type(BuildType type) {
    spr = create_tile_sprite(type);
    spr.setPosition(pos.x, pos.y);
}
void Tile::mark() {
    is_marked = true;
}
void Tile::unmark() {
    is_marked = false;
}
bool Tile::is_walkable() {
    return !is_marked;
}


