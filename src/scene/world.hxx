#pragma once

#include "roomtype.hxx"
#include "objecttype.hxx"
#include "scene/worker.hxx"
#include "scene/world.hxx"
#include "scene/tile.hxx"
#include "scene/task.hxx"
#include "scene/map.hxx"
#include "resources.hxx"

namespace scene {

    class World {
    public:
        World(sf::RenderWindow &w);

        // TODO remove/move
        // xD
        //sf::Vector2i window2tile(int x, int y);
        //sf::Vector2i window2world(int x, int y);
        sf::Vector2i world2tile(int x, int y);
        sf::Vector2i tile2world(int x, int y);
        sf::Vector2i world2window(int x, int y);
        sf::Vector2i tile2window(int x, int y);

        //sf::Vector2i window2tile(sf::Vector2i p) { return window2tile(p.x, p.y); }
        //sf::Vector2i window2world(sf::Vector2i p) { return window2world(p.x, p.y); }
        sf::Vector2i world2tile(sf::Vector2i p) { return world2tile(p.x, p.y); }
        sf::Vector2i tile2world(sf::Vector2i p) { return tile2world(p.x, p.y); }
        sf::Vector2i world2window(sf::Vector2i p) { return world2window(p.x, p.y); }
        sf::Vector2i tile2window(sf::Vector2i p) { return tile2window(p.x, p.y); }

        bool in_world(const WindowPos &p) const;
        bool in_world(const WorldPos &p) const;
        WorldPos window2world(const WindowPos &p) const;
        MapPos window2map(const WindowPos &p) const;
        MapPos world2map(const WorldPos &p) const;

        //shared_ptr<Tile> get_tile(const WorldPos &p) const;
        shared_ptr<Tile> get_tile(const MapPos &p) const;

        // TODO remove
        bool in_world(sf::Vector2i worldpos);
        bool in_world(int x, int y);
        bool is_tile(int x, int y);

        int num_floors() const;
        void set_curr_floor(int floor);
        int get_curr_floor() const;
    private:
        int curr_floor;

    public:
        // TODO move to commands
        // World positions
        void build(sf::Vector2i worldpos, RoomType type);
        void remove(sf::Vector2i worldpos);

        // Tile positions
        void build(int x, int y, RoomType type);
        void build(int x, int y, ObjectType type);
        //void remove(int x, int y);
        void sell_object(int x, int y);

        // Build and remove things in a 2x2 area, in tile coordinates.
        void build(int x1, int y1, int x2, int y2, RoomType type);
        //void build(int x1, int y1, int x2, int y2, ObjectType type);
        //void remove(int x1, int y1, int x2, int y2);

        // TODO move to commands
        // Current action
        void preview_room_build(int x, int y);
        void preview_room_build(int x1, int y1, int x2, int y2);
        void preview_object_build(int x, int y);
        void clear_preview();

        void handle_input(const sf::Event &e);
        void update(const sf::Time &dt);
        void draw();

        // TODO move to commands/events
        void new_worker();
        WorkerPtr choose_free_worker();
        vector<sf::Vector2i> pathfind(sf::Vector2i s, sf::Vector2i t);
        void task_done(Task task);
        void skip_task(Task task);
        void assign_tasks();

        //WorkerPtr select_closest_worker(int x, int y);
        shared_ptr<Worker> select_closest_worker(const WorldPos &p);

        int calculate_build_cost(int x1, int y1, int x2, int y2, RoomType type);
        RoomType get_tile_type(int x, int y);
    private:
        sf::RenderWindow &w;
        sf::View view;

        // TODO multiple levels
        shared_ptr<Tile> get_tile(int x, int y);
        shared_ptr<Tile> get_tile(sf::Vector2i pos);

        //vector<vector<shared_ptr<Tile>>> grid;
        //shared_ptr<Level> level;
        shared_ptr<Map> map;
        vector<WorkerPtr> workers;

    public:
        void add_task(unique_ptr<Task> task);
    private:
        deque<unique_ptr<Task>> pending_tasks;

        // TODO delete, old
        //deque<WorkerPtr> free_workers;
        deque<Task> tasks;

        sf::Text mpos;
        sf::Text txt;
        sf::Text stat_txt;

        // Count money etc.
        Resources resources;
        void draw_stats();
        void draw_stats(string pre, int &val, sf::Color color, int x, int y);

        // Levels
        int current_level;

        // TODO move to Locator object
    public:
        shared_ptr<PlanningObject> get_planning_object(PlanningType o) const;
    private:
        void init_planning_objects();
        vector<shared_ptr<PlanningObject>> planning_objects;
    };

}; // Scene

