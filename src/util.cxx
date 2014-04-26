#include "util.hxx"

sf::Color make_color(int hex) {
    return sf::Color(hex >> 16, hex >> 8 & 0xff, hex & 0xff);
}

