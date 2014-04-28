#pragma once

#include <lua.hpp>

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

