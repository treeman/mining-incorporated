#pragma once

#include "roomtype.hxx"
#include "objecttype.hxx"
#include "pos.hxx"

// A task is something for workers to do,
// verified by the world so it works.
namespace scene {

    // TODO
    // rework
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

        string to_string() const;

        IPoint pos;
        bool is_done;
        RoomType room_type;
        ObjectType object_type;
    };

    Task create_dig_task(int x, int y);
    Task create_room_task(int x, int y, RoomType type);
    Task create_object_task(int x, int y, ObjectType type);
    Task create_sell_task(int x, int y);

} // Scene
