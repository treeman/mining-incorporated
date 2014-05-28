#pragma once

#include "gui/selection.hxx"

namespace scene {

    class PlanningObject;
    class Material;
    class Task;
    class RoomType;

    // Use built-in type system for switch case.
    // Testing out how it works.
    class Event {
    public:
        virtual ~Event() = default;

        virtual string to_string() const = 0;

        // World will call this whenever the event has rached the world.
        virtual void handle(World *world) = 0;
    };

    class PlacePlanningEvent : public Event {
    public:
        PlacePlanningEvent(shared_ptr<PlanningObject> o, gui::MapSelection area);

        string to_string() const override;
        void handle(World *world) override;

        shared_ptr<PlanningObject> obj;
        gui::MapSelection area;
    };

    class RemovePlanningEvent : public Event {
    public:
        RemovePlanningEvent(gui::MapSelection area);

        string to_string() const override;
        void handle(World *world) override;

        gui::MapSelection area;
    };

    class BuildMaterialEvent : public Event {
    public:
        BuildMaterialEvent(shared_ptr<Material> o, gui::MapSelection area);

        string to_string() const override;
        void handle(World *world) override;

        shared_ptr<Material> material;
        gui::MapSelection area;
    };

    class BuildRoomEvent : public Event {
    public:
        BuildRoomEvent(shared_ptr<RoomType> o, gui::MapSelection area);

        string to_string() const override;
        void handle(World *world) override;

        shared_ptr<RoomType> type;
        gui::MapSelection area;
    };

    class TaskDoneEvent : public Event {
    public:
        TaskDoneEvent(shared_ptr<Task> o);

        string to_string() const override;
        void handle(World *world) override;

        shared_ptr<Task> task;
    };

    class MineEvent : public Event {
    public:
        MineEvent(gui::MapSelection area);

        string to_string() const override;
        void handle(World *world) override;

        gui::MapSelection area;
    };
}

