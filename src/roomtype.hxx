#pragma once

#include "util.hxx"

// TODO
// Shall only build when everything is mined out!!
// Cannot build on Stone Tiles... Must mine them out first.
enum RoomType {
    Rock, // Also serves as unpassable
    Mine, // Serves as a corridor
    Baracks, // So we can hire more workers
    Office,  // Unlock other things?
    Storage, // Store goodies!!
    MassHall, // Eat?
    Research, // Unlock new things?

    // If time
    // Hygien, // only maybe!
    // Deliveries,
    // Garbage,
};

struct RoomInfo {
    RoomType type;
    string name;
    string spr_path;

    // TODO
    // bool walkable;
    // int build_cost;
};

// Ease of use, heh.
extern map<int, RoomInfo> room_info;
RoomInfo *get_info(RoomType type);

sf::Sprite create_tile_sprite(RoomType type);

