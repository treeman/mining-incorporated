#include "butler.hxx"
#include "scene/room.hxx"

namespace scene {

Room::Room(shared_ptr<RoomType> type) {
    txt = create_txt("consola.ttf", 12, type->name);
}

int Room::get_floor() const {
    return floor;
}

void Room::draw(sf::RenderWindow &w) {

}

} // scene

