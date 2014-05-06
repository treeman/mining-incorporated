#pragma once

class Logger {
public:
    virtual ~Logger();

    // c++ style
    template<typename T>
    Logger &operator << (T v);

    // TODO
    // printf style
    // http://stackoverflow.com/questions/17671772/c11-variadic-printf-performance
    //void operator()(const char *msg, ...);
    //template<typename... Ts>
    //int safe_printf(const char * f, const Ts&... ts)
    //{
        //check_printf(f, normalizeArg(ts)...);  // check format specifiers
        //return printf(f, ts...); // output with clean arguments
    //}
protected:
    virtual void write(string s) = 0;
};

