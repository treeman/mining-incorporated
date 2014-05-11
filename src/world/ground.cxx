#include <cassert>
#include "ground.hxx"
#include "locator.hxx"
#include "lua.hxx"
#include "abort.hxx"

Ground::Ground() : is_walkable(false), remove_time(0), build_time(0)
{ }

unique_ptr<Tile> Ground::create_tile(int x, int y) const {
    // TODO refactor Tile
    unique_ptr<Tile> tile(new Tile(this));
    tile->set_pos(x, y);
    return move(tile);
}


map<string, shared_ptr<const Ground>> grounds;

void load_ground_definitions(string path) {
    L_("Loading ground file %s\n", path);

    LuaState L;

    if (luaL_dofile(L, path.c_str())) {
        const char *err = lua_tostring(L, -1);
        throw lua_parse_error(path, err);
    }

    // Go through global table
    //lua_getglobal(L, "ground");
    //print_table(L);
    //lua_pop(L, 1);

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

        grounds.insert({key, shared_ptr<Ground const>(move(ground))});
    }
    lua_pop(L, 1);

    assert(L.stack_size() == 0);

    L_("found %d grounds\n", grounds.size());
    for (auto &x : grounds) {
        L_("  %s\n", x.second->key);
    }
}

shared_ptr<const Ground> get_ground(string key) {
    auto it = grounds.find(key);
    if (it == grounds.end()) {
        throw lua_parse_error(fmt("Could not find ground definition for '%s'", key));
    }
    return it->second;
}

