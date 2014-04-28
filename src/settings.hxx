#pragma once

#include "lua.hxx"
#include "util.hxx"

class Settings {
public:
    Settings();

    // Load all variables from lua file
    void load_from_file(string path);

    // TODO something prettier?
    bool has_num_setting(string s);
    double get_num_setting(string s);

    bool has_bool_setting(string s);
    bool get_bool_setting(string s);

    bool has_string_setting(string s);
    string get_string_setting(string s);
private:
    LuaState L;

    map<string, double> nums;
    map<string, bool> bools;
    map<string, string> strings;
};

