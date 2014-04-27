#pragma once

#include "util.hxx"

// TODO more!
enum ObjectType {
    Elevator,
    Bed,
};

struct ObjectInfo {
    ObjectType type;
    string name;
    string spr_path;

    // TODO stuff?
};

// Ease of use, heh.
extern map<int, ObjectInfo> object_info;
ObjectInfo *get_info(ObjectType type);

sf::Sprite create_object_sprite(ObjectType type);

