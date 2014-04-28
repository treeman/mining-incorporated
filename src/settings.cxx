#include <unordered_set>
#include "settings.hxx"

#include "util.hxx"

// Predefined keys in lua environment. We don't want to treat them as settings.
unordered_set<string> ignored_keys = {
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

Settings::Settings() {
}

void Settings::load_from_file(string path) {
    if (luaL_dofile(L, path.c_str())) {
        const char *err = lua_tostring(L, -1);
        printf("Lua error: %s\n", err);
        return; // TODO fail
    }

    // Go through global table
    lua_getglobal(L, "_G");
    for (lua_pushnil(L); lua_next(L, -2); lua_pop(L, 1)) {
        string key = lua_tostring(L, 2);
        if (ignored_keys.count(key)) continue;

        printf("key: %s\n", key.c_str());
        if (lua_isnumber(L, -1)) {
            nums[key] = (double)lua_tonumber(L, -1);
            printf("  num: %lf\n", nums[key]);
        }
        else if (lua_isstring(L, -1)) {
            strings[key] = lua_tostring(L, -1);
            printf("  num: %s\n", strings[key].c_str());
        }
        else if (lua_isboolean(L, -1)) {
            bools[key] = lua_toboolean(L, -1);
            printf("  bool: %d\n", bools[key]);
        }

    }
}

bool Settings::has_num_setting(string s) {
    return nums.find(s) != nums.end();
}
double Settings::get_num_setting(string s) {
    return nums.find(s)->second;
}
bool Settings::has_bool_setting(string s) {
    return bools.find(s) != bools.end();
}
bool Settings::get_bool_setting(string s) {
    return bools.find(s)->second;
}
bool Settings::has_string_setting(string s) {
    return strings.find(s) != strings.end();
}
string Settings::get_string_setting(string s) {
    return strings.find(s)->second;
}

