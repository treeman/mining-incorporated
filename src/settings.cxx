#include <unordered_set>
#include <cassert>

#include "settings.hxx"
#include "conversions.hxx"
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

        if (lua_isnumber(L, -1)) {
            nums[key].v = (double)lua_tonumber(L, -1);
        }
        else if (lua_isstring(L, -1)) {
            strings[key].v = lua_tostring(L, -1);
        }
        else if (lua_isboolean(L, -1)) {
            bools[key].v = lua_toboolean(L, -1);
        }
        // Skip functions and tables atm.
    }
}

void Settings::set_num_setting(string s, double val) {
    auto it = nums.find(s);
    assert(it != nums.end());
    it->second.v = val;
    for (auto cb : it->second.cbs)
        cb(val);
    for (auto cb : global_cbs)
        cb(s, to_string(val));
}
void Settings::set_bool_setting(string s, bool val) {
    auto it = bools.find(s);
    assert(it != bools.end());
    it->second.v = val;
    for (auto cb : it->second.cbs)
        cb(val);
    for (auto cb : global_cbs)
        cb(s, to_string(val));
}
void Settings::set_string_setting(string s, string val) {
    auto it = strings.find(s);
    assert(it != strings.end());
    it->second.v = val;
    for (auto cb : it->second.cbs)
        cb(val);
    for (auto cb : global_cbs)
        cb(s, val);
}

void Settings::register_global_callback(function<void(string, string)> f) {
    global_cbs.push_back(f);
}

// TODO error reporting instead.
void Settings::register_num_callback(string s, function<void(double)> f) {
    auto it = nums.find(s);
    assert(it != nums.end());
    it->second.cbs.push_back(f);
}
void Settings::register_bool_callback(string s, function<void(bool)> f) {
    auto it = bools.find(s);
    assert(it != bools.end());
    it->second.cbs.push_back(f);
}
void Settings::register_string_callback(string s, function<void(string)> f) {
    auto it = strings.find(s);
    assert(it != strings.end());
    it->second.cbs.push_back(f);
}

double Settings::get_num_setting(string s) {
    auto it = nums.find(s);
    assert(it != nums.end());
    return it->second.v;
}
bool Settings::get_bool_setting(string s) {
    auto it = bools.find(s);
    assert(it != bools.end());
    return it->second.v;
}
string Settings::get_string_setting(string s) {
    auto it = strings.find(s);
    assert(it != strings.end());
    return it->second.v;
}

