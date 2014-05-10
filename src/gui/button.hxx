#pragma once

#include "basicincludes.hxx"
#include "guiobject.hxx"

class Button : public GuiObject {
public:
    Button(function<void()> f, string s);
    virtual ~Button() { }

    virtual void select() override;
    virtual void deselect() override;

    sf::FloatRect bounds() const override { return bound; }

    void set_pos(int x, int y) override;

    //void check_hover(sf::Vector2i pos);
    //bool check_click(sf::Vector2i pos);

    void handle_hover() override;
    void handle_nonhover() override;
    void handle_click(int button) override;

    void update(const sf::Time &dt) override;
    void draw(sf::RenderWindow &w) override;
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

