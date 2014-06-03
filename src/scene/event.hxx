#pragma once

#include "gui/selection.hxx"

namespace scene {

    class PlanningObject;
    class Material;
    class Task;
    class RoomType;
    class ObjectType;

    class Event {
    public:
        virtual ~Event() { }

        virtual string to_string() const = 0;

        // World will call this whenever the event has rached the world.
        virtual void handle(World *world) = 0;
    };

    class HandleEvent : public Event {
    public:
        HandleEvent(function<void(World *world)> handle, string to_string);

        string to_string() const override;
        void handle(World *world) override;
    private:
        function<void(World *world)> h;
        string str;
    };
}

