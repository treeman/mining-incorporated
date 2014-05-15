#include "tile.hxx"
#include "butler.hxx"
#include "ground.hxx"

namespace scene {

// Tile class
Tile::Tile(const Ground *_ground) : preview(nullptr),
    tmp_suppress_preview(false), ground(_ground)
{
    // TODO move to set_ground
    ground_spr = create_sprite(ground->spr);
}
void Tile::set_pos(int x, int y) {
    pos.x = x; pos.y = y;
    ground_spr.setPosition(x, y);
    if (preview != nullptr)
        preview->set_pos(x, y);
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
    preview->set_pos(pos.x, pos.y);
}
void Tile::remove_preview() {
    preview = nullptr;
}

bool Tile::is_walkable() {
    return ground->is_walkable;
}

const Ground *Tile::get_ground() const {
    return ground;
}

} // scene
