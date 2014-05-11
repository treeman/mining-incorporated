#pragma once

#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>
using namespace std;

#include "util/fmt.hxx"

class Logger {
public:
    virtual ~Logger() { }

    // c++ style
    template<typename T>
    Logger &operator << (T v) {
        stringstream ss;
        ss << v;
        write(ss.str());
        return *this;
    }

    // printf with type checking.
    template<typename... Ts>
    void operator()(string f, const Ts&... ts)
    {
        write(fmt(f.c_str(), ts...));
    }
    template<typename... Ts>
    void operator()(const char *f, const Ts&... ts)
    {
        write(fmt(f, ts...));
    }
private:
    virtual void write(string s) = 0;
};

