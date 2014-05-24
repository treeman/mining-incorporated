#include "butler.hxx"
#include "constants.hxx"
#include "log.hxx"
#include "util/ext.hxx"
#include "scene/world.hxx"
#include "gui/interface.hxx"
#include "gui/button.hxx"
#include "gui/picbutton.hxx"
#include "gui/buttonpanel.hxx"

namespace gui {

Interface::Interface(scene::World *w, sf::RenderWindow &win) : world(w), window(win), panel(*this),
    current_state(nullptr), curr_floor(0)
{
    // Setup guistates.
    states.resize(static_cast<unsigned>(GuiState::NUM_STATES));
    states[static_cast<unsigned>(GuiState::INFO)].reset(new InfoState(this, world));
    states[static_cast<unsigned>(GuiState::MATERIAL)].reset(new MaterialState(this, world));
    states[static_cast<unsigned>(GuiState::PLANNING)].reset(new PlanningState(this, world));
    set_state(GuiState::INFO);
    assert(current_state != nullptr);

    stat_txt = create_txt("consola.ttf", 14);
}

scene::World &Interface::get_world() const {
    assert(world != nullptr);
    return *world;
}

// TODO block on interactions
bool Interface::handle_input(const sf::Event &e) {
    panel.handle_input(e);
    current_state->handle_input(e);

    switch (e.type) {
        case sf::Event::TextEntered:
            if ('1' <= e.text.unicode && e.text.unicode <= '9') {
                set_floor(e.text.unicode - '1');
            }
            break;
        default: break;
    }

    return true;
}
void Interface::update(const sf::Time &dt) {
    current_state->update(dt);
    panel.update(dt);

    // Add in some debug information.
    if (Locator::get_settings().get_bool("debug_positions")) {
        WindowPos mp(get_mpos());
        if (world->in_world(mp, curr_floor)) {
            WorldPos wpos(world->window2world(mp, curr_floor));
            MapPos map_pos(world->world2map(wpos));
            // Treat as int position, prevent unnecessary decimals
            D_.set_key("world", IPoint(wpos.pos).to_string() + " (" + to_string(wpos.floor) + ")");
            D_.set_key("map", map_pos.to_string());
        }
        else {
            D_.set_key("world", "invalid");
            D_.set_key("map", "invalid");
        }
    }
}
void Interface::draw() {
    current_state->draw(window);
    panel.draw(window);
    draw_resources();
    draw_floor_selection();
}
void Interface::set_state(GuiState state) {
    unsigned x = static_cast<unsigned>(state);
    // TODO flag
    D_.set_key("gui state", type2string(state));
    assert(x < states.size());
    current_state = states[x];
    current_state->reset();
}

void Interface::handle_event(const Event &e) {
    current_state->handle_event(e);
}

int Interface::current_floor() const {
    return curr_floor;
}

void Interface::set_floor(int floor) {
    if (0 <= floor && floor < world->num_floors()) {
        curr_floor = floor;
    }
    else {
        L_("Trying to set invalid floor: %d\n", floor);
    }
}
void Interface::draw_floor_selection() {
    // TODO draw other floors as well.
    stat_txt.setString("floor: " + to_string(curr_floor + 1) + "/" + to_string(world->num_floors()));
    stat_txt.setPosition(155, 15);
    stat_txt.setColor(sf::Color::White);
    window.draw(stat_txt);
}

void Interface::draw_resources() {
    // TODO specify from lua
    // Draw current state
    int xoff = 690;
    int yoff = 10;

    auto resources = world->get_resources();

    stat_txt.setColor(sf::Color::White);
    stat_txt.setPosition(510, yoff);
    stat_txt.setString(fmt("workers: %d/%d", world->num_workers(), resources.max_workers));
    window.draw(stat_txt);

    stat_txt.setColor(make_color(0x2F9C3F));
    stat_txt.setPosition(660, yoff);
    stat_txt.setString("$" + to_string(resources.money));
    window.draw(stat_txt);

    // Draw collected resources.
    int h = 16, curr_y = yoff + h + 5;
    draw_stats("Aluminium: ", resources.aluminium, make_color(0xF6926D), xoff, curr_y);
    curr_y += h;
    draw_stats("Coal: ", resources.coal, make_color(0xB6926D), xoff, curr_y);
    curr_y += h;
    draw_stats("Copper: ", resources.copper, make_color(0x924924), xoff, curr_y);
    curr_y += h;
    draw_stats("Diamond: ", resources.diamond, make_color(0x0092DB), xoff, curr_y);
    curr_y += h;
    draw_stats("Gold: ", resources.gold, make_color(0xFFB600), xoff, curr_y);
    curr_y += h;
    draw_stats("Iron: ", resources.iron, make_color(0xFFFFFF), xoff, curr_y);
    curr_y += h;
}

void Interface::draw_stats(string pre, int &val, sf::Color color, int x, int y) {
    stat_txt.setColor(sf::Color::White);
    stat_txt.setPosition(x, y);
    stat_txt.setString(pre);
    window.draw(stat_txt);
    int off = stat_txt.getGlobalBounds().width;

    stat_txt.setString(to_string(val));
    stat_txt.setColor(color);
    stat_txt.setPosition(x + off, y);
    window.draw(stat_txt);
}

} // Gui

