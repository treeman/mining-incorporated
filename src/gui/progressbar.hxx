#pragma once

#include "std.hxx"

namespace gui {

    class Progressbar {
    public:
        Progressbar();

        void set_position(int x, int y);
        void set_target_time(float target);
        void set_completion(float t);
        void add_increment(float dt);
        void reset();

        void draw(sf::RenderWindow &w);
    private:
        sf::ConvexShape back, bar;
        int x, y;
        float tot_length, curr_completion, ratio;
    };

}

