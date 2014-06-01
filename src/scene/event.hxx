#pragma once

#include "gui/selection.hxx"

namespace scene {

    class PlanningObject;
    class Material;
    class Task;
    class RoomType;
    class ObjectType;

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
        PlacePlanningEvent(shared_ptr<PlanningObject> o, MapArea area);

        string to_string() const override;
        void handle(World *world) override;

        shared_ptr<PlanningObject> obj;
        MapArea area;
    };

    class RemovePlanningEvent : public Event {
    public:
        RemovePlanningEvent(MapArea area);

        string to_string() const override;
        void handle(World *world) override;

        MapArea area;
    };

    class BuildMaterialEvent : public Event {
    public:
        BuildMaterialEvent(shared_ptr<Material> o, MapArea area);

        string to_string() const override;
        void handle(World *world) override;

        shared_ptr<Material> material;
        MapArea area;
    };

    class BuildObjectEvent : public Event {
    public:
        BuildObjectEvent(shared_ptr<ObjectType> o, MapArea area);

        string to_string() const override;
        void handle(World *world) override;

        shared_ptr<ObjectType> obj;
        MapArea area;
    };

    class BuildRoomEvent : public Event {
    public:
        BuildRoomEvent(shared_ptr<RoomType> o, MapArea area);

        string to_string() const override;
        void handle(World *world) override;

        shared_ptr<RoomType> type;
        MapArea area;
    };

    class RemoveRoomEvent : public Event {
    public:
        RemoveRoomEvent(MapArea area);

        string to_string() const override;
        void handle(World *world) override;

        MapArea area;
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
        MineEvent(MapArea area);

        string to_string() const override;
        void handle(World *world) override;

        MapArea area;
    };
}

