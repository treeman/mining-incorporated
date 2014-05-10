#pragma once

#include "pos/point.hxx"

// Would like to declare an actual new type, but...
typedef Point<int> TilePos;
typedef Point<float> WindowPos;

template<typename T>
class BasePos {
public:
    BasePos(int _lvl) : lvl(_lvl) { }
    BasePos(int x, int y, int _lvl) : pos(x, y), lvl(_lvl) { }

    bool operator == (const BasePos &p) const {
        return pos == p.pos && lvl == p.lvl;
    }
    bool operator != (const BasePos &p) const {
        return !(*this == p);
    }

    string to_string() const {
        return pos.to_string() + " (" + std::to_string(lvl) + ")";
    }

    TilePos pos;
    int lvl;
};

typedef BasePos<int> DimensionPos;
typedef BasePos<float> WorldPos;

