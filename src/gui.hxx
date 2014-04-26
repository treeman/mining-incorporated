#pragma once

#include "util.hxx"
#include "buttonlist.hxx"
#include "buildtype.hxx"

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
    void handle_preview(int x, int y);

    void add_room(string s); // TODO extend?

    World *world;
    sf::RenderWindow &window;

    ButtonList categories;
    ButtonList rooms;

    sf::Vector2i selection_start, selection_end;
    bool active_selection;

    BuildInfo *to_build;
    void set_build_info(BuildType type);
};

