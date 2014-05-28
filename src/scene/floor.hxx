#pragma once

#include "pos.hxx"
#include "scene/tile.hxx"
#include "scene/path.hxx"

namespace scene {

    class Floor {
    public:
        shared_ptr<Tile> tile(const TilePos &p);
        bool in_floor(const TilePos &p) const;

        void update(const sf::Time &dt);
        void draw(sf::RenderWindow &w);
    private:
        Floor(int num);
        friend shared_ptr<Floor> make_first_floor();
        friend shared_ptr<Floor> make_random_floor(int num);

        vector<vector<shared_ptr<Tile>>> grid;
    public:
        Path pathfind(const TilePos &from, const TilePos &to) const;
    private:
        int floor_num;
    };
}

