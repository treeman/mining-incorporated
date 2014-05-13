#pragma once

#include "gui/object.hxx"

namespace Gui {

    class Subcategory : public InputHandler {
    public:
        Subcategory();

        bool is_over(const WindowPos &p) const override;
        void set_pos(const WindowPos &p) override;

        void update(const sf::Time &dt) override;
        void draw(sf::RenderWindow &w) override;
    };

    class Subcategories : public InputHandler {
    public:
        Subcategories();

        bool is_over(const WindowPos &p) const override;
        void set_pos(const WindowPos &p) override;

        void update(const sf::Time &dt) override;
        void draw(sf::RenderWindow &w) override;
    private:
        unique_ptr<List> categories;
        vector<unique_ptr<List>> subcategories;
        int curr_cat;
    };

}

