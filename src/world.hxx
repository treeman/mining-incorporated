#pragma once

#include "world.hxx"
#include "tile.hxx"
#include "worker.hxx"

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

    bool in_world(sf::Vector2i wp);
    bool in_world(int x, int y);

    void build(sf::Vector2i wp);

    void handle_input(const sf::Event &e);
    void update(const sf::Time &dt);
    void draw();

    //TilePtr get_tile(sf::Vector2i wp);
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

