#pragma once

#include "std.hxx"

namespace scene {

    struct RoomType {
        string name;

        string to_string() const { return "Roomtype " + name; }
    };
}

