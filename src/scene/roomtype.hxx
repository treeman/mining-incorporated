#pragma once

#include "std.hxx"

namespace scene {

    struct RoomType {
        string name;

        string to_string() const { return "Roomtype " + name; }

        bool operator == (const RoomType &t) const {
            return name == t.name;
        }
        bool operator != (const RoomType &t) const {
            return !(*this == t);
        }
    };
}

