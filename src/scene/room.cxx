#include "butler.hxx"
#include "log.hxx"
#include "constants.hxx"
#include "util/ext.hxx"
#include "scene/room.hxx"
#include "scene/world.hxx"

namespace scene {

Room::Room(shared_ptr<RoomType> _type, MapArea area, World *_world) :
    world(_world), type(_type)
{
    floor = area.floor();
    for (MapPos p : area) {
        tiles.push_back(p);
    }

    sf::FloatRect size(0, 0, tile_width, tile_width);
    tile1 = make_rect(size);
    tile1.setFillColor(make_color(0x9C9C9C, 100));
    tile2 = make_rect(size);
    tile2.setFillColor(make_color(0x6E6E6E, 100));

    setup();
}

int Room::get_floor() const {
    return floor;
}

void Room::draw(sf::RenderWindow &w) {
    if (is_dirty) setup();

    for (MapPos p : tiles) {
        WorldPos wp = world->map2world(p);
        // Checkboard pattern
        int parity = (p.pos.x + p.pos.y) & 1;
        auto &tile = parity ? tile1 : tile2;

        tile.setPosition(wp.pos);
        w.draw(tile);
    }

    w.draw(txt);
}

void Room::setup() {
    is_dirty = false;
    txt = create_txt("consola.ttf", 12, type->name);
    MapPos txt_pos = tiles.front();
    for (MapPos p : tiles) {
        txt_pos.pos.x = min(txt_pos.pos.x, p.pos.x);
        txt_pos.pos.y = min(txt_pos.pos.y, p.pos.y);
    }
    WorldPos wp = world->map2world(txt_pos);
    txt.setPosition(wp.pos);
}

} // scene

