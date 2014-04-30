#pragma once

#include "roomtype.hxx"
#include "roomtype.hxx"
#include "objecttype.hxx"

enum TaskType {
    Dig,
    BuildRoom,
    PlaceObject,
    SellTask,
};

class Task {
public:
    Task();
    TaskType type;

    string to_str();

    sf::Vector2i pos;
    bool is_done;
    RoomType room_type;
    ObjectType object_type;
};

Task create_dig_task(int x, int y);
Task create_room_task(int x, int y, RoomType type);
Task create_object_task(int x, int y, ObjectType type);
Task create_sell_task(int x, int y);

