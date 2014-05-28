#pragma once

#include "std.hxx"
#include "scene/planningobject.hxx"
#include "scene/ground.hxx"

namespace scene {

    // Create objects of different types.
    class ObjectFactory {
    public:
        ObjectFactory();

        shared_ptr<PlanningObject> create_planning_object(PlanningType o) const;
        const Ground *get_ground(string key) const;
    private:
        void init_planning_objects();
        vector<shared_ptr<PlanningObject>> planning_objects;

        // Persistent things.
        void load_ground_definitions(string path);
        void load_ore_definitions(string path);
        map<string, shared_ptr<Ground>> grounds;
    };

};

