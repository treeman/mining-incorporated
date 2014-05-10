#pragma once

#include "point.hxx"

// Would like to declare an actual new type, but...
typedef Point<int> TilePos;
typedef Point<float> WindowPos;

class DimensionPos {
public:
    DimensionPos(int _lvl) : lvl(_lvl) { }
    DimensionPos(int x, int y, int _lvl) : pos(x, y), lvl(_lvl) { }

    bool operator == (const DimensionPos &p) const {
        return pos == p.pos && lvl == p.lvl;
    }
    bool operator != (const DimensionPos &p) const {
        return !(*this == p);
    }

    TilePos pos;
    int lvl;
};

class WorldPos {
public:
    WorldPos(int _lvl) : lvl(_lvl) { }
    WorldPos(float x, float y, int _lvl) : pos(x, y), lvl(_lvl) { }

    bool operator == (const WorldPos &p) const {
        return pos == p.pos && lvl == p.lvl;
    }
    bool operator != (const WorldPos &p) const {
        return !(*this == p);
    }

    Point<float> pos;
    int lvl;
};

