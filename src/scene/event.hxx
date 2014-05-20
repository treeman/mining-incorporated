#pragma once

#include "gui/selection.hxx"

namespace scene {

    class PlanningObject;
    class Material;
    class Task;

    // Use built-in type system for switch case.
    // Testing out how it works.
    class Event {
    public:
        virtual ~Event() = default;

        virtual string to_string() const = 0;
    };

    class PlacePlanningEvent : public Event {
    public:
        PlacePlanningEvent(shared_ptr<PlanningObject> o, gui::MapSelection area);

        string to_string() const override;

        shared_ptr<PlanningObject> obj;
        gui::MapSelection area;
    };

    class RemovePlanningEvent : public Event {
    public:
        RemovePlanningEvent(gui::MapSelection area);

        string to_string() const override;

        gui::MapSelection area;
    };

    class BuildMaterialEvent : public Event {
    public:
        BuildMaterialEvent(shared_ptr<Material> o, gui::MapSelection area);

        string to_string() const override;

        shared_ptr<Material> material;
        gui::MapSelection area;
    };

    class TaskDoneEvent : public Event {
    public:
        TaskDoneEvent(shared_ptr<Task> o);

        string to_string() const override;

        shared_ptr<Task> task;
    };
}

