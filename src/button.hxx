#pragma once

#include "basicincludes.hxx"
#include "guiobject.hxx"

class Button : public GuiObject {
public:
    Button(function<void()> f, string s);
    virtual ~Button() { }

    void set_pos(int x, int y);
    sf::FloatRect bounds() const { return bound; }

    virtual void select();
    virtual void deselect();

    //void check_hover(sf::Vector2i pos);
    //bool check_click(sf::Vector2i pos);

    void handle_hover();
    void handle_nonhover();
    void handle_click(int button);

    bool is_over(int x, int y);

    void update(const sf::Time &dt);
    void draw(sf::RenderWindow &w);
protected:
    sf::Text txt;
    sf::FloatRect bound;
    sf::ConvexShape back;
    function<void()> on_click;
    bool selected;
    bool hover;
};

typedef shared_ptr<Button> ButtonPtr;

// Deselects itself when clicked on.
class ClickButton : public Button {
public:
    ClickButton(function<void()> f, string s);
    virtual ~ClickButton() { }

    void select();
};

