#pragma once

#include "util.hxx"
#include "task.hxx"

class World;

class Worker {
public:
    Worker(int x, int y, World *world);

    bool is_free();
    bool assign_task(Task task);

    void update(const sf::Time &dt);
    void draw(sf::RenderWindow &w);
private:
    void follow_path(const sf::Time &dt);

    sf::Sprite spr;
    sf::Vector2f pos;
    sf::Vector2i tile_pos;
    vector<sf::Vector2i> path;

    World *world;

    Task current_task;
    sf::Text txt;
};

typedef shared_ptr<Worker> WorkerPtr;

WorkerPtr create_worker(int x, int y, World *world);

