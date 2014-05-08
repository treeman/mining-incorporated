#include "fmt.hxx"

namespace safe_fmt {
    void check_printf(const char *f) {
        for (; *f; ++f) {
            if (*f != '%' || *++f == '%') continue;
            throw fmt_error("too many format specifiers.");
        }
    }

    const char *normalize(const string& arg) {
        return arg.c_str();
    }
}

