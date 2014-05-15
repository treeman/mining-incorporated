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
    current_state(nullptr)
{
    // Setup guistates.
    states.resize(static_cast<unsigned>(GuiState::NUM_STATES));
    states[static_cast<unsigned>(GuiState::INFO)].reset(new InfoState(this, world));
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

// Old stuff

#if 0
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

    auto curr = world->window2map(wp).pos;
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

void Interface::draw_floor_selection() {
    const int floor = world->get_curr_floor();
    txt.setString("floor: " + to_string(floor));
    txt.setPosition(155, 15);
    txt.setColor(sf::Color::White);
    window.draw(txt);
}

void Interface::set_floor(int floor) {
    if (0 <= floor && floor < world->num_floors()) {
        world->set_curr_floor(floor);
    }
}

#endif

} // Gui

