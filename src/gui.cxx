#include "gui.hxx"
#include "world.hxx"

Gui::Gui(World *w, sf::RenderWindow &win) : world(w), window(win),
    categories(20, 570), rooms(20, 530), to_build(NULL) {
    // TODO make better
    //categories.add(ButtonPtr(new Button([&]() mutable { printf("Rooms!\n"); }, "Rooms")));
    //categories.add(ButtonPtr(new Button([&]() mutable { printf("Economy!\n"); }, "Economy")));

    for (auto x : build_info) {
        const auto info = x.second;
        rooms.add(ButtonPtr(new Button([=]() mutable {
                        this->to_build = get_info(info.type);
                    }, info.name)));
    }

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
    rooms.update(dt);
}
void Gui::draw(sf::RenderWindow &w) {
    categories.draw(w);
    rooms.draw(w);
}

void Gui::handle_move(int x, int y) {
    sf::Vector2i p(x, y);
    categories.check_hover(p);
    rooms.check_hover(p);

    handle_preview(x, y);
}
void Gui::handle_left_click(int x, int y) {
    sf::Vector2i p(x, y);
    categories.check_click(p);
    rooms.check_click(p);

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
    if (!to_build) return;

    sf::Vector2i tstart = world->window2tile(selection_start);
    sf::Vector2i tend = world->window2tile(selection_end);

    world->clear_preview();
    //printf("type: %d\n", to_build->type);
    // XXX ???
    if (to_build->type == Demolish) {
    }
    world->build(tstart.x, tstart.y, tend.x, tend.y, to_build->type);
}

void Gui::handle_preview(int x, int y) {
    auto curr = world->window2tile(sf::Mouse::getPosition(window));
    // TODO hover over 1 if no selection
    if (active_selection) {
        sf::Vector2i tstart = world->window2tile(selection_start);

        world->preview_build(tstart.x, tstart.y, curr.x, curr.y);
    }
    else {
        //world->clear_preview();
        //world->preview_build(curr.x, curr.y);
    }
}

void Gui::add_room(string s) {
            //set_
            //printf("%s!\n", s.c_str());
        //}, s)));
    //rooms.add(ButtonPtr(new Button([=]() mutable {
            //printf("%s!\n", s.c_str());
        //}, s)));
}

void Gui::set_build_info(BuildType type) {
    if (!to_build) printf("Error no build info!\n");
    else {
        auto info = get_info(type);
        printf("Building %s\n", info->name.c_str());
        to_build = info;
    }
}
