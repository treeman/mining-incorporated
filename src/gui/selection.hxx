#pragma once

#include "pos.hxx"

// TODO should be able to move selection even outside world border.
// But clamp it to fit.
template<typename T>
struct AreaSelection {
    AreaSelection() : start(-1), end(-1) { }
    AreaSelection(T x, T y) : start(x), end(y) { normalize(); }
    AreaSelection(const AreaSelection &o) : start(o.start), end(o.end) {
        normalize();
    }
    AreaSelection &operator = (const AreaSelection &o) {
        start = o.start;
        end = o.end;
        normalize();
        return *this;
    }

    void normalize() {
        if (start.pos.x > end.pos.x) swap(start.pos.x, end.pos.x);
        if (start.pos.y > end.pos.y) swap(start.pos.y, end.pos.y);
    }

    string to_string() const {
        IPoint s(start.pos), e(end.pos);
        if (s == e)
            return s.to_string();
        else
            return s.to_string() + " - " + e.to_string();
    }

    T start, end;
};

typedef AreaSelection<MapPos> MapSelection;
typedef AreaSelection<WorldPos> WorldSelection;

class World;
MapSelection to_map(World *world, WorldSelection sel);

class Selection {
public:
    Selection();

    WorldSelection get_area() const;

    string to_string() const;

    void begin(const WorldPos &start);
    void extend(const WorldPos &end);
    void clear();
    bool is_active() const;
    bool is_point() const;
private:
    WorldSelection area;
    bool active;
};

