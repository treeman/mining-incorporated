#pragma once

#include "std.hxx"
#include "scene/roomtype.hxx"
#include "scene/area.hxx"
#include "scene/world.hxx"

namespace scene {

    class Room {
    public:
        Room(shared_ptr<RoomType> type, MapArea area, World *world);

        int get_floor() const;
        void extend(MapPos pos);
        void remove(MapPos pos);
        void extend(MapArea area);
        void remove(MapArea area);
        bool can_extend(shared_ptr<RoomType> type, MapArea area) const;
        bool empty() const;

        string to_string() const;
        int size() const;

        void draw(sf::RenderWindow &w);
    private:
        void setup();
        bool is_dirty;

        World *world;

        sf::Text txt;
        int floor;
        sf::ConvexShape tile1, tile2;

        set<MapPos> tiles;
        shared_ptr<RoomType> type;
    };
}

