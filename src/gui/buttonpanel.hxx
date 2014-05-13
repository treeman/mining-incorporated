#pragma once

#include "input/inputhandler.hxx"
#include "gui/list.hxx"

namespace Gui {

    class Interface;

    // Main interface with buttons down low.
    // Each button will have it's own subcategory with different things.
    class ButtonPanel : public InputHandler {
    public:
        ButtonPanel(Interface &gui);

        bool handle_input(const sf::Event &e);

        void update(const sf::Time &dt);
        void draw(sf::RenderWindow &w);
    private:
        Interface &gui;

        unique_ptr<List> categories;
        vector<unique_ptr<List>> subcategories;
        int curr;
    };

}

