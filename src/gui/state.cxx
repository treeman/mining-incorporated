#include "locator.hxx"
#include "util/ext.hxx"
#include "gui/state.hxx"
#include "gui/interface.hxx"
#include "world/world.hxx"
#include "world/ore.hxx"

namespace Gui {

State::State() : gui(nullptr), world(nullptr) {

}

void State::init(Interface *_gui, World *_world) {
    gui = _gui;
    world = _world;
}

string type2string(GuiState type) {
    switch (type) {
        case GuiState::INFO: return "Info";
        case GuiState::PLANNING: return "Planning";
        default: return "Invalid";
    }
}

void InfoState::reset() {

}
bool InfoState::handle_input(const sf::Event &e) {
    return true;
}
void InfoState::update(const sf::Time &dt) {
    D_.tmp("updating");
    const WindowPos wp(get_mpos());
    if (world->in_world(wp)) {
        const WorldPos world_pos(world->window2world(wp));
        const MapPos dim_pos(world->world2map(world_pos));

        shared_ptr<Tile> tile(world->get_tile(dim_pos));
        auto ground = tile->get_ground();

        // TODO make something more persistent.
        if (auto ore = dynamic_cast<const Ore*>(ground)) {
            D_.tmp(fmt("ore: %s", ore->key));
        }
        else {
            D_.tmp(fmt("ground: %s", ground->key));
        }

        shared_ptr<Worker> worker(world->select_closest_worker(world_pos));
        if (worker != nullptr) {
            D_.tmp("Some worker!");
        }
    }
}
void InfoState::draw(sf::RenderWindow &w) {

}

void PlanningState::reset() {

}

void PlanningState::handle_event(const Gui::Event &e) {
    L_("Recieved event: %s\n", e.to_string());
}

bool PlanningState::handle_input(const sf::Event &e) {
    return true;
}
void PlanningState::update(const sf::Time &dt) {

}
void PlanningState::draw(sf::RenderWindow &w) {

}

} // Gui
