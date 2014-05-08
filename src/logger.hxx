#pragma once

#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>
using namespace std;

#include "safe_printf.hxx"

class Logger {
public:
    virtual ~Logger() { }

    // TODO
    // cannot chain << endl!
    // c++ style
    template<typename T>
    Logger &operator << (T v) {
        stringstream ss;
        ss << v;
        write(ss.str());
        return *this;
    }

    template<typename... Ts>
    void operator()(const char *f, const Ts&... ts)
    {
        // TODO make type safe later.
        //check_printf(f, normalizeArg(ts)...);

        safe_printf(f, ts...);
        //char buf[4048];
        //snprintf(buf, 4048, f, ts...);
        //write(buf);
    }
private:
    virtual void write(string s) = 0;
};

