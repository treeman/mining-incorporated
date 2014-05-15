#pragma once

#include "gui/selection.hxx"
#include "scene/planningobject.hxx"

namespace scene {

    // Use built-in type system for switch case.
    // Testing out how it works.
    class Command {
    public:
        virtual ~Command() = default;

        virtual string to_string() const = 0;
    };

    class PlacePlanningCommand : public Command {
    public:
        PlacePlanningCommand(shared_ptr<PlanningObject> o, gui::MapSelection area);

        string to_string() const override;

        shared_ptr<PlanningObject> obj;
        gui::MapSelection area;
    };

    class RemovePlanningCommand : public Command {
    public:
        RemovePlanningCommand(gui::MapSelection area);

        string to_string() const override;

        gui::MapSelection area;
    };

}

