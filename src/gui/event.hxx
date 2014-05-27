#pragma once

#include "scene/planningobject.hxx"
#include "scene/material.hxx"
#include "scene/roomtype.hxx"

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

    // Choose room to build.
    class RoomTypeEvent : public Event {
    public:
        RoomTypeEvent(shared_ptr<scene::RoomType> o) : obj(o) { }

        string to_string() const {
            return obj->name;
        }

        shared_ptr<scene::RoomType> obj;
    };
}

