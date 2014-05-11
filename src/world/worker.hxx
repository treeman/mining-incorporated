#pragma once

#include "task.hxx"
#include "gui/progressbar.hxx"
#include "pos.hxx"

class World;

class Worker {
public:
    Worker(int x, int y, World *world);

    // TODO change to our own positions
    // TODO position in center of worker
    // TODO some kind of bounding box?
    sf::Vector2f get_pos() const { return pos; }

    bool is_free();
    bool assign_task(Task task);

    void update(const sf::Time &dt);
    void draw(sf::RenderWindow &w);
private:
    void follow_path(const sf::Time &dt);

    sf::Sprite spr;
    FPoint pos;
    TilePos tile_pos;
    vector<sf::Vector2i> path;

    World *world;

    Task current_task;
    sf::Text txt;

    bool has_work_time;
    sf::Clock work_clock;
    float work_time;
    Progressbar progressbar;
};

typedef shared_ptr<Worker> WorkerPtr;

WorkerPtr create_worker(int x, int y, World *world);

