#pragma once

#include "objecttype.hxx"
#include "resources.hxx"
#include "scene/worker.hxx"
#include "scene/world.hxx"
#include "scene/tile.hxx"
#include "scene/task.hxx"
#include "scene/map.hxx"
#include "scene/command.hxx"

namespace scene {

    class World {
    public:
        World(sf::RenderWindow &w);

        bool in_world(const WindowPos &p) const;
        bool in_world(const WorldPos &p) const;

        WorldPos window2world(const WindowPos &p) const;
        MapPos window2map(const WindowPos &p) const;
        MapPos world2map(const WorldPos &p) const;
        WindowPos map2window(const MapPos &p) const;
        WindowPos world2window(const WorldPos &p) const;

        shared_ptr<Tile> get_tile(const MapPos &p) const;

        // TODO remove
        bool in_world(sf::Vector2i worldpos);
        bool in_world(int x, int y);
        bool is_tile(int x, int y);

        // TODO move to gui
        int num_floors() const;
        void set_curr_floor(int floor);
        int get_curr_floor() const;
    private:
        int curr_floor;

    public:
        void handle_input(const sf::Event &e);
        void update(const sf::Time &dt);
        void draw();

        void push_cmd(unique_ptr<Command> cmd);
        void push_task(shared_ptr<Task> task); // TODO unique_ptr!
    private:
        deque<shared_ptr<Task>> pending_tasks;

        // TODO move to commands/events
        void new_worker();
        WorkerPtr choose_free_worker();
        void task_done(shared_ptr<Task> task);
        void skip_task(shared_ptr<Task> task);
        void assign_tasks();

        // TODO move to map
        vector<sf::Vector2i> pathfind(sf::Vector2i s, sf::Vector2i t);

        // TODO some kind of bounding box for workers
        shared_ptr<Worker> select_closest_worker(const WorldPos &p);
    private:
        sf::RenderWindow &w;
        sf::View view;

        // TODO multiple levels
        shared_ptr<Tile> get_tile(int x, int y);
        shared_ptr<Tile> get_tile(sf::Vector2i pos);

        shared_ptr<Map> map;
        vector<WorkerPtr> workers;

        sf::Text stat_txt;

        // Count money etc.
        Resources resources;

        // TODO move to gui
        void draw_stats();
        void draw_stats(string pre, int &val, sf::Color color, int x, int y);

        // TODO move to gui
        // Levels
        int current_level;
    };

}; // Scene

