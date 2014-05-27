#pragma once

#include <memory>
using namespace std;

#include "scene/planningobject.hxx"

namespace scene {

    // TODO Handle ground and materials here as well.
    // Create objects of different types.
    class ObjectFactory {
    public:
        ObjectFactory();

        shared_ptr<PlanningObject> create_planning_object(PlanningType o) const;
    private:
        vector<shared_ptr<PlanningObject>> planning_objects;
    };

};

