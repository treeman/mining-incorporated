#pragma once

#include "input/inputhandler.hxx"
#include "gui/list.hxx"
#include "gui/button.hxx"

namespace gui {

    class Interface;

    // Main interface with buttons down low.
    // Each button will have it's own subcategory with different things.
    class ButtonPanel : public InputHandler {
    public:
        ButtonPanel(Interface &gui);

        bool handle_input(const sf::Event &e);
    private:
        bool mark_hover(const WindowPos &p);
        bool click(const WindowPos &p);

    public:
        void update(const sf::Time &dt);
        void draw(sf::RenderWindow &w);
    private:
        Interface &gui;

        enum class Categories : int {
            UNSELECTED = -1,
            PLANNING,
        };

        unique_ptr<List> categories;
        vector<unique_ptr<List>> subcategories;
        Categories curr;

        function<void(BaseButton &button)> make_category_selector(Categories cat);
    };

}

