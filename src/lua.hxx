#pragma once

#include <stdexcept>
#include <unordered_set>
#include <string>
using namespace std;

#include <lua.hpp>
#include "util/fmt.hxx"

// Predefined keys in lua environment. We don't want to treat them as settings.
bool is_predefined_lua_key(string key);

// RAII for lua object
class LuaState {
public:
    LuaState();
    ~LuaState();

    // Implicitly act as a lua_State pointer
    operator lua_State*() { return L; }

    // TODO
    // move outside!!
    void dofile(string path);

    // Getters with exception on failure
    string require_string(string key, string err);
    double require_num(string key, string err);
    bool require_bool(string key, string err);

    //bool get_string(string key, string &res) noexcept;
    //bool get_num(string key, double &res) noexcept;
    //bool get_bool(string key, bool &res) noexcept;

    void dump_stack();
    int stack_size() const;
private:
    lua_State *L;
    string path;
};

// TODO take lua_State *L
void print_table(LuaState &L);

class lua_parse_error : public logic_error {
public:
    lua_parse_error(const char *s) noexcept : logic_error(s) { }
    lua_parse_error(const string &s) noexcept : logic_error(s) { }
    lua_parse_error(const string &path, const char *err) noexcept :
        logic_error(fmt("Error parsing file '%s': %s", path, err)) { }
    lua_parse_error(const string &path, const string &err) noexcept :
        logic_error(fmt("Error parsing file '%s': %s", path, err)) { }
};

