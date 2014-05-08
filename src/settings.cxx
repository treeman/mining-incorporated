#include "settings.hxx"
#include "string.hxx"
#include "locator.hxx"

Settings::Settings() {
}

void Settings::load_from_file(string path) {
    LuaState L;

    L_("Loading settings from file %s\n", path.c_str());
    if (luaL_dofile(L, path.c_str())) {
        const char *err = lua_tostring(L, -1);
        printf("Lua error: %s\n", err);
        return; // TODO fail
    }

    // Go through global table
    lua_getglobal(L, "_G");
    for (lua_pushnil(L); lua_next(L, -2); lua_pop(L, 1)) {
        string key = lua_tostring(L, 2);
        if (is_predefined_lua_key(key)) continue;

        if (lua_isnumber(L, -1)) {
            nums[key].v = (double)lua_tonumber(L, -1);
            L_("  %s = %g\n", key.c_str(), nums[key].v);
        }
        else if (lua_isstring(L, -1)) {
            strings[key].v = lua_tostring(L, -1);
            L_("  %s = %s\n", key.c_str(), strings[key].v.c_str());
        }
        else if (lua_isboolean(L, -1)) {
            bools[key].v = lua_toboolean(L, -1);
            L_("  %s = %s\n", key.c_str(), bools[key].v ? "true" : "false");
        }
        // Skip functions and tables atm.
    }
    lua_pop(L, 1);
    assert(L.stack_size() == 0);
    L_("load done\n");
}

void Settings::set_num(string s, double val) {
    auto it = nums.find(s);
    assert(it != nums.end());
    it->second.v = val;
    for (auto cb : it->second.cbs)
        cb(val);
    for (auto cb : global_cbs)
        cb(s, to_string(val));
}
void Settings::set_bool(string s, bool val) {
    auto it = bools.find(s);
    assert(it != bools.end());
    it->second.v = val;
    for (auto cb : it->second.cbs)
        cb(val);
    for (auto cb : global_cbs)
        cb(s, to_string(val));
}
void Settings::set_string(string s, string val) {
    auto it = strings.find(s);
    assert(it != strings.end());
    it->second.v = val;
    for (auto cb : it->second.cbs)
        cb(val);
    for (auto cb : global_cbs)
        cb(s, val);
}

void Settings::register_num(string s, double val) {
    if (nums.find(s) == nums.end())
        nums[s].v = val;
}
void Settings::register_bool(string s, bool val) {
    if (bools.find(s) == bools.end())
        bools[s].v = val;
}
void Settings::register_string(string s, string val) {
    if (strings.find(s) == strings.end())
        strings[s].v = val;
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

double Settings::get_num(string s) {
    auto it = nums.find(s);
    assert(it != nums.end());
    return it->second.v;
}
bool Settings::get_bool(string s) {
    auto it = bools.find(s);
    assert(it != bools.end());
    return it->second.v;
}
string Settings::get_string(string s) {
    auto it = strings.find(s);
    assert(it != strings.end());
    return it->second.v;
}

