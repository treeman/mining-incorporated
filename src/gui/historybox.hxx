#pragma once

#include "basicincludes.hxx"

namespace gui {

    // Draw a list of strings with scrolling.
    class HistoryBox {
    public:
        HistoryBox(int x, int y, int w, int h);

        void draw(sf::RenderWindow &w);

        void add_line(string s);
    private:
        vector<string> history;
        sf::ConvexShape back;
        sf::Text txt;
        int line_height;
        int x, y, w, h;
    };

}

