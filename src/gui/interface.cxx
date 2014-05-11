#include "butler.hxx"
#include "constants.hxx"
#include "util/ext.hxx"
#include "world/world.hxx"
#include "gui/interface.hxx"
#include "gui/button.hxx"

namespace Gui {

Interface::Interface(World *w, sf::RenderWindow &win) : world(w), window(win),
    selection_start(-1), selection_end(-1),
    room_to_build(nullptr), object_to_build(nullptr), current_state(nullptr)
{
    unique_ptr<List>(new List(20, 570)).swap(categories);

    // A bit hacky, could refactor into gui elements.
    curr_subcategory = -1;
    show_management = false;
    categories->add(shared_ptr<Button>(new Button([&]() mutable {
            curr_subcategory = 0;
            this->clear_selection();
            show_management = false;
        }, "Rooms")));
    categories->add(shared_ptr<Button>(new Button([&]() mutable {
            curr_subcategory = 1;
            this->clear_selection();
            show_management = false;
        }, "Objects")));
    categories->add(shared_ptr<Button>(new Button([&]() mutable {
            //curr_subcategory = -1;
            show_management = true;
            //curr_subcategory = 1;
            //this->clear_selection();
            curr_subcategory = 2;
            this->clear_selection();
        }, "Management")));

    // Rooms
    const int subx = 20, suby = 530;
    unique_ptr<List> rooms(new List(subx, suby));
    for (auto x : room_info) {
        auto &info = x.second;
        if (info.name == "") continue; // Hack
        rooms->add(shared_ptr<Button>(new Button([=]() mutable {
                        this->room_to_build = &info;
                        this->object_to_build = nullptr;
                    }, info.name)));
    }
    subcategory.push_back(move(rooms));

    // Objects
    unique_ptr<List> objects(new List(subx, suby));
    for (auto x : object_info) {
        auto &info = x.second;
        if (info.name == "") continue; // Hack
        objects->add(shared_ptr<Button>(new Button([=]() mutable {
                        this->object_to_build = &info;
                        this->room_to_build = nullptr;
                    }, info.name)));
    }
    subcategory.push_back(move(objects));

    // Management
    // TODO move away
    unique_ptr<List> management(new List(subx, suby));
    management->add(shared_ptr<Button>(new Button([=]() mutable{
                        this->want_to_select();
                    }, "Select")));
    management->add(shared_ptr<Button>(new ClickButton([=]() mutable{
                        this->clear_selection(); // TODO this will deselect this one T.T
                        world->new_worker();
                    }, "Hire Worker")));
    subcategory.push_back(move(management));

    active_selection = false;
    preview_cost = 0;
    txt = create_txt("consola.ttf", 16);
    want_select = false;

    //set_state("info");
}

// TODO block on interactions
bool Interface::handle_input(const sf::Event &e) {
    categories->handle_input(e);
    if (curr_subcategory != -1)
        subcategory[curr_subcategory]->handle_input(e);

    switch (e.type) {
        case sf::Event::MouseMoved:
            handle_move(WindowPos(e.mouseMove.x, e.mouseMove.y));
            break;
        case sf::Event::MouseButtonPressed:
            if (e.mouseButton.button == sf::Mouse::Button::Left) {
                handle_left_click(WindowPos(e.mouseButton.x, e.mouseButton.y));
            }
            else if (e.mouseButton.button == sf::Mouse::Button::Right) {
                handle_right_click(WindowPos(e.mouseButton.x, e.mouseButton.y));
            }
            break;
        case sf::Event::MouseButtonReleased:
            if (e.mouseButton.button == sf::Mouse::Button::Left) {
                handle_left_release(WindowPos(e.mouseButton.x, e.mouseButton.y));
            }
            else if (e.mouseButton.button == sf::Mouse::Button::Right) {
                handle_right_release(WindowPos(e.mouseButton.x, e.mouseButton.y));
            }
            break;
        case sf::Event::TextEntered:
            if ('1' <= e.text.unicode && e.text.unicode <= '9') {
                set_level(e.text.unicode - '1');
            }
            break;
        default: break;
    }
    return true;
}
void Interface::update(const sf::Time &dt) {
    categories->update(dt);
    if (curr_subcategory != -1)
        subcategory[curr_subcategory]->update(dt);
}
void Interface::draw(sf::RenderWindow &w) {
    categories->draw(w);
    if (curr_subcategory != -1)
        subcategory[curr_subcategory]->draw(w);
    draw_level_selection();
    if (preview_cost)
        draw_preview_cost();
}

void Interface::handle_move(const WindowPos &p) {
    //sf::Vector2i p(x, y);
    //categories.check_hover(p);
    //if (curr_subcategory != -1)
        //subcategory[curr_subcategory].check_hover(p);

    handle_preview(p);
}
void Interface::handle_left_click(const WindowPos &p) {
    //sf::Vector2i p(x, y);
    //categories.check_click(p);
    //if (curr_subcategory != -1)
        //subcategory[curr_subcategory].check_click(p);

    if (!world->in_world(p)) return;

    if (want_select) {
        try_select(p);
    }
    else {
        // TODO refactor
        selection_start = world->window2world(p);
        active_selection = true;
    }
}
void Interface::handle_right_click(const WindowPos &p) {

}
void Interface::handle_left_release(const WindowPos &p) {
    if (!world->in_world(p)) return;

    selection_end = world->window2world(p);
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
void Interface::handle_right_release(const WindowPos &p) {

}
void Interface::build() {
    if (room_to_build) build_room();
    else if (object_to_build) build_object();
}
void Interface::build_room() {
    if (!room_to_build) return;

    // TODO fix
    //sf::Vector2i tstart = world->window2tile(selection_start);
    //sf::Vector2i tend = world->window2tile(selection_end);

    //world->build(tstart.x, tstart.y, tend.x, tend.y, room_to_build->type);
    preview_cost = 0;
}
void Interface::build_object() {
    //sf::Vector2i pos = world->window2tile(selection_end); // Harr! Selection! Harr!
    WorldPos pos = selection_end;

    // TODO better
    world->clear_preview();
    world->build(pos.pos.x, pos.pos.y, object_to_build->type);
    preview_cost = 0;
}

void Interface::handle_preview(const WindowPos &p) {
    WindowPos wp(get_mpos());
    if (!world->in_world(wp)) return;

    auto curr = world->window2dimension(wp).pos;
    if (object_to_build) {
        world->clear_preview();
        world->preview_object_build(curr.x, curr.y);
        preview_cost = object_to_build->cost;
    }
    else if (active_selection) {
        // TODO cleanup
        auto tstart = selection_start.pos;

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
void Interface::clear_selection() {
    room_to_build = nullptr;
    object_to_build = nullptr;
    for (auto &bl : subcategory)
        bl->deselect();
    want_select = false;
}

void Interface::draw_preview_cost() {
    // Draw preview cost
    // TODO better position
    WindowPos wp(get_mpos());
    if (!world->in_world(wp)) return;

    auto curr = world->window2world(wp).pos;
    int x = 0, y = 0;
    if (object_to_build || (!active_selection && room_to_build)) {
        x = curr.x + 20;
        y = curr.y - 30;
    }
    else {
        auto sel = selection_start.pos;
        //auto sel = world->tile2window(selection_start);
        //printf("%d,%d -> %d,%d\n", selection_start.x, selection_start.y, sel.x, sel.y);
        int left = min((int)sel.x, (int)curr.x);
        int top = min((int)sel.y, (int)curr.y);
        x = left + 20;
        y = top - 30;
    }
    txt.setPosition(x, y);
    txt.setColor(sf::Color::White);
    stringstream ss; ss << "$" << preview_cost;
    txt.setString(ss.str());
    window.draw(txt);
}

void Interface::want_to_select() {
    clear_selection();
    want_select = true;
}

void Interface::try_select(const WindowPos &p) {
    if (!world->in_world(p)) return;

    WorldPos pos = world->window2world(p);
    WorkerPtr worker = world->select_closest_worker(pos.pos.x, pos.pos.y);
    if (worker) {
        // TODO better points...
        // TODO select distance from center of worker
        auto p = worker->get_pos();
        //double d = hypot((double)pos.x - p.x, (double)pos.y - p.y);
        float d = pos.pos.dist(IPoint(p));
        if (d <= min_select_dist) {
            // TODO store as weak_ptr
            printf("Worker at %lf %lf dist %lf\n", p.x, p.y, d);
        }
    }
}

void Interface::draw_level_selection() {
    const int lvl = world->get_curr_level();
    txt.setString("level: " + to_string(lvl));
    txt.setPosition(155, 15);
    txt.setColor(sf::Color::White);
    window.draw(txt);
}

void Interface::set_level(int lvl) {
    if (0 <= lvl && lvl < world->num_levels()) {
        world->set_curr_level(lvl);
    }
}

void Interface::set_state(string next) {
    auto it = states.find(next);
    assert(it != states.end());
    current_state = it->second;
}

}

