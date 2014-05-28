#pragma once

#include "std.hxx"
#include "scene/roomtype.hxx"

namespace scene {

    class Room {
    public:
        Room(shared_ptr<RoomType> type);

        int get_floor() const;

        void draw(sf::RenderWindow &w);
    private:
        sf::Text txt;
        int floor;
    };
}

