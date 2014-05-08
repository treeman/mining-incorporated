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
