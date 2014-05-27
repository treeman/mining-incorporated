#pragma once

#include "std.hxx"

enum RoomType {
    Rock, // Also serves as unpassable
    Mine, // Serves as a corridor
    Baracks, // So we can hire more workers
    Office,  // Unlock other things?
    Storage, // Store goodies!!
    MassHall, // Eat?
    Research, // Unlock new things?

    // Epic Hack but hey
    AluminiumOre,
    CoalOre,
    CopperOre,
    DiamondOre,
    GoldOre,
    IronOre,

    // If time
    // Hygien, // only maybe!
    // Deliveries,
    // Garbage,
};

struct RoomInfo {
    RoomInfo(RoomType t);

    RoomType type;
    string name;
    string spr_path;
    int cost;
    bool can_build;
    bool is_ore;
    bool is_walkable;
    float remove_time;
    float build_time;

    int min_ores, max_ores;
    int money_per_ore; // Could make something more advanced.
};

// Ease of use, heh.
extern map<int, RoomInfo> room_info;
void init_rooms();
RoomInfo *get_info(RoomType type);

sf::Sprite create_tile_sprite(RoomType type);

