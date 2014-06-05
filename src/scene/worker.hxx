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

        WorldPos get_pos() const;
        int on_floor() const;

        // TODO move to bounding box?
        bool is_on(const WorldPos &p) const;

        bool is_free() const;
        bool assign_task(shared_ptr<Task> task);
        bool has_task() const;
        shared_ptr<Task> get_task() const;

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

        // TODO list of variables, specify from lua!
        // 0.0 - 1.0
        float fatigue;
        float hunger;
        float happiness;
        float hygien;
        float motivation;
    public:
        void debug();
    };

}

