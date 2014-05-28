#include "locator.hxx"
#include "butler.hxx"
#include "util/ext.hxx"
#include "gui/state.hxx"
#include "gui/interface.hxx"
#include "scene/world.hxx"
#include "scene/ore.hxx"
#include "scene/event.hxx"

namespace gui {

MineState::MineState(Interface *gui, scene::World *world) : State(gui, world),
    selection(new Selection(
        world,
        gui,
        [this](WorldSelection sel) mutable {
            MapSelection mapsel = to_map(this->world, sel);

            unique_ptr<scene::Event> cmd(new scene::MineEvent(mapsel));
            this->world->push_event(std::move(cmd));
        },
        [](WorldSelection) {}
    ))
{
    preview_spr.reset(new sf::Sprite(create_sprite("mine_selection_preview.png")));
}

void MineState::reset() {
    selection->clear();
}

bool MineState::handle_input(const sf::Event &e) {
    selection->handle_input(e);
    return true;
}

void MineState::update(const sf::Time &dt) {
    selection->show_debug();
}
void MineState::draw(sf::RenderWindow &w) {
    if (!selection->want_remove() && selection->is_active()) {
        MapSelection sel = to_map(world, selection->get_area());
        for (MapPos mp : sel) {
            WindowPos p = world->map2window(mp);
            preview_spr->setPosition(p.x, p.y);
            if (world->can_mine(mp)) {
                preview_spr->setColor(sf::Color(255, 255, 255, 100));
            }
            else {
                // TODO move color to lua
                preview_spr->setColor(make_color(0xFF9E9E, 150));
            }
            w.draw(*preview_spr);
        }
    }
}

} // Gui

