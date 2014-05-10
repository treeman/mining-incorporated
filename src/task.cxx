#include "task.hxx"

// Hate this
string to_str(TaskType type) {
    switch (type) {
        case Dig: return "Dig";
        case BuildRoom: return "BuildRoom";
        case PlaceObject: return "PlaceObject";
        case SellTask: return "SellTask";
        default: return "unknown";
    }
}

Task::Task() : is_done(false) {

}

string Task::to_str() {
    stringstream ss;
    if (type == Dig) {
        ss << "Dig " << pos;
    }
    else if (type == BuildRoom) {
        ss << "Build room " << room_type << " at " << pos;
    }
    else if (type == PlaceObject) {
        ss << "Place object " << object_type << " at " << pos;
    }
    else if (type == SellTask) {
        ss << "Sell object " << pos;
    }
    else {
        ss << "Unknown task";
    }
    return ss.str();
}

Task create_dig_task(int x, int y) {
    Task task;
    task.type = Dig;
    task.pos = IPoint(x, y);

    return task;
}
Task create_room_task(int x, int y, RoomType type) {
    Task task;
    task.type = BuildRoom;
    task.pos = IPoint(x, y);
    task.room_type = type;

    return task;
}
Task create_object_task(int x, int y, ObjectType type) {
    Task task;
    task.type = PlaceObject;
    task.pos = IPoint(x, y);
    task.object_type = type;

    return task;
}
Task create_sell_task(int x, int y) {
    Task task;
    task.type = SellTask;
    task.pos = IPoint(x, y);

    return task;
}

