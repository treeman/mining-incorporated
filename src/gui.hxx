#pragma once

#include "guilist.hxx"
#include "roomtype.hxx"
#include "objecttype.hxx"
#include "inputhandler.hxx"
#include "pos.hxx"

class World;

class Gui : public InputHandler {
public:
    Gui(World *world, sf::RenderWindow &window);

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

    unique_ptr<GuiList> categories;

    // TODO subcategory class
    vector<unique_ptr<GuiList>> subcategory;
    int curr_subcategory;

    // TODO selection class
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

    void draw_level_selection();
    void set_level(int lvl);
};

