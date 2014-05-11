#include <cassert>
#include "ore.hxx"
#include "locator.hxx"
#include "lua.hxx"

Ore::Ore()
{ }

unique_ptr<Tile> Ore::create_tile(int x, int y) const {
    // TODO refactor Tile
    unique_ptr<Tile> tile(new Tile(this));
    tile->set_pos(x, y);
    return move(tile);
}

map<string, shared_ptr<const Ore>> ores;

void load_ore_definitions(string path) {
    L_("Loading ore file %s\n", path);

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

        ores.insert({key, shared_ptr<Ore const>(move(ore))});
    }
    lua_pop(L, 1);

    assert(L.stack_size() == 0);

    L_("found %d ores\n", ores.size());
    for (auto &x : ores) {
        L_("  %s\n", x.first);
    }
}

shared_ptr<const Ore> get_ore(string key) {
    auto it = ores.find(key);
    if (it == ores.end()) {
        throw lua_parse_error(fmt("Could not find ore definition for '%s'", key));
    }
    return it->second;
}

