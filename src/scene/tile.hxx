#pragma once

//#include "roomtype.hxx"
#include "object.hxx"
#include "scene/planningobject.hxx"

namespace scene {

    class Ground;

    class Tile {
    public:
        void set_pos(int x, int y);

        void draw(sf::RenderWindow &w);

        /*
        // TODO move away?
        void set_room_preview();
        void set_object_preview();
        void clear_preview();

        void set_room_build_pending();
        void set_object_build_pending();
        */

        void suppress_preview();
        void set_preview(shared_ptr<PlanningObject> o);
        void remove_preview();
    private:
        shared_ptr<PlanningObject> preview;
        bool tmp_suppress_preview;

    public:
        bool is_walkable();

        /*
        bool has_object() const;
        void set_object(ObjectPtr obj);
        void remove_object();
        ObjectPtr get_object();
        */
    private:
        sf::Sprite ground_spr;
        sf::Vector2i pos;

        /*
        bool room_preview, object_preview;
        sf::Sprite room_preview_spr, object_preview_spr;
        ObjectPtr obj;
        RoomType room_type;
        bool room_build_pending, object_build_pending;
        */

        // TODO should be able to change ground
        Tile(const Ground *ground);
        const Ground *ground;

    public:
        const Ground *get_ground() const;

        friend class Ground;
        friend class Ore;
    };

}

