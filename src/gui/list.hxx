#pragma once

#include "basicincludes.hxx"
#include "gui/object.hxx"

namespace gui {

    // TODO horisontal vs vertical align
    // TODO manage styles over the objects (height, width etc..)
    // GuiObjects ordered in a list.
    class List : public Object {
    public:
        List(int x, int y);

        void deselect() override;

        void add(shared_ptr<BoundedObject> o);

        bool is_over(const WindowPos &p) const override;
        bool handle_input(const sf::Event &e) override;

        // TODO make this ine work!
        void set_pos(const WindowPos &p) override { };

        void update(const sf::Time &dt) override ;
        void draw(sf::RenderWindow &w) override;
    private:
        vector<shared_ptr<BoundedObject>> objects;
        WindowPos pos;
        int space;
    };

}
