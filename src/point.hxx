#pragma once

#include "basicincludes.hxx"

// TODO make our own point type?
float len(sf::Vector2f v);
sf::Vector2f normalize(sf::Vector2f v);

template<typename T>
ostream& operator<< (ostream &o, sf::Vector2<T> &p) {
    o << p.x << ", " << p.y;
    return o;
}

