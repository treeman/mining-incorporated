#pragma once

#include "std.hxx"
#include "scene/roomtype.hxx"

namespace scene {

    class Room {
    public:
        Room(shared_ptr<RoomType> type, MapArea area);

        int get_floor() const;
        void increase(MapArea area);

        void draw(sf::RenderWindow &w);
    private:
        sf::Text txt;
        int floor;
    };
}

