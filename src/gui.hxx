#pragma once

#include "buttonlist.hxx"
#include "roomtype.hxx"
#include "objecttype.hxx"
#include "inputhandler.hxx"

class World;

class Gui : public InputHandler {
public:
    Gui(World *world, sf::RenderWindow &window);

    bool handle_input(const sf::Event &e);
    void update(const sf::Time &dt);
    void draw(sf::RenderWindow &w);
private:
    void handle_move(int x, int y);
    void handle_left_click(int x, int y);
    void handle_right_click(int x, int y);
    void handle_left_release(int x, int y);
    void handle_right_release(int x, int y);
    void build();
    void build_room();
    void build_object();
    void handle_preview(int x, int y);

    World *world;
    sf::RenderWindow &window;

    ButtonList categories;

    vector<ButtonList> subcategory;
    int curr_subcategory;

    sf::Vector2i selection_start, selection_end;
    bool active_selection;

    void clear_selection();
    RoomInfo *room_to_build;
    ObjectInfo *object_to_build;
    int preview_cost;

    sf::Text txt;
    void draw_preview_cost(sf::RenderWindow &w);

    // TODO draw other buttons/economy and things if this is true.
    bool show_management;

    // Selection pointer. Can select workers and objects.
    void want_to_select();
    bool want_select;
    void try_select(int x, int y);
};

