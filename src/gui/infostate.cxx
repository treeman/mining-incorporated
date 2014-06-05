#include "log.hxx"
#include "locator.hxx"
#include "util/ext.hxx"
#include "gui/state.hxx"
#include "gui/interface.hxx"
#include "scene/world.hxx"
#include "scene/ore.hxx"
#include "scene/event.hxx"

namespace gui {

InfoState::InfoState(Interface *gui, scene::World *world) : State(gui, world), selected_worker{nullptr} {

}
bool InfoState::handle_input(const sf::Event &e) {
    switch (e.type) {
        case sf::Event::MouseButtonPressed:
            if (e.mouseButton.button == sf::Mouse::Button::Left) {
                left_click(WindowPos(e.mouseButton.x, e.mouseButton.y));
            }
            break;
        default: break;
    }
    return true;
}
void InfoState::update(const sf::Time &dt) {
    D_.tmp("updating");
    const WindowPos wp(get_mpos());
    const int floor = gui->current_floor();
    if (world->in_world(wp, floor)) {
        const WorldPos world_pos(world->window2world(wp, floor));
        const MapPos dim_pos(world->world2map(world_pos));

        shared_ptr<scene::Tile> tile(world->get_tile(dim_pos));
        const scene::Ground *ground = tile->get_ground();
        assert(ground != nullptr);

        // TODO make something more persistent.
        if (auto ore = dynamic_cast<const scene::Ore*>(ground)) {
            D_.tmp(fmt("ore: %s", ore->key));
        }
        else {
            D_.tmp(fmt("ground: %s", ground->key));
        }

        auto room = world->get_room(dim_pos);
        if (room != nullptr) {
            D_.tmp(fmt("room: %s", room->to_string()));
        }

        // TODO more printouts!
        shared_ptr<scene::Worker> worker(world->select_worker(world_pos));
        if (worker != nullptr) {
            //D_.tmp("Hovering over worker!");
            //worker->debug();
        }
        if (selected_worker != nullptr) {
            //D_.tmp("worker selected");
            selected_worker->debug();
        }
    }
}
void InfoState::draw(sf::RenderWindow &w) {

}
void InfoState::left_click(const WindowPos &p) {
    const int f = gui->current_floor();
    if (world->in_world(p, f)) {
        auto wpos = world->window2world(p, f);
        selected_worker = world->select_worker(wpos);
    }
}


} // Gui

