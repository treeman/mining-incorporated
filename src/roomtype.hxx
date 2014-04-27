#pragma once

#include "util.hxx"

// TODO
// Shall only build when everything is mined out!!
// Cannot build on Stone Tiles... Must mine them out first.
enum RoomType {
    Demolish, // Also serves as unpassable
    Baracks, // So we can hire more workers
    Office,  // Unlock other things?
    Storage, // Store goodies!!

    // TODO
    Corridor, // Connections. Need to start with a few on the top layer.
    MassHall,
    Research,

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