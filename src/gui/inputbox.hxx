#pragma once

#include "std.hxx"

namespace gui {

    class InputBox {
    public:
        InputBox(int x, int y);

        void add_char(char c);
        void del_char();
        void clear();
        string get_string() const;

        void update(const sf::Time &dt);
        void draw(sf::RenderWindow &w);
    private:
        sf::Text txt;
        string s;
    };

}

