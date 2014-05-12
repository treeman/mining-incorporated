#pragma once

#include "world/tile.hxx"
#include "pos.hxx"

class Floor {
public:
    shared_ptr<Tile> tile(int x, int y); // TODO remove?
    shared_ptr<Tile> tile(const TilePos &p);

    void update(const sf::Time &dt);
    void draw(sf::RenderWindow &w);
    // TODO fix
//private:
    Floor();
    //friend make_level(int level);
    vector<vector<shared_ptr<Tile>>> grid;
};

shared_ptr<Floor> make_floor(int floor);

