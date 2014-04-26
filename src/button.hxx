#pragma once

#include "util.hxx"

class Button {
public:
    Button(function<void()> f, int x, int y, string s);

    void check_click(sf::Vector2i pos);
    void update(const sf::Time &dt);
    void draw(sf::RenderWindow &w);
private:
    sf::Text txt;
    sf::FloatRect bound;
    function<void()> on_click;
};

