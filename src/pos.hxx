#pragma once

#include "pos/point.hxx"

// Would like to declare an actual new type, but...
typedef Point<int> TilePos;
typedef Point<float> WindowPos;

template<typename T>
class BasePos {
public:
    BasePos(int _floor) : floor(_floor) { }
    BasePos(Point<T> p, int _floor) : pos(p), floor(_floor) { }
    BasePos(int x, int y, int _floor) : pos(x, y), floor(_floor) { }

    bool operator == (const BasePos &p) const {
        return pos == p.pos && floor == p.floor;
    }
    bool operator != (const BasePos &p) const {
        return !(*this == p);
    }

    string to_string() const {
        return pos.to_string() + " (" + std::to_string(floor) + ")";
    }

    Point<T> pos;
    int floor;
};

typedef BasePos<int> MapPos;
typedef BasePos<float> WorldPos;

