#pragma once

#include <iostream>
#include <cassert>
using namespace std;

// TODO change to formating instead of actuall printf things.
void check_printf(const char *f);

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
            default:
                printf("failed format '%c'!\n", *f);
        }
        return check_printf(++f, ts...);
    }
    printf("too few argument specifiers.\n");
}

const char *normalize(const string& arg);

template <class T>
T normalize(T arg) { return arg; }

template<typename... Ts>
void safe_printf(const char *f, const Ts&... ts)
{
    check_printf(f, normalize(ts)...);
    printf(f, normalize(ts)...);
}

