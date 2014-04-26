#include "util.hxx"

sf::Color make_color(int hex) {
    return sf::Color(hex >> 16, hex >> 8 & 0xff, hex & 0xff);
}

float len(sf::Vector2f v) {
    return hypot(v.x, v.y);
}
sf::Vector2f normalize(sf::Vector2f v) {
    //return v * 100.0f;
    float l = len(v);
    if (l == 0) return v;
    //return v * 0.2;
    return v * (1.0f / l);
}

