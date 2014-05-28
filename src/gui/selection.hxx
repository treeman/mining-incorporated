#pragma once

#include "pos.hxx"
#include "scene/area.hxx"

namespace scene {
    class World;
};

namespace gui {
    class Interface;

    // TODO should be able to move selection even outside world border.
    // But clamp it to fit.
    class Selection {
    public:
        Selection(
            scene::World *world,
            Interface *gui,
            function<void(scene::WorldArea)> on_build,
            function<void(scene::WorldArea)> on_remove
        );

        scene::WorldArea get_area() const;
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
        scene::WorldArea area;
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
        function<void(scene::WorldArea)> on_build, on_remove;
    };

}

