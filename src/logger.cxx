#include <cstdio>
#include <stdarg.h>
#include <iostream>
using namespace std;

#include "logger.hxx"

Logger::~Logger() { }

// c++ style
template<typename T>
Logger &Logger::operator << (T v) {
    write(to_string(v));
    return *this;
}

// printf style
//void Logger::operator()(const char *msg, ...) {
    //va_list args;
    //va_start(args, msg);
    //char buf[4048]; // heh
    //vsprintf(buf, msg, args);
    //write(buf);
}

