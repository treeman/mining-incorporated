#pragma once

#include "scene/planningobject.hxx"

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
        PlanningObjectEvent(shared_ptr<scene::PlanningObject> o);

        string to_string() const;
        shared_ptr<scene::PlanningObject> obj;
    };
}

