#include <cassert>
#include "ground.hxx"
#include "locator.hxx"
#include "lua.hxx"

// TODO cannot handle plain arrays
// table entries without keys fails.
void print_table(LuaState &L) {
    //L.dump_stack();
    for (lua_pushnil(L); lua_next(L, -2); lua_pop(L, 1)) {
        // If array of numbers, not sure how to treat it.
        if (lua_isnumber(L, -2)) {
            //L_ << "skipping\n";
            //L.dump_stack();
            continue;
        }

        string key = lua_tostring(L, -2);
        if (is_predefined_lua_key(key)) continue;

        //L.dump_stack();

        if (lua_isnumber(L, -1)) {
            L_ << key << ": " << (double)lua_tonumber(L, -1) << '\n';
        }
        else if (lua_isstring(L, -1)) {
            L_ << key << ": " << lua_tostring(L, -1) << '\n';
        }
        else if (lua_isboolean(L, -1)) {
            L_ << key << ": " << lua_toboolean(L, -1) << '\n';
        }
        else if (lua_istable(L, -1)) {
            //L_ << "going through table " << key << '\n';
            print_table(L);
        }
        else {
            L_ << "unknown\n";
        }
        // Skip functions and tables atm.
    }
}

void load_ground_definitions(string path) {
    L_("Loading ground file %s\n", path.c_str());

    LuaState L;

    if (luaL_dofile(L, path.c_str())) {
        const char *err = lua_tostring(L, -1);
        printf("Lua error: %s\n", err);
        return; // TODO fail
    }

    // Go through global table
    lua_getglobal(L, "_G");
    print_table(L);
    lua_pop(L, 1);
    assert(L.stack_size() == 0);
}

