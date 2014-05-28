#include "lua.hxx"
#include "log.hxx"
#include "scene/objectfactory.hxx"
#include "scene/ore.hxx"

namespace scene {

ObjectFactory::ObjectFactory() {
    init_planning_objects();
    load_ground_definitions("ground.lua");
    load_ore_definitions("ore.lua");
}

shared_ptr<PlanningObject> ObjectFactory::create_planning_object(PlanningType o) const {
    unsigned x = static_cast<unsigned>(o);
    assert(x < planning_objects.size());
    assert(planning_objects[x] != nullptr);
    shared_ptr<PlanningObject> res(new PlanningObject(*planning_objects[x].get()));
    return move(res);
}
const Ground *ObjectFactory::get_ground(string key) const {
    auto it = grounds.find(key);
    if (it == grounds.end()) {
        throw lua_parse_error(fmt("Could not find ground definition for '%s'", key));
    }
    return it->second.get();
}

void ObjectFactory::init_planning_objects() {
    // TODO load from lua
    // Maybe cleanup?
    auto col = sf::Color(255, 255, 255, 100);
    planning_objects.resize(static_cast<unsigned>(PlanningType::NUM_OBJECTS));
    planning_objects[static_cast<unsigned>(PlanningType::ROOM)].reset(
        new PlanningObject("room_preview.png", PlanningType::ROOM, col));
    planning_objects[static_cast<unsigned>(PlanningType::OBJECT)].reset(
        new PlanningObject("object_preview.png", PlanningType::OBJECT, col));
}

void ObjectFactory::load_ground_definitions(string path) {
    LuaState L;
    L.dofile(path);

    vector<shared_ptr<Ground>> found;

    // Find definitions inside 'ground' table.
    lua_getglobal(L, "ground");
    for (lua_pushnil(L); lua_next(L, -2); lua_pop(L, 1)) {
        shared_ptr<Ground> ground(new Ground());

        string key = lua_tostring(L, -2);
        //L_ << key << '\n';
        //L.dump_stack();
        if (!lua_istable(L, -1))
            throw lua_parse_error(path, fmt("ground %s not a table.", key));
        ground->key = key;

        // TODO create functions for these?
        // or just use these raw?
        lua_pushstring(L, "sprite");
        lua_gettable(L, -2);
        if (!lua_isstring(L, -1)) {
            throw lua_parse_error(path, fmt("%s missing sprite.", key));
        }
        ground->spr = lua_tostring(L, -1);
        //L_ << "  sprite: " << ground->spr << '\n';
        lua_pop(L, 1);

        lua_pushstring(L, "remove_time");
        lua_gettable(L, -2);
        if (lua_isnumber(L, -1)) {
            ground->remove_time = (float)lua_tonumber(L, -1);
            //L_("  remove_time: %f\n", ground->remove_time);
        }
        lua_pop(L, 1);

        lua_pushstring(L, "build_time");
        lua_gettable(L, -2);
        if (lua_isnumber(L, -1)) {
            ground->build_time = (float)lua_tonumber(L, -1);
            //L_("  build_time: %f\n", ground->build_time);
        }
        lua_pop(L, 1);

        lua_pushstring(L, "walkable");
        lua_gettable(L, -2);
        if (lua_isboolean(L, -1)) {
            ground->is_walkable = lua_toboolean(L, -1);
            //L_("  walkable: %s\n", to_string(ground->is_walkable));
        }
        lua_pop(L, 1);

        grounds.insert({key, ground});
        found.push_back(ground);
    }
    lua_pop(L, 1);

    assert(L.stack_size() == 0);

    L_("found %d grounds\n", found.size());
    for (auto x : found) {
        L_("  %s\n", x->key);
    }
}

void ObjectFactory::load_ore_definitions(string path) {
    LuaState L;
    L.dofile(path);

    vector<shared_ptr<Ore>> found;

    // Find definitions inside 'ground' table.
    lua_getglobal(L, "ore");
    for (lua_pushnil(L); lua_next(L, -2); lua_pop(L, 1)) {
        shared_ptr<Ore> ore(new Ore());

        string key = lua_tostring(L, -2);
        //L_ << key << '\n';
        //L.dump_stack();
        if (!lua_istable(L, -1))
            throw lua_parse_error(path, fmt("ore %s not a table.", key));
        ore->key = key;

        // TODO create functions for these?
        // or just use these raw?
        lua_pushstring(L, "sprite");
        lua_gettable(L, -2);
        if (!lua_isstring(L, -1)) {
            throw lua_parse_error(path, fmt("%s missing sprite.", key));
        }
        ore->spr = lua_tostring(L, -1);
        //L_ << "  sprite: " << ore->spr << '\n';
        lua_pop(L, 1);

        lua_pushstring(L, "remove_time");
        lua_gettable(L, -2);
        if (lua_isnumber(L, -1)) {
            ore->remove_time = (float)lua_tonumber(L, -1);
            //L_("  remove_time: %f\n", ore->remove_time);
        }
        lua_pop(L, 1);

        lua_pushstring(L, "build_time");
        lua_gettable(L, -2);
        if (lua_isnumber(L, -1)) {
            ore->build_time = (float)lua_tonumber(L, -1);
            //L_("  build_time: %f\n", ore->build_time);
        }
        lua_pop(L, 1);

        lua_pushstring(L, "walkable");
        lua_gettable(L, -2);
        if (lua_isboolean(L, -1)) {
            ore->is_walkable = lua_toboolean(L, -1);
            //L_("  walkable: %s\n", to_string(ore->is_walkable));
        }
        lua_pop(L, 1);

        grounds.insert({key, ore});
        found.push_back(ore);
        //ores.insert({key, shared_ptr<Ground>(move(ore))});
    }
    lua_pop(L, 1);

    assert(L.stack_size() == 0);

    L_("found %d ores\n", found.size());
    for (auto x : found) {
        L_("  %s\n", x->key);
    }
}

};

