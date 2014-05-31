#pragma once

#include "std.hxx"

namespace scene {

    struct ObjectType {
        string name;
        string spr;
        int cost;

        string to_string() const { return name; }

        bool operator == (const RoomType &t) const {
            return name == t.name;
        }
        bool operator != (const RoomType &t) const {
            return !(*this == t);
        }
    };
}

