#include <cstdlib>
#include <time.h>
#include <random>

#include "util.hxx"

sf::Color make_color(int hex) {
    return sf::Color(hex >> 16, hex >> 8 & 0xff, hex & 0xff);
}

float len(sf::Vector2f v) {
    return hypot(v.x, v.y);
}
sf::Vector2f normalize(sf::Vector2f v) {
    float l = len(v);
    if (l == 0) return v;
    return v * (1.0f / l);
}

sf::ConvexShape make_rect(const sf::FloatRect &rect) {
    sf::ConvexShape shape;
    shape.setPointCount(4);
    shape.setPoint(0, sf::Vector2f(rect.left, rect.top));
    shape.setPoint(1, sf::Vector2f(rect.left, rect.top + rect.height));
    shape.setPoint(2, sf::Vector2f(rect.left + rect.width, rect.top + rect.height));
    shape.setPoint(3, sf::Vector2f(rect.left + rect.width, rect.top));
    return shape;
}

// W0000
typedef std::minstd_rand G;
G g(time(NULL));
typedef std::uniform_int_distribution<> D;

int rand_int(int a, int b) {
    if (a > b) swap(a, b);
    D d(a, b);
    return d(g);
    //return a + (rand() % (int)(b - a + 1));
}

