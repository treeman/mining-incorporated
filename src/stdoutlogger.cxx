#include "stdoutlogger.hxx"

void StdoutLogger::write(string s) {
    printf("%s", s.c_str());
}

