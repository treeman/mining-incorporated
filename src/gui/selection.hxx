#pragma once

#include "pos.hxx"

struct SelectionArea {
    SelectionArea();

    WorldPos start, end;
};

class Selection {
public:
    Selection();

    void begin(const WorldPos &start);
    void extend(const WorldPos &end);
    void clear();
    bool is_active() const;
    bool is_point() const;
private:
    SelectionArea area;
    bool active;
};

