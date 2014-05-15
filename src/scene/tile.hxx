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
        sf::Vector2i pos;

        // TODO should be able to change ground
        Tile(const Ground *ground);
        const Ground *ground;

    public:
        const Ground *get_ground() const;

        friend class Ground;
        friend class Ore;
    };

}

