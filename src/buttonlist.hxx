#pragma once

#include "util.hxx"
#include "button.hxx"

class ButtonList {
public:
    ButtonList(int x, int y);

    void add(shared_ptr<Button> b);

    void deselect_all();

    void check_hover(sf::Vector2i pos);
    void check_click(sf::Vector2i pos);
    void update(const sf::Time &dt);
    void draw(sf::RenderWindow &w);
private:
    vector<shared_ptr<Button>> buttons;
    int x, y;
};

