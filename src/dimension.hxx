#pragma once

#include "level.hxx"

class Dimension {
public:
    shared_ptr<Tile> tile(int x, int y, int lvl) const;
    shared_ptr<Level> level(int lvl) const;

    int num_levels() const;

    void update(const sf::Time &dt);
    void draw(sf::RenderWindow &w, int lvl);
//private:
    Dimension();
    vector<shared_ptr<Level>> levels;
};

shared_ptr<Dimension> make_dimension();

