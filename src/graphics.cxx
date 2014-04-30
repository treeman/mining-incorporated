#include "graphics.hxx"

sf::Color make_color(int a, int r, int g, int alpha) {
    return sf::Color(a, r, g, alpha);
}

sf::Color make_color(int hex) {
    return sf::Color(hex >> 16, hex >> 8 & 0xff, hex & 0xff);
}

sf::Color make_color(int hex, int alpha) {
    return sf::Color(hex >> 16, hex >> 8 & 0xff, hex & 0xff, alpha);
}

sf::Color make_alpha_color(int hex) {
    return sf::Color(hex >> 16, hex >> 8 & 0xff, hex & 0xff, hex >> 24);
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

