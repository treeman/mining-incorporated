#pragma once

#include <iostream>
#include <stdexcept>
#include <cassert>
using namespace std;

namespace safe_fmt {
    void check_printf(const char *f);

    class fmt_error : public logic_error {
    public:
        fmt_error(const char *s) noexcept : logic_error(s) { }
        fmt_error(const string &s) noexcept : logic_error(s) { }
    };

    // TODO better error reporting? Or something?
    // Use asserts here as it's a bit hard to report type names during runtime.
    template<class T, typename... Ts>
    void check_printf(const char *f, const T &t, const Ts&... ts) {
        for (; *f; ++f) {
            if (*f != '%' || *++f == '%') continue;
            switch (*f) {
                case 'f':
                case 'g':
                    assert(is_floating_point<T>::value);
                    break;
                case 'd':
                case 'i':
                    assert(is_integral<T>::value);
                    break;
                case 's':
                    assert((is_same<T, const char*>::value) || (is_same<T, char*>::value));
                    break;
                case 'c':
                    assert((is_same<T, char>::value));
                    break;
                default:
                    throw fmt_error("unknown format '%" + string({*f}) + "'");
            }
            return check_printf(++f, ts...);
        }
        throw fmt_error("too few argument specifiers.");
    }

    const char *normalize(const string& arg);

    template <class T>
    T normalize(T arg) { return arg; }

    // A safe printf style.
    template<typename... Ts>
    void safe_printf(const char *f, const Ts&... ts)
    {
        check_printf(f, normalize(ts)...);
        printf(f, normalize(ts)...);
    }

    // Create a C++ string with sprintf.
    template<typename... Ts>
    string fmt(const char *f, const Ts&... ts)
    {
        check_printf(f, normalize(ts)...);

        // Cannot handle arbitrary length, but it's fine for me.
        const int MAX_SIZE = 4048;
        static char buf[MAX_SIZE];
        snprintf(buf, 4048, f, normalize(ts)...);
        return string(buf);
    }
}

using safe_fmt::fmt;

