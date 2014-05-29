#pragma once

#include "pos.hxx"

namespace scene {

    class World;

    template<typename T>
    struct Area {
        Area() : first(-1), last(-1) { }
        Area(T x, T y) : first(x), last(y) {
            assert(x.floor == y.floor);
            normalize();
        }
        Area(const Area &o) : first(o.first), last(o.last) {
            normalize();
        }
        Area &operator = (const Area &o) {
            first = o.first;
            last = o.last;
            normalize();
            return *this;
        }

        void normalize() {
            if (first.pos.x > last.pos.x) swap(first.pos.x, last.pos.x);
            if (first.pos.y > last.pos.y) swap(first.pos.y, last.pos.y);
        }

        string to_string() const {
            IPoint s(first.pos), e(last.pos);
            if (s == e)
                return s.to_string();
            else
                return s.to_string() + " - " + e.to_string();
        }

        template<typename S>
        S area() const {
            S dx = abs(first.pos.x - last.pos.x) + 1;
            S dy = abs(first.pos.y - last.pos.y) + 1;
            return dx * dy;
        }

        bool inside(T p) const {
            if (p.floor != floor()) return false;

            return first.pos.x <= p.pos.x && p.pos.x <= last.pos.x
                && first.pos.y <= p.pos.y && p.pos.y <= last.pos.y;
        }

        // Grid distance
        int dist(T p) const {
            if (p.floor != floor()) return numeric_limits<int>::max();

            if (inside(p)) return 0;
            int dx = 0, dy = 0;
            if (first.pos.x > p.pos.x || p.pos.x > last.pos.x) {
                dx = min(abs(first.pos.x - p.pos.x), abs(p.pos.x - last.pos.x));
            }
            if (first.pos.y > p.pos.y || p.pos.y > last.pos.y) {
                dy = min(abs(first.pos.y - p.pos.y), abs(p.pos.y - last.pos.y));
            }

            return dx + dy;
        }

        int floor() const {
            assert(first.floor == last.floor);
            return first.floor;
        }

        T first, last;

        class my_it : public iterator<forward_iterator_tag, T> {
        public:
            my_it(T _pos, T _first, T _last) : pos(_pos), first(_first), last(_last) { }

            const T &operator*() const { return pos; }
            my_it &operator++() {
                pos = next();
                return *this;
            }
            my_it operator++(int) {
                my_it res(pos, first, last);
                pos = next();
                return res;
            }

            bool operator == (const my_it &it) const { return pos == it.pos; }
            bool operator != (const my_it &it) const { return pos != it.pos; }
        private:
            T next() const {
                T res(pos);
                ++res.pos.x;
                if (res.pos.x > last.pos.x) {
                    res.pos.x = first.pos.x;
                    ++res.pos.y;
                }
                return res;
            }
            T pos;
            const T first, last;
        };

        using const_iterator = my_it;

        const_iterator begin() const { return my_it(first, first, last); }
        const_iterator end() const { return ++my_it(last, first, last); }
    };

    typedef Area<MapPos> MapArea;
    typedef Area<WorldPos> WorldArea;

    MapArea to_map(scene::World *world, WorldArea area);

} // scene

