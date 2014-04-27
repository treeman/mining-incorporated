#pragma once

#include "util.hxx"
#include "buttonlist.hxx"
#include "roomtype.hxx"
#include "objecttype.hxx"

class World;

class Gui {
public:
    Gui(World *world, sf::RenderWindow &window);

    void handle_input(const sf::Event &e);
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
    //ButtonList rooms;

    sf::Vector2i selection_start, selection_end;
    bool active_selection;

    void clear_selection();
    RoomInfo *room_to_build;
    ObjectInfo *object_to_build;
};

