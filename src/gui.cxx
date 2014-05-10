#include "gui.hxx"
#include "world.hxx"
#include "butler.hxx"
#include "constants.hxx"
#include "button.hxx"

Gui::Gui(World *w, sf::RenderWindow &win) : world(w), window(win),
    room_to_build(nullptr), object_to_build(nullptr)
{
    unique_ptr<GuiList>(new GuiList(20, 570)).swap(categories);

    // A bit hacky, could refactor into gui elements.
    curr_subcategory = -1;
    show_management = false;
    categories->add(ButtonPtr(new Button([&]() mutable {
            curr_subcategory = 0;
            this->clear_selection();
            show_management = false;
        }, "Rooms")));
    categories->add(ButtonPtr(new Button([&]() mutable {
            curr_subcategory = 1;
            this->clear_selection();
            show_management = false;
        }, "Objects")));
    categories->add(ButtonPtr(new Button([&]() mutable {
            //curr_subcategory = -1;
            show_management = true;
            //curr_subcategory = 1;
            //this->clear_selection();
            curr_subcategory = 2;
            this->clear_selection();
        }, "Management")));

    // Rooms
    const int subx = 20, suby = 530;
    unique_ptr<GuiList> rooms(new GuiList(subx, suby));
    for (auto x : room_info) {
        auto &info = x.second;
        if (info.name == "") continue; // Hack
        rooms->add(ButtonPtr(new Button([=]() mutable {
                        this->room_to_build = &info;
                        this->object_to_build = nullptr;
                    }, info.name)));
    }
    subcategory.push_back(move(rooms));

    // Objects
    unique_ptr<GuiList> objects(new GuiList(subx, suby));
    for (auto x : object_info) {
        auto &info = x.second;
        if (info.name == "") continue; // Hack
        objects->add(ButtonPtr(new Button([=]() mutable {
                        this->object_to_build = &info;
                        this->room_to_build = nullptr;
                    }, info.name)));
    }
    subcategory.push_back(move(objects));

    // Management
    // TODO move away
    unique_ptr<GuiList> management(new GuiList(subx, suby));
    management->add(ButtonPtr(new Button([=]() mutable{
                        this->want_to_select();
                    }, "Select")));
    management->add(ButtonPtr(new ClickButton([=]() mutable{
                        this->clear_selection(); // TODO this will deselect this one T.T
                        world->new_worker();
                    }, "Hire Worker")));
    subcategory.push_back(move(management));

    active_selection = false;
    preview_cost = 0;
    txt = create_txt("consola.ttf", 16);
    want_select = false;
}

// TODO block on interactions
bool Gui::handle_input(const sf::Event &e) {
    categories->handle_input(e);
    if (curr_subcategory != -1)
        subcategory[curr_subcategory]->handle_input(e);

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
            break;
        case sf::Event::TextEntered:
            if ('0' <= e.text.unicode && e.text.unicode <= '9') {
                set_level(e.text.unicode - '0');
            }
            break;
        default: break;
    }
    return true;
}
void Gui::update(const sf::Time &dt) {
    categories->update(dt);
    if (curr_subcategory != -1)
        subcategory[curr_subcategory]->update(dt);
}
void Gui::draw(sf::RenderWindow &w) {
    categories->draw(w);
    if (curr_subcategory != -1)
        subcategory[curr_subcategory]->draw(w);
    draw_level_selection();
    if (preview_cost)
        draw_preview_cost();
}

void Gui::handle_move(int x, int y) {
    sf::Vector2i p(x, y);
    //categories.check_hover(p);
    //if (curr_subcategory != -1)
        //subcategory[curr_subcategory].check_hover(p);

    handle_preview(x, y);
}
void Gui::handle_left_click(int x, int y) {
    sf::Vector2i p(x, y);
    //categories.check_click(p);
    //if (curr_subcategory != -1)
        //subcategory[curr_subcategory].check_click(p);

    if (want_select) {
        try_select(x, y);
    }
    else {
        // TODO refactor
        selection_start = sf::Vector2i(x, y);
        active_selection = true;
    }
}
void Gui::handle_right_click(int x, int y) {

}
void Gui::handle_left_release(int x, int y) {
    selection_end = sf::Vector2i(x, y);
    active_selection = false;
    preview_cost = 0;

    // Can cancel by holding right at release
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        world->clear_preview();
    }
    else {
        build();
    }
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

    world->build(tstart.x, tstart.y, tend.x, tend.y, room_to_build->type);
    preview_cost = 0;
}
void Gui::build_object() {
    sf::Vector2i pos = world->window2tile(selection_end); // Harr! Selection! Harr!

    world->clear_preview();
    world->build(pos.x, pos.y, object_to_build->type);
    preview_cost = 0;
}

void Gui::handle_preview(int x, int y) {
    auto curr = world->window2tile(sf::Mouse::getPosition(window));
    if (object_to_build) {
        world->clear_preview();
        world->preview_object_build(curr.x, curr.y);
        preview_cost = object_to_build->cost;
    }
    else if (active_selection) {
        sf::Vector2i tstart = world->window2tile(selection_start);

        world->preview_room_build(tstart.x, tstart.y, curr.x, curr.y);
        if (room_to_build)
            preview_cost = world->calculate_build_cost(tstart.x, tstart.y, curr.x, curr.y, room_to_build->type);
    }
    else if (room_to_build) {
        world->clear_preview();
        world->preview_room_build(curr.x, curr.y);
        preview_cost = room_to_build->cost;
    }
}

// Clear everything.
void Gui::clear_selection() {
    room_to_build = nullptr;
    object_to_build = nullptr;
    for (auto &bl : subcategory)
        bl->deselect();
    want_select = false;
}

void Gui::draw_preview_cost() {
    // Draw preview cost
    // TODO better position
    auto curr = sf::Mouse::getPosition(window);
    int x = 0, y = 0;
    if (object_to_build || (!active_selection && room_to_build)) {
        x = curr.x + 20;
        y = curr.y - 30;
    }
    else {
        auto sel = selection_start;
        //auto sel = world->tile2window(selection_start);
        //printf("%d,%d -> %d,%d\n", selection_start.x, selection_start.y, sel.x, sel.y);
        int left = min(sel.x, curr.x);
        int top = min(sel.y, curr.y);
        x = left + 20;
        y = top - 30;
    }
    txt.setPosition(x, y);
    txt.setColor(sf::Color::White);
    stringstream ss; ss << "$" << preview_cost;
    txt.setString(ss.str());
    window.draw(txt);
}

void Gui::want_to_select() {
    clear_selection();
    want_select = true;
}

void Gui::try_select(int x, int y) {
    sf::Vector2i pos = world->window2world(x, y);
    WorkerPtr worker = world->select_closest_worker(pos.x, pos.y);
    if (worker) {
        // TODO better points...
        // TODO select distance from center of worker
        auto p = worker->get_pos();
        double d = hypot((double)pos.x - p.x, (double)pos.y - p.y);
        if (d <= min_select_dist) {
            // TODO store as weak_ptr
            printf("Worker at %lf %lf dist %lf\n", p.x, p.y, d);
        }
    }
}

void Gui::draw_level_selection() {
    const int lvl = world->get_curr_level();
    txt.setString("level: " + to_string(lvl));
    txt.setPosition(10, 40);
    txt.setColor(sf::Color::White);
    window.draw(txt);
}

void Gui::set_level(int lvl) {
    if (0 <= lvl && lvl < world->num_levels()) {
        world->set_curr_level(lvl);
    }
}

