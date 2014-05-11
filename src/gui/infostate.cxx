#include "gui/infostate.hxx"
#include "util/ext.hxx"
#include "world/world.hxx"
#include "locator.hxx"
#include "world/ore.hxx"
#include "world/ground.hxx"

namespace Gui {

bool InfoState::handle_input(const sf::Event &e) {
    return true;
}
void InfoState::update(const sf::Time &dt) {
    D_.tmp("updating");
    const WindowPos wp(get_mpos());
    if (world->in_world(wp)) {
        const WorldPos world_pos(world->window2world(wp));
        const DimensionPos dim_pos(world->world2dimension(world_pos));

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

}

