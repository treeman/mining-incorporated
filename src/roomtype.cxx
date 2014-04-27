#include "roomtype.hxx"
#include "butler.hxx"

map<int, RoomInfo> room_info = {
    { Rock, { Rock, "", "rock_tile.png", }, }, // Special!
    { Mine, { Mine, "Mine", "stone_tile.png" } },
    { Baracks, { Baracks, "Baracks", "wood_tile.png" } },
    { Office, { Office, "Office", "marble_tile.png" } },
    { Storage, { Storage, "Storage", "store_tile.png" } },
    { MassHall, { MassHall, "MassHall", "carpet_tile.png" } },
    { Research, { Research, "Research", "star_tile.png" } },
};

RoomInfo *get_info(RoomType type) {
    auto it = room_info.find(type);
    if (it == room_info.end()) {
        printf("Error! Could not find RoomType %d!\n", type);
        exit(-1);
    }
    return &it->second;
}

sf::Sprite create_tile_sprite(RoomType type) {
    auto it = room_info.find(type);
    if (it == room_info.end()) {
        printf("Error type %d not found in build_info!\n", type);
        exit(-1);
    }
    return create_sprite(it->second.spr_path);
}

