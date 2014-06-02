#pragma once

#include "std.hxx"
#include "pos.hxx"
#include "scene/planningobject.hxx"

namespace scene {

    class Ground;
    class Room;
    class Object;

    class Tile {
    public:
        void set_pos(const WorldPos &p);
        WorldPos get_pos() const;

        void draw(sf::RenderWindow &w);

        void suppress_preview();
        void set_preview(shared_ptr<PlanningObject> o);
        void remove_preview();
    private:
        shared_ptr<PlanningObject> preview;
        bool tmp_suppress_preview;

    public:
        bool is_walkable();

    private:
        sf::Sprite ground_spr;
        WorldPos pos;

        Tile(const Ground *ground);
        const Ground *ground;
    public:
        void set_ground(const Ground *ground);
        const Ground *get_ground() const;

        friend class Ground;
        friend class Ore;

        shared_ptr<Room> get_room() const;
        void set_room(shared_ptr<Room> room);
    private:
        shared_ptr<Room> room;
    public:
        shared_ptr<Object> get_object() const;
        void set_object(shared_ptr<Object> o);
    private:
        shared_ptr<Object> object;
    };

}

