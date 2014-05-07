#include "consolelogger.hxx"

void ConsoleLogger::write(string s) {
    printf("%s", s.c_str());
}

