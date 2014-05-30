#include "tile.hxx"
#include "butler.hxx"
#include "ground.hxx"

namespace scene {

// Tile class
Tile::Tile(const Ground *_ground) : preview(nullptr),
    tmp_suppress_preview(false), pos(-1, -1, -1), room(nullptr)
{
    set_ground(_ground);
}
//void Tile::set_pos(int x, int y) {
    //pos.x = x; pos.y = y;
    //ground_spr.setPosition(x, y);
    //if (preview != nullptr)
        //preview->set_pos(x, y);
//}
void Tile::set_pos(const WorldPos &p) {
    pos = p;
    ground_spr.setPosition(pos.pos);
    if (preview != nullptr)
        preview->set_pos(pos.pos.x, pos.pos.y);
}
WorldPos Tile::get_pos() const {
    return pos;
}

void Tile::draw(sf::RenderWindow &w) {
    ground_spr.setColor(sf::Color::White);
    w.draw(ground_spr);

    if (tmp_suppress_preview)
        tmp_suppress_preview = false;
    else if (preview != nullptr)
        preview->draw(w);
}

void Tile::suppress_preview() {
    tmp_suppress_preview = true;
}
void Tile::set_preview(shared_ptr<PlanningObject> o) {
    assert(o != nullptr);
    preview.reset(new PlanningObject(*o));
    preview->set_pos(pos.pos.x, pos.pos.y);
}
void Tile::remove_preview() {
    preview = nullptr;
}

bool Tile::is_walkable() {
    return ground->is_walkable;
}

void Tile::set_ground(const Ground *_ground) {
    ground = _ground;
    ground_spr = create_sprite(ground->spr);
    ground_spr.setPosition(pos.pos.x, pos.pos.y);
}

const Ground *Tile::get_ground() const {
    assert(ground != nullptr);
    return ground;
}

shared_ptr<Room> Tile::get_room() const {
    return room;
}
void Tile::set_room(shared_ptr<Room> _room) {
    room = _room;
}

} // scene

