#pragma once

#include "basicincludes.hxx"
#include "guiobject.hxx"

// TODO horisontal vs vertical align
// TODO manage styles over the objects (height, width etc..)
// GuiObjects ordered in a list.
class GuiList : public GuiObject {
public:
    GuiList(int x, int y);

    void deselect();

    void add(shared_ptr<GuiObject> o);

    sf::FloatRect bounds() const;
    bool handle_input(const sf::Event &e);

    void set_pos(int x, int y) { }

    void update(const sf::Time &dt);
    void draw(sf::RenderWindow &w);
private:
    vector<shared_ptr<GuiObject>> objects;
    int x, y, space;
};

