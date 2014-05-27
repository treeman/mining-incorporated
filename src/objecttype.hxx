#pragma once

#include "std.hxx"

// TODO more!
enum ObjectType {
    SellObject, // Special ;)
    Elevator,
    Bed,
};

struct ObjectInfo {
    ObjectType type;
    string name;
    string spr_path;
    int cost;

    // TODO stuff?
};

// Ease of use, heh.
extern map<int, ObjectInfo> object_info;
ObjectInfo *get_info(ObjectType type);

sf::Sprite create_object_sprite(ObjectType type);

