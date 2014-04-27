#include "roomtype.hxx"
#include "butler.hxx"

    float remove_time;
    float build_time;
RoomInfo::RoomInfo(RoomType t) : type(t), cost(0), can_build(false), is_ore(false),
    remove_time(0), build_time(0), min_ores(0), max_ores(0), money_per_ore(0)
{ }

map<int, RoomInfo> room_info;

void add_buildable_room(RoomType type, string name, string spr, int cost) {
    RoomInfo info(type);
    info.name = name;
    info.spr_path = spr;
    info.cost = cost;
    info.can_build = true;
    info.is_walkable = true;
    // TODO fix.
    //info.build_time = 0.5;
    info.build_time = 0.1;

    room_info.insert(make_pair(type, info));
}

void add_ore(RoomType type, string spr, float mining_time, int least, int most, int val) {
    RoomInfo info(type);
    info.is_ore = true;
    info.spr_path = spr;
    info.is_walkable = false;
    info.min_ores = least;
    info.max_ores = most;
    info.money_per_ore = val;
    //info.remove_time = mining_time;
    // TODO fix. Just for checking
    info.remove_time = mining_time / 20;

    room_info.insert(make_pair(type, info));
}

void init_rooms() {
    // Special
    RoomInfo rock(Rock);
    rock.spr_path = "rock_tile.png";
    rock.is_walkable = false;
    //rock.remove_time = 1;
    rock.remove_time = 0.2;
    room_info.insert(make_pair(Rock, rock));

    add_buildable_room(Mine, "Mine", "stone_tile.png", 0);
    add_buildable_room(Baracks, "Baracks", "wood_tile.png", 10);
    add_buildable_room(Office, "Office", "marble_tile.png", 10);
    add_buildable_room(Storage, "Storage", "store_tile.png", 10);
    add_buildable_room(MassHall, "MassHall", "carpet_tile.png", 10);
    add_buildable_room(Research, "Research", "star_tile.png", 40);

    // Should change from room to.. .something
    add_ore(AluminiumOre, "aluminium_ore.png", 2, 2, 3, 5);
    add_ore(CoalOre, "coal_ore.png", 1, 3, 6, 2);
    add_ore(CopperOre, "copper_ore.png", 4, 2, 3, 10);
    add_ore(DiamondOre, "diamond_ore.png", 15, 1, 3, 100);
    add_ore(GoldOre, "gold_ore.png", 10, 1, 2, 80);
    add_ore(IronOre, "iron_ore.png", 6, 1, 7, 10);
}

RoomInfo *get_info(RoomType type) {
    auto it = room_info.find(type);
    if (it == room_info.end()) {
        printf("Error! Could not find RoomType %d!\n", type);
        return NULL;
    }
    return &it->second;
}

sf::Sprite create_tile_sprite(RoomType type) {
    auto it = room_info.find(type);
    if (it == room_info.end()) {
        printf("Error type %d not found in build_info!\n", type);
        return sf::Sprite();
    }
    return create_sprite(it->second.spr_path);
}

