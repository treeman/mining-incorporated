#include "tile.hxx"
#include "butler.hxx"
#include "ground.hxx"

// Tile class
Tile::Tile(const Ground *_ground) : ground(_ground) {
    room_preview = object_preview = false;
    room_build_pending = object_build_pending = false;

    // TODO move to set_ground
    spr = create_sprite(ground->spr);
    room_preview_spr = create_sprite("room_preview.png");
    room_preview_spr.setColor(sf::Color(255, 255, 255, 100));
    object_preview_spr = create_sprite("object_preview.png");
    object_preview_spr.setColor(sf::Color(255, 255, 255, 150));
}
void Tile::set_pos(int x, int y) {
    pos.x = x; pos.y = y;
    spr.setPosition(x, y);
    room_preview_spr.setPosition(x, y);
    object_preview_spr.setPosition(x, y);
}

void Tile::draw(sf::RenderWindow &w) {
    // TODO different tiles for different rooms
    //if (is_marked)
        //spr.setColor(sf::Color(240, 0, 100));
    //else
    spr.setColor(sf::Color::White);
    w.draw(spr);

    if (room_preview || room_build_pending) {
        w.draw(room_preview_spr);
    }

    if (has_object()) {
        obj->draw(w);
    }
    else if (object_preview || object_build_pending) {
        w.draw(object_preview_spr);
    }
}

void Tile::set_room_preview() { room_preview = true; object_preview = false; }
void Tile::set_object_preview() { room_preview = false; object_preview = true; }
void Tile::clear_preview() { room_preview = object_preview = false; }

void Tile::set_room_build_pending() { room_build_pending = true; }
void Tile::set_object_build_pending() { object_build_pending = true; }

bool Tile::is_walkable() {
    return ground->is_walkable;
}

bool Tile::has_object() const {
    return (bool)obj;
}
void Tile::set_object(ObjectPtr o) {
    object_preview = object_build_pending = false;
    obj = o;
    obj->set_pos(pos.x, pos.y);
}
void Tile::remove_object() {
    obj.reset();
}

ObjectPtr Tile::get_object() {
    return obj;
}

