#include "butler.hxx"
#include "constants.hxx"
#include "locator.hxx"
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
}

scene::World &Interface::get_world() const {
    assert(world != nullptr);
    return *world;
}

// TODO block on interactions
bool Interface::handle_input(const sf::Event &e) {
    panel.handle_input(e);
    current_state->handle_input(e);

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
void Interface::draw(sf::RenderWindow &w) {
    current_state->draw(w);
    panel.draw(w);
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
    /*
    // TODO draw other floors as well.
    txt.setString("floor: " + to_string(curr_floor));
    txt.setPosition(155, 15);
    txt.setColor(sf::Color::White);
    window.draw(txt);
    */
}

// Old stuff

#if 0

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

#endif

} // Gui

