#pragma once

#include "tile.hxx"

class Level {
public:
    shared_ptr<Tile> tile(int x, int y);

    void update(const sf::Time &dt);
    void draw(sf::RenderWindow &w);
//private:
    Level();
    //friend make_level(int level);
    vector<vector<shared_ptr<Tile>>> grid;
};

shared_ptr<Level> make_level(int level);

