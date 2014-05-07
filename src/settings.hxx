#pragma once

#include "basicincludes.hxx"
#include "lua.hxx"

class Settings {
public:
    Settings();

    // Load all variables from lua file
    void load_from_file(string path);

    // TODO something prettier?
    double get_num(string s);
    bool get_bool(string s);
    string get_string(string s);

    void set_num(string s, double val);
    void set_bool(string s, bool val);
    void set_string(string s, string val);

    // Only if no existing setting.
    void register_num(string s, double val);
    void register_bool(string s, bool val);
    void register_string(string s, string val);

    // When things are changing
    void register_global_callback(function<void(string, string)> f);
    void register_num_callback(string s, function<void(double)> f);
    void register_bool_callback(string s, function<void(bool)> f);
    void register_string_callback(string s, function<void(string)> f);
private:
    LuaState L;

    template<typename T>
    struct Type {
        T v;
        vector<function<void(T)>> cbs;
    };

    map<string, Type<double>> nums;
    map<string, Type<bool>> bools;
    map<string, Type<string>> strings;

    vector<function<void(string, string)>> global_cbs;
};

