#include "buildtype.hxx"
#include "butler.hxx"

map<int, BuildInfo> build_info = {
    { Demolish, { Demolish, "Demolish", "rock_tile.png", }, },
    { Corridor, { Corridor, "Corridor", "stone_tile.png" } },
    { Baracks, { Baracks, "Baracks", "wood_tile.png" } },
    { Office, { Office, "Office", "marble_tile.png" } },
    { Storage, { Storage, "Storage", "store_tile.png" } },
    { MassHall, { MassHall, "MassHall", "carpet_tile.png" } },
    { Research, { Research, "Research", "star_tile.png" } },
};

BuildInfo *get_info(BuildType type) {
    auto it = build_info.find(type);
    if (it == build_info.end()) {
        printf("Error! Could not find RoomType %d!\n", type);
        exit(-1);
    }
    return &it->second;
}

sf::Sprite create_tile_sprite(BuildType type) {
    auto it = build_info.find(type);
    if (it == build_info.end()) {
        printf("Error type %d not found in build_info!\n", type);
        exit(-1);
    }
    return create_sprite(it->second.spr_path);
}

