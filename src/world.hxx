#pragma once

#include "world.hxx"
#include "tile.hxx"
#include "worker.hxx"

class World {
public:
    World(sf::RenderWindow &w);

    sf::Vector2i window2world(int x, int y);
    bool in_world(sf::Vector2i wp);
    bool in_world(int x, int y);

    void build(sf::Vector2i wp);

    void handle_input(const sf::Event &e);
    void update(const sf::Time &dt);
    void draw();
private:
    sf::RenderWindow &w;
    sf::View view;

    // TODO multiple levels
    vector<vector<TilePtr>> grid;
    vector<WorkerPtr> workers;

    sf::Text mpos;
};

