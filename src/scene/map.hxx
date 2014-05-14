#pragma once

#include "scene/floor.hxx"
#include "pos.hxx"

namespace scene {

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

    // TODO encapsulate
    shared_ptr<Map> make_map();

} // Scene

