#pragma once

#include "world/tile.hxx"
#include "pos.hxx"

class Level {
public:
    shared_ptr<Tile> tile(int x, int y); // TODO remove?
    shared_ptr<Tile> tile(const TilePos &p);

    void update(const sf::Time &dt);
    void draw(sf::RenderWindow &w);
    // TODO fix
//private:
    Level();
    //friend make_level(int level);
    vector<vector<shared_ptr<Tile>>> grid;
};

shared_ptr<Level> make_level(int level);

