#pragma once

#include <lua.hpp>
#include <unordered_set>
#include <string>
using namespace std;

// Predefined keys in lua environment. We don't want to treat them as settings.
bool is_predefined_lua_key(string key);

// RAII for lua object
class LuaState {
public:
    LuaState() : L( lua_open() ) {
        luaL_openlibs( L );
    }

    ~LuaState() {
        lua_close( L );
    }
    //implicitly act as a lua_State pointer
    inline operator lua_State*() {
        return L;
    }

protected:
    lua_State *L;
};

