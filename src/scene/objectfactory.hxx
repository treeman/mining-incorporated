#pragma once

#include "std.hxx"
#include "scene/planningobject.hxx"
#include "scene/ground.hxx"
#include "scene/map.hxx"
#include "scene/objecttype.hxx"

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

        void load_ground_definitions(string path);
        void load_ore_definitions(string path);
        map<string, shared_ptr<Ground>> grounds;
    public:
        shared_ptr<Map> make_map() const;

        const ObjectType *get_object_type(string key) const;
        vector<const ObjectType*> get_buildable_objects() const;
    private:
        void load_object_definitions(string path);
        map<string, shared_ptr<ObjectType>> objects;
    };

};

