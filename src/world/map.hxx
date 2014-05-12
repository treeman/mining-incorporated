#pragma once

#include "world/floor.hxx"
#include "pos.hxx"

class Map {
public:
    shared_ptr<Tile> tile(const MapPos &p) const;
    shared_ptr<Tile> tile(int x, int y, int floor) const; // TODO remove?
    shared_ptr<Floor> floor(int floor) const;

    int num_floors() const;

    void update(const sf::Time &dt);
    void draw(sf::RenderWindow &w, int floor);
//private:
    Map();
    vector<shared_ptr<Floor>> floors;
};

shared_ptr<Map> make_map();

