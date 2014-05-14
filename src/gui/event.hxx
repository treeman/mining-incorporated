#pragma once

#include "world/planningobject.hxx"

namespace Gui {

    class Event {
    public:
        virtual ~Event() = default;

        virtual string to_string() const = 0;
    };

    // Choose a planning object.
    class PlanningObjectEvent : public Event {
    public:
        PlanningObjectEvent(shared_ptr<PlanningObject> o);

        string to_string() const;
        shared_ptr<PlanningObject> obj;
    };
}

