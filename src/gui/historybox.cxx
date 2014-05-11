#include "butler.hxx"
#include "util/ext.hxx"
#include "gui/historybox.hxx"

HistoryBox::HistoryBox(int _x, int _y, int _w, int _h) : x(_x), y(_y), w(_w), h(_h) {
    int opacity = 0xDD;
    back = make_rect(sf::FloatRect(x, y, w, h));
    back.setFillColor(make_color(51, 51, 51, opacity));
    back.setOutlineColor(make_color(0x6E6E6E, opacity));

    txt = create_txt("arial.ttf", 10);
    txt.setString("tmp");
    line_height = txt.getLocalBounds().height + 4;
}

void HistoryBox::draw(sf::RenderWindow &w) {
    w.draw(back);

    // TODO make overridable setting
    const int x_off = 5, y_off = 5;

    int curr_x = x + x_off, curr_y = x + y_off;

    // TODO history should be scrollable
    // Draw history scrolling down.
    const int lines = (h - 2 * y_off) / line_height;
    const int hist_size = history.size();
    int off = max(0, hist_size - lines);
    for (int i = off; i < hist_size; ++i) {
        const string s = history[i];
        txt.setPosition(curr_x, curr_y);
        txt.setString(s);
        txt.setColor(sf::Color::White);
        w.draw(txt);
        curr_y += line_height;
    }
}

void HistoryBox::add_line(string s) {
    history.push_back(s);
}

