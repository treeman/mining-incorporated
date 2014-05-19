#pragma once

#include "roomtype.hxx"
#include "objecttype.hxx"
#include "pos.hxx"
#include "input/inputhandler.hxx"
#include "gui/list.hxx"
#include "gui/state.hxx"
#include "state/statestack.hxx"
#include "gui/buttonpanel.hxx"

namespace scene {
    class World;
};

namespace gui {

    class ButtonPanel;

    class Interface : public InputHandler {
    public:
        Interface(scene::World *world, sf::RenderWindow &window);

        scene::World &get_world() const;

        void handle_event(const Event &event);
        bool handle_input(const sf::Event &e);
        void update(const sf::Time &dt);
        void draw();
    private:
        scene::World *world;
        sf::RenderWindow &window;

        ButtonPanel panel;

    public:
        void set_state(GuiState state);
    private:
        vector<shared_ptr<State>> states;
        shared_ptr<State> current_state;

    public:
        int current_floor() const;
        void set_floor(int floor);
    private:
        void draw_floor_selection();
        int curr_floor;

        void draw_resources();
        void draw_stats(string pre, int &val, sf::Color color, int x, int y);
        sf::Text stat_txt;
    };

};

