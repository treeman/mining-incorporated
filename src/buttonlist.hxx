#pragma once

#include "button.hxx"
#include "guiobject.hxx"

class ButtonList : public GuiObject {
public:
    ButtonList(int x, int y);
    virtual ~ButtonList() { }

    void add(shared_ptr<Button> b);

    void deselect();

    bool is_over(int x, int y);

    void handle_hover();
    void handle_nonhover();
    void handle_click(int button);
    void handle_release(int button);

    //void check_hover(sf::Vector2i pos);
    //void check_click(sf::Vector2i pos);

    void update(const sf::Time &dt);
    void draw(sf::RenderWindow &w);
private:
    vector<shared_ptr<Button>> buttons;
    int x, y;
};

