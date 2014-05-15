#pragma once

#include <memory>
using namespace std;

#include "scene/planningobject.hxx"

namespace scene {

    // Create objects of different types.
    class ObjectFactory {
    public:
        ObjectFactory();

        shared_ptr<PlanningObject> create_planning_object(PlanningType o) const;
    private:
        vector<shared_ptr<PlanningObject>> planning_objects;
    };

};

