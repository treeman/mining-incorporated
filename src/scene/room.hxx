#pragma once

#include "std.hxx"
#include "scene/roomtype.hxx"
#include "scene/area.hxx"

namespace scene {

    class Room {
    public:
        Room(shared_ptr<RoomType> type, MapArea area, World *world);

        int get_floor() const;
        void increase(MapArea area);
        void remove(MapArea area);

        void draw(sf::RenderWindow &w);
    private:
        void setup();
        bool is_dirty;

        World *world;

        sf::Text txt;
        int floor;
        sf::ConvexShape tile1, tile2;

        vector<MapPos> tiles;
        shared_ptr<RoomType> type;
    };
}

