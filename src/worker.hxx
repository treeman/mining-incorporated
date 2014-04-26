#pragma once

#include "util.hxx"
#include "worker.hxx"

class Worker {
public:
    Worker(int x, int y);

    void update(const sf::Time &dt);
    void draw(sf::RenderWindow &w);
private:
    sf::Sprite spr;
    sf::Vector2i pos;
};

typedef shared_ptr<Worker> WorkerPtr;

WorkerPtr create_worker(int x, int y);
