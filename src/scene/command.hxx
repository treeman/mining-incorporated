#pragma once

#include "gui/selection.hxx"
#include "scene/planningobject.hxx"
#include "scene/material.hxx"

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

    class BuildMaterialCommand : public Command {
    public:
        BuildMaterialCommand(shared_ptr<Material> o, gui::MapSelection area);

        string to_string() const override;

        shared_ptr<Material> material;
        gui::MapSelection area;
    };

}

