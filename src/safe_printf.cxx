#include "safe_printf.hxx"

void check_printf(const char *f) {
    for (; *f; ++f) {
        if (*f != '%' || *++f == '%') continue;
        //throw exception;
        printf("too many format specifiers.\n");
    }
}

const char *normalize(const string& arg) {
   return arg.c_str();
}
