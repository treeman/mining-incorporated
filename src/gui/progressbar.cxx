#include "progressbar.hxx"
#include "util/ext.hxx"

// ^^
const int w = 23, h = 4;

Progressbar::Progressbar() : x(0), y(0) {
    back = make_rect(sf::FloatRect(0, 0, w, h));
    bar = make_rect(sf::FloatRect(0, 0, w - 2, h - 2));
    tot_length = curr_completion = 0;
    ratio = 1;
}

void Progressbar::set_position(int _x, int _y) {
    x = _x; y = _y;
}
void Progressbar::set_target_time(float target) {
    tot_length = target;
}
void Progressbar::set_completion(float t) {
    curr_completion = t;
    curr_completion = min(curr_completion, tot_length);
    if (tot_length)
        ratio = curr_completion / tot_length;
}
void Progressbar::add_increment(float dt) {
    curr_completion += dt;
    curr_completion = min(curr_completion, tot_length);
    if (tot_length)
        ratio = curr_completion / tot_length;
}
void Progressbar::reset() {
    curr_completion = 0;
}

void Progressbar::draw(sf::RenderWindow &w) {
    back.setPosition(x, y);
    back.setOutlineColor(make_color(0x4A4A4A));
    back.setFillColor(make_color(0xD1D1D1));
    w.draw(back);

    bar.setPosition(x + 1, y + 1);
    bar.setScale(ratio, 1);
    bar.setFillColor(sf::Color::Red);
    w.draw(bar);
}

