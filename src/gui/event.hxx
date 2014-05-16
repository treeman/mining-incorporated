#pragma once

#include "scene/planningobject.hxx"
#include "scene/material.hxx"

namespace gui {

    // buttons and similar -> gui states.
    class Event {
    public:
        virtual ~Event() = default;

        virtual string to_string() const = 0;
    };

    // Choose a planning object.
    class PlanningObjectEvent : public Event {
    public:
        PlanningObjectEvent(shared_ptr<scene::PlanningObject> o) : obj(o) { }

        string to_string() const {
            return obj->to_string() + " Planning";
        }

        shared_ptr<scene::PlanningObject> obj;
    };

    // Choose ground material.
    class GroundMaterialObjectEvent : public Event {
    public:
        GroundMaterialObjectEvent(shared_ptr<scene::Material> o) : obj(o) { }

        string to_string() const {
            return obj->to_string();
        }

        shared_ptr<scene::Material> obj;
    };
}

