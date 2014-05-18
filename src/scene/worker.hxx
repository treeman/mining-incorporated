#pragma once

#include "pos.hxx"
#include "scene/task.hxx"
#include "scene/planningobject.hxx"
#include "scene/path.hxx"
#include "gui/progressbar.hxx"

namespace scene {

    class World;

    class Worker {
    public:
        Worker(const WorldPos &pos, World *world);

        // TODO change to our own positions
        // TODO position in center of worker
        // TODO some kind of bounding box?
        //sf::Vector2f get_pos() const { return pos; }
        //
        WorldPos get_pos() const;
        int on_floor() const;

        bool is_free() const;
        bool assign_task(shared_ptr<Task> task);

        void update(const sf::Time &dt);
        void draw(sf::RenderWindow &w);
    private:
        World *world;

        void follow_path(const sf::Time &dt);
        unsigned p_ind;
        Path path;

        sf::Sprite spr;
        WorldPos world_pos;
        MapPos map_pos;

        shared_ptr<Task> current_task;
        sf::Text txt;

        bool has_work_time;
        sf::Clock work_clock;
        float work_time;
        gui::Progressbar progressbar;
    };

}

