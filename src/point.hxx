#pragma once

#include "basicincludes.hxx"

template<typename T>
class Point {
public:
    Point() : x(0), y(0) { }
    Point(T _x, T _y) : x(_x), y(_y) { }
    template<typename S>
    explicit Point(const Point<S> &o) : x(o.x), y(o.y) { }
    template<typename S>
    explicit Point(const sf::Vector2<S> &o) : x(o.x), y(o.y) { }

    operator sf::Vector2<T>() const { return sf::Vector2<T>(x, y); }

    bool operator < (const Point &p) const { return tie(x, y) < tie(p.x, p.y); }
    bool operator > (const Point &p) const { return p < *this; }
    bool operator == (const Point &p) const { return x == p.x && y == p.y; }
    bool operator != (const Point &p) const { return !(*this == p); }
    bool operator <= (const Point &p) const { return !(*this > p); }
    bool operator >= (const Point &p) const { return !(*this < p); }

    Point<T> operator * (T s) const { return Point(x * s, y * s); }
    Point<T> operator / (T s) const { return Point(x / s, y / s); }

    Point<T> operator - (const Point &p) const { return Point(x - p.x, y - p.y); }
    Point<T> operator + (const Point &p) const { return Point(x + p.x, y + p.y); }

    T operator | (const Point &p) const { return x * p.x + y * p.y; }
    T cross(const Point &p) const { return x * p.y - y * p.x; }
    float dist(const Point &p) const { return hypot((float)(x - p.x), (float)(y - p.y)); }
    T distsq(const Point &p) const {
        T dx = x - p.x, dy = y - p.y;
        return dx * dx + dy * dy;
    }
    float len() const { return hypot((float)x, (float)y); }
    Point<T> normalize() const {
        const float l = len();
        return l == 0 ? *this : *this * (1.0f / l);
    }

    void print(const char *s = "") const {
        cout << "(" << x << ", " << y << ")" << s << flush;
    }

    T x, y;

    static const Point zero;
};

// Return angle aob in radians.
template<typename T>
double angle(const Point<T> &a, const Point<T> &o, const Point<T> &b) {
    auto oa = a - o, ob = b - o;
    return acos((oa | ob) / sqrt((oa | oa) * (ob | ob)));
}

// > 0 ccw, < 0 cw, = 0 collinear.
template<typename T>
T orient(const Point<T> &p, const Point<T> &q, const Point<T> &r) {
    return (p - q).cross(r - q);
}

// Is the angle pqr ccw <=> is r to the left side of line pq?
template<typename T>
bool is_ccw(const Point<T> &p, const Point<T> &q, const Point<T> &r) {
    return orient(p, q, r) > 0;
}

// Are the 3 points on a line?
template<typename T>
bool is_collinear(const Point<T> &p, const Point<T> &q, const Point<T> &r) {
    return orient(p, q, r) == 0;
}

template<typename T>
std::ostream &operator<<(std::ostream &os, Point<T> const &p) {
    return os << p.x << ", " << p.y;
}

template<typename T>
Point<T> make_point(T x, T y) { return Point<T>(x, y); }

typedef Point<int> IPoint;
typedef Point<float> FPoint;

