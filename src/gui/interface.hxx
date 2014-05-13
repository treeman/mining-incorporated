#pragma once

#include "roomtype.hxx"
#include "objecttype.hxx"
#include "pos.hxx"
#include "input/inputhandler.hxx"
#include "gui/list.hxx"
#include "gui/state.hxx"
#include "state/statestack.hxx"
#include "gui/buttonpanel.hxx"

class World;

namespace Gui {
    class ButtonPanel;

    class Interface : public InputHandler {
    public:
        Interface(World *world, sf::RenderWindow &window);

        bool handle_input(const sf::Event &e);
        void update(const sf::Time &dt);
        void draw(sf::RenderWindow &w);
    private:
        // TODO state transitions
        void handle_move(const WindowPos &p);
        void handle_left_click(const WindowPos &p);
        void handle_right_click(const WindowPos &p);
        void handle_left_release(const WindowPos &p);
        void handle_right_release(const WindowPos &p);
        void build();
        void build_room();
        void build_object();
        void handle_preview(const WindowPos &p);

        World *world;
        sf::RenderWindow &window;

        ButtonPanel panel;

        unique_ptr<List> categories;

        // TODO subcategory class
        vector<unique_ptr<List>> subcategory;
        int curr_subcategory;

        // TODO selection class
        // TODO move to states
        WorldPos selection_start, selection_end;
        bool active_selection;

        void clear_selection();
        RoomInfo *room_to_build;
        ObjectInfo *object_to_build;
        int preview_cost;

        sf::Text txt;
        void draw_preview_cost();

        // TODO draw other buttons/economy and things if this is true.
        bool show_management;

        // Selection pointer. Can select workers and objects.
        void want_to_select();
        bool want_select;
        void try_select(const WindowPos &p);

        void draw_floor_selection();
        void set_floor(int floor);

    public:
        void set_state(GuiStates state);
    private:
        vector<shared_ptr<State>> states;
        shared_ptr<State> current_state;
    };

}

