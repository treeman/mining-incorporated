#pragma once

#include "pos.hxx"

namespace scene {
    class World;
};

namespace gui {

    // TODO should be able to move selection even outside world border.
    // But clamp it to fit.
    // TODO iterator over it.
    template<typename T>
    struct AreaSelection {
        AreaSelection() : first(-1), last(-1) { }
        AreaSelection(T x, T y) : first(x), last(y) {
            assert(x.floor == y.floor);
            normalize();
        }
        AreaSelection(const AreaSelection &o) : first(o.first), last(o.last) {
            normalize();
        }
        AreaSelection &operator = (const AreaSelection &o) {
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

        using iterator = my_it;

        iterator begin() const { return my_it(first, first, last); }
        iterator end() const { return ++my_it(last, first, last); }
    };

    typedef AreaSelection<MapPos> MapSelection;
    typedef AreaSelection<WorldPos> WorldSelection;

    MapSelection to_map(scene::World *world, WorldSelection sel);

    class Interface;

    class Selection {
    public:
        Selection(
            scene::World *world,
            Interface *gui,
            function<void(WorldSelection)> on_build,
            function<void(WorldSelection)> on_remove
        );

        WorldSelection get_area() const;
        WindowPos get_outside_txt_pos() const;

        string to_string() const;
        void show_debug() const;

        void begin(const WorldPos &first);
        void extend(const WorldPos &last);
        void clear();
        bool is_active() const;
        bool want_remove() const;
        bool is_point() const;
    private:
        WorldSelection area;
        bool active;
        bool remove;

    public:
        bool handle_input(const sf::Event &e);
    private:
        void move(const WindowPos &p);
        void left_click(const WindowPos &p);
        void right_click(const WindowPos &p);
        void left_release(const WindowPos &p);
        void right_release(const WindowPos &p);

        scene::World *world;
        Interface *gui;
        function<void(WorldSelection)> on_build, on_remove;
    };

}

