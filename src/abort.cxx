#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "abort.hxx"
#include "log.hxx"

void abort_game(string msg) {
    L_("\nAborting due to critical error.\n%s\n", msg.c_str());
    if (Locator::has_window()) {
        auto &w = Locator::get_window();
        w.close();
    }
    exit(EXIT_FAILURE);
}

