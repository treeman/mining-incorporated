#pragma once

#include "util.hxx"
#include "buildtype.hxx"

class Button {
public:
    Button(function<void()> f, string s);

    void set_pos(int x, int y);
    sf::FloatRect get_bounds() const { return bound; }

    void select();
    void deselect();

    void check_hover(sf::Vector2i pos);
    bool check_click(sf::Vector2i pos);
    void update(const sf::Time &dt);
    void draw(sf::RenderWindow &w);
private:
    sf::Text txt;
    sf::FloatRect bound;
    sf::ConvexShape back;
    function<void()> on_click;
    bool selected;
    bool hover;
};

typedef shared_ptr<Button> ButtonPtr;

