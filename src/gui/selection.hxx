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
        AreaSelection() : start(-1), end(-1) { }
        AreaSelection(T x, T y) : start(x), end(y) { normalize(); }
        AreaSelection(const AreaSelection &o) : start(o.start), end(o.end) {
            normalize();
        }
        AreaSelection &operator = (const AreaSelection &o) {
            start = o.start;
            end = o.end;
            normalize();
            return *this;
        }

        void normalize() {
            if (start.pos.x > end.pos.x) swap(start.pos.x, end.pos.x);
            if (start.pos.y > end.pos.y) swap(start.pos.y, end.pos.y);
        }

        string to_string() const {
            IPoint s(start.pos), e(end.pos);
            if (s == e)
                return s.to_string();
            else
                return s.to_string() + " - " + e.to_string();
        }

        T start, end;
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

        string to_string() const;
        void show_debug() const;

        void begin(const WorldPos &start);
        void extend(const WorldPos &end);
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

