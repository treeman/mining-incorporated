#pragma once

#include "pos.hxx"
#include "scene/tile.hxx"
#include "scene/path.hxx"

namespace scene {

    class Floor {
    public:
        shared_ptr<Tile> tile(int x, int y); // TODO remove?
        shared_ptr<Tile> tile(const TilePos &p);
        bool in_floor(const TilePos &p) const;

        void update(const sf::Time &dt);
        void draw(sf::RenderWindow &w);
        // TODO fix
    //private:
        friend shared_ptr<Floor> make_floor(int floor);
        Floor(int num);
        vector<vector<shared_ptr<Tile>>> grid;

    public:
        Path pathfind(const TilePos &from, const TilePos &to) const;
    private:
        int floor_num;
    };

    shared_ptr<Floor> make_floor(int floor);

}

