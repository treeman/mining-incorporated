#include "gui.hxx"
#include "world.hxx"

Gui::Gui(World *w, sf::RenderWindow &win) : world(w), window(win),
    categories(20, 570), room_to_build(NULL), object_to_build(NULL) {
    // TODO make better
    curr_subcategory = -1;
    categories.add(ButtonPtr(new Button([&]() mutable {
            curr_subcategory = 0;
            this->clear_selection();
        }, "Rooms")));
    categories.add(ButtonPtr(new Button([&]() mutable {
            curr_subcategory = 1;
            this->clear_selection();
        }, "Objects")));

    // Rooms
    const int subx = 20, suby = 530;
    ButtonList rooms(subx, suby);
    for (auto x : room_info) {
        const auto info = x.second;
        if (info.name == "") continue; // Hack
        rooms.add(ButtonPtr(new Button([=]() mutable {
                        this->room_to_build = get_info(info.type); // TODO we hacve info already?!?
                        this->object_to_build = NULL;
                    }, info.name)));
    }
    subcategory.push_back(rooms);

    // Objects
    ButtonList objects(subx, suby);
    for (auto x : object_info) {
        const auto info = x.second;
        if (info.name == "") continue; // Hack
        objects.add(ButtonPtr(new Button([=]() mutable {
                        this->object_to_build = get_info(info.type); // TODO we have it??
                        this->room_to_build = NULL;
                    }, info.name)));
    }
    //objects.add(ButtonPtr(new Button([&]() mutable { printf("Bed!\n"); }, "Bed")));
    subcategory.push_back(objects);

    active_selection = false;
}

void Gui::handle_input(const sf::Event &e) {
    switch (e.type) {
        case sf::Event::MouseMoved:
            handle_move(e.mouseMove.x, e.mouseMove.y);
            break;
        case sf::Event::MouseButtonPressed:
            if (e.mouseButton.button == sf::Mouse::Button::Left) {
                handle_left_click(e.mouseButton.x, e.mouseButton.y);
            }
            else if (e.mouseButton.button == sf::Mouse::Button::Right) {
                handle_right_click(e.mouseButton.x, e.mouseButton.y);
            }
            break;
        case sf::Event::MouseButtonReleased:
            if (e.mouseButton.button == sf::Mouse::Button::Left) {
                handle_left_release(e.mouseButton.x, e.mouseButton.y);
            }
            else if (e.mouseButton.button == sf::Mouse::Button::Right) {
                handle_right_release(e.mouseButton.x, e.mouseButton.y);
            }
        default: break;
    }
}
void Gui::update(const sf::Time &dt) {
    categories.update(dt);
    if (curr_subcategory != -1)
        subcategory[curr_subcategory].update(dt);
}
void Gui::draw(sf::RenderWindow &w) {
    categories.draw(w);
    if (curr_subcategory != -1)
        subcategory[curr_subcategory].draw(w);
}

void Gui::handle_move(int x, int y) {
    sf::Vector2i p(x, y);
    categories.check_hover(p);
    if (curr_subcategory != -1)
        subcategory[curr_subcategory].check_hover(p);

    handle_preview(x, y);
}
void Gui::handle_left_click(int x, int y) {
    sf::Vector2i p(x, y);
    categories.check_click(p);
    if (curr_subcategory != -1)
        subcategory[curr_subcategory].check_click(p);

    selection_start = sf::Vector2i(x, y);
    active_selection = true;
}
void Gui::handle_right_click(int x, int y) {

}
void Gui::handle_left_release(int x, int y) {
    selection_end = sf::Vector2i(x, y);
    active_selection = false;
    build();
}
void Gui::handle_right_release(int x, int y) {

}
void Gui::build() {
    if (room_to_build) build_room();
    else if (object_to_build) build_object();
}
void Gui::build_room() {
    if (!room_to_build) return;

    sf::Vector2i tstart = world->window2tile(selection_start);
    sf::Vector2i tend = world->window2tile(selection_end);

    world->clear_preview();
    world->build(tstart.x, tstart.y, tend.x, tend.y, room_to_build->type);
}
void Gui::build_object() {
    sf::Vector2i pos = world->window2tile(selection_end); // Harr! Selection! Harr!

    world->clear_preview();
    world->build(pos.x, pos.y, object_to_build->type);
}

void Gui::handle_preview(int x, int y) {
    auto curr = world->window2tile(sf::Mouse::getPosition(window));
    if (object_to_build) {
        world->clear_preview();
        world->preview_object_build(curr.x, curr.y);
    }
    else if (active_selection) {
        sf::Vector2i tstart = world->window2tile(selection_start);

        world->preview_room_build(tstart.x, tstart.y, curr.x, curr.y);
    }
}

void Gui::clear_selection() {
    room_to_build = NULL;
    object_to_build = NULL;
    for (auto bl : subcategory)
        bl.deselect_all();
}

