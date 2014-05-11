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
        // TODO make something more persistent.
        const DimensionPos p(world->window2dimension(wp));
        shared_ptr<Tile> tile(world->get_tile(p));
        TilePos tp(tile->get_pos());
        auto ground = tile->get_ground();

        if (auto ore = dynamic_cast<const Ore*>(ground)) {
            D_.tmp(fmt("ore: %s", ore->key));
        }
        else {
            D_.tmp(fmt("ground: %s", ground->key));
        }
    }
}
void InfoState::draw(sf::RenderWindow &w) {

}

}

