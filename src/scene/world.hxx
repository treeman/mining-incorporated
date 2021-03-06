#pragma once

#include "visualdebug.hxx"
#include "resources.hxx"
#include "scene/worker.hxx"
#include "scene/world.hxx"
#include "scene/tile.hxx"
#include "scene/task.hxx"
#include "scene/map.hxx"
#include "scene/event.hxx"
#include "scene/roomtype.hxx"
#include "scene/room.hxx"

namespace scene {

    class World {
    public:
        World(sf::RenderWindow &w);

        bool in_world(const WindowPos &p, int floor) const;
        bool in_world(const WorldPos &p) const;

        // TODO to center positions for WorldPos and WindowPos
        WorldPos map2world(const MapPos &p) const;
        WorldPos window2world(const WindowPos &p, int floor) const;
        MapPos window2map(const WindowPos &p, int floor) const;
        MapPos world2map(const WorldPos &p) const;
        WindowPos map2window(const MapPos &p) const;
        WindowPos world2window(const WorldPos &p) const;

        WorldPos clamp(const WorldPos &p) const;

        shared_ptr<Tile> get_tile(const MapPos &p) const;

        bool can_build(const MapPos &p, shared_ptr<Material> material) const;
        bool can_build(const MapPos &p, shared_ptr<RoomType> roomtype) const;
        bool can_build(const MapPos &p, const ObjectType *objecttype) const;
        bool can_mine(const MapPos &p) const;

        int num_floors() const;
    public:
        void handle_input(const sf::Event &e);
        void update(const sf::Time &dt);
        void draw(int floor);

        void push_event(unique_ptr<Event> cmd);
        void push_task(shared_ptr<Task> task);

        Path pathfind(const MapPos &from, const MapPos &to) const;
    private:
        void draw_pending_tasks();
        deque<shared_ptr<Task>> pending_tasks;
        VisualDebug task_debug;

        void new_worker(); // TODO specify locations
        shared_ptr<Worker> choose_free_worker();
        void assign_tasks();
    public:
        void task_done(shared_ptr<Task> task);
        //void skip_task(shared_ptr<Task> task);

    public:
        shared_ptr<Worker> select_closest_worker(const WorldPos &p);
        shared_ptr<Worker> select_worker(const WorldPos &p);
        int num_workers() const;
    private:
        sf::RenderWindow &w;
        sf::View view;

        shared_ptr<Map> map;
        vector<shared_ptr<Worker>> workers;

        // Count money etc.
        Resources resources;
    public:
        const Resources &get_resources() const;

    public:
        void mark_room(shared_ptr<RoomType> type, MapArea area);
        void remove_room(MapArea area);
        shared_ptr<Room> get_room(const MapPos &p) const;
    private:
        void remove_empty_rooms();
        vector<shared_ptr<Room>> rooms;
    };

}; // Scene

