#pragma once

#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>
using namespace std;

// TODO
// Poke with this with updated gcc.
// http://stackoverflow.com/questions/17671772/c11-variadic-printf-performance
/*
const char *normalizeArg(const string& arg) {
   return arg.c_str();
}
*/

/*
template <class T>
typename enable_if<is_integral<T>::value, long>::type
normalizeArg(T arg)
{
    return arg;
}
*/
/*
template <class T>
typename enable_if<is_floating_point<T>::value, double>::type
normalizeArg(T arg) { return arg; }

template <class T>
typename enable_if<is_pointer<T>::value, T>::type
normalizeArg(T arg) { return arg; }
*/

/*
void check_printf(const char *f) {
    for (; *f; ++f) {
        if (*f != '%' || *++f == '%') continue;
        //throw exception;
        printf("failed format!\n");
    }
}
template<class T, typename... Ts>
void check_printf(const char *f, const T &t, const Ts&... ts) {
    for (; *f; ++f) {
        if (*f != '%' || *++f == '%') continue;
        switch (*f) {
            case 'f':
            case 'g':
                assert(is_floating_point<T>::value);
                break;
            default: printf("failed format!\n");
        }
        return check_printf(++f, ts...);
    }
    printf("too few argument specifiers.\n");
}
*/
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

        char buf[4048];
        snprintf(buf, 4048, f, ts...);
        write(buf);
    }
private:
    virtual void write(string s) = 0;
};

