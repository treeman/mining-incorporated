#pragma once

#include "world.hxx"
#include "tile.hxx"
#include "worker.hxx"
#include "roomtype.hxx"
#include "objecttype.hxx"

class World {
public:
    World(sf::RenderWindow &w);

    sf::Vector2i window2tile(int x, int y);
    sf::Vector2i window2world(int x, int y);
    sf::Vector2i world2tile(int x, int y);
    sf::Vector2i tile2world(int x, int y);

    sf::Vector2i window2tile(sf::Vector2i p) { return window2tile(p.x, p.y); }
    sf::Vector2i window2world(sf::Vector2i p) { return window2world(p.x, p.y); }
    sf::Vector2i world2tile(sf::Vector2i p) { return world2tile(p.x, p.y); }
    sf::Vector2i tile2world(sf::Vector2i p) { return tile2world(p.x, p.y); }

    bool in_world(sf::Vector2i worldpos);
    bool in_world(int x, int y);
    bool is_tile(int x, int y);

    // World positions
    void build(sf::Vector2i worldpos, RoomType type);
    void remove(sf::Vector2i worldpos);

    // Tile positions
    void build(int x, int y, RoomType type);
    void build(int x, int y, ObjectType type);
    void remove(int x, int y);

    // Build and remove things in a 2x2 area, in tile coordinates.
    void build(int x1, int y1, int x2, int y2, RoomType type);
    void build(int x1, int y1, int x2, int y2, ObjectType type);
    void remove(int x1, int y1, int x2, int y2);

    // Current action
    void preview_room_build(int x, int y);
    void preview_room_build(int x1, int y1, int x2, int y2);
    void preview_object_build(int x, int y);
    void clear_preview();

    void handle_input(const sf::Event &e);
    void update(const sf::Time &dt);
    void draw();

    void new_worker();
    WorkerPtr choose_free_worker();
    vector<sf::Vector2i> pathfind(sf::Vector2i s, sf::Vector2i t);

    sf::RenderWindow &w;
    sf::View view;

    // TODO multiple levels
    vector<vector<TilePtr>> grid;
    vector<WorkerPtr> workers;

    deque<WorkerPtr> free_workers;

    sf::Text mpos;
};

