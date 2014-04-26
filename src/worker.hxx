#pragma once

#include "util.hxx"
#include "worker.hxx"

class World;

class Worker {
public:
    Worker(int x, int y, World *world);

    void follow_path(const sf::Time &dt);
    void set_path(vector<sf::Vector2i> p);

    void update(const sf::Time &dt);
    void draw(sf::RenderWindow &w);

    sf::Sprite spr;
    sf::Vector2f pos;
    sf::Vector2i tile_pos;
    vector<sf::Vector2i> path;

    World *world;
};

typedef shared_ptr<Worker> WorkerPtr;

WorkerPtr create_worker(int x, int y, World *world);
