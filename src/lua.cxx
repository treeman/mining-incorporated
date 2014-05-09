#include "lua.hxx"
#include "locator.hxx"

unordered_set<string> lua_ignored_keys = {
    "string",
    "xpcall",
    "package",
    "tostring",
    "print",
    "os",
    "unpack",
    "require",
    "getfenv",
    "setmetatable",
    "next",
    "assert",
    "tonumber",
    "io",
    "rawequal",
    "collectgarbage",
    "getmetatable",
    "module",
    "rawset",
    "math",
    "debug",
    "pcall",
    "table",
    "newproxy",
    "type",
    "coroutine",
    "_G",
    "select",
    "gcinfo",
    "pairs",
    "rawget",
    "loadstring",
    "ipairs",
    "_VERSION",
    "dofile",
    "setfenv",
    "load",
    "error",
    "loadfile",
};

bool is_predefined_lua_key(string key) {
    return lua_ignored_keys.find(key) != lua_ignored_keys.end();
}

LuaState::LuaState() : L( lua_open() ) {
    luaL_openlibs( L );
}

LuaState::~LuaState() {
    lua_close( L );
}

void LuaState::dump_stack() {
    const int top = lua_gettop(L);
    L_("lua stack (%d)\n", top);

    for (int i = 1; i <= top; i++) {
        const int t = lua_type(L, i);
        L_("   %d %d: ", i, -(top - i + 1));
        switch (t) {
            case LUA_TSTRING:
                L_("'%s'\n", lua_tostring(L, i));
                break;
            case LUA_TBOOLEAN:
                L_("%s\n", lua_toboolean(L, i) ? "true" : "false");
                break;
            case LUA_TNUMBER:
                L_("%g\n", lua_tonumber(L, i));
                break;
            default:
                L_("%s\n", lua_typename(L, t));
                break;
        }
    }
}

int LuaState::stack_size() const { return lua_gettop(L); }

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

        L.dump_stack();

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
