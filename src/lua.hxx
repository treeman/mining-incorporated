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
    LuaState();
    ~LuaState();

    // Implicitly act as a lua_State pointer
    operator lua_State*() { return L; }


    void dump_stack();
    int stack_size() const;
protected:
    lua_State *L;
};

