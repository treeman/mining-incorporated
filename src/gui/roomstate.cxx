#include "locator.hxx"
#include "butler.hxx"
#include "log.hxx"
#include "util/ext.hxx"
#include "gui/state.hxx"
#include "gui/interface.hxx"
#include "scene/world.hxx"
#include "scene/ore.hxx"
#include "scene/event.hxx"

namespace gui {

RoomState::RoomState(Interface *gui, scene::World *world) : State(gui, world), type(nullptr),
    selection(new Selection(
        world,
        gui,
        [this](WorldSelection sel) mutable {
            MapSelection mapsel = to_map(this->world, sel);

            L_("Marking!\n");

            assert(type != nullptr);
            unique_ptr<scene::Event> cmd(new scene::BuildRoomEvent(type, mapsel));
            this->world->push_event(std::move(cmd));
        },
        [](WorldSelection sel) { }))
{
    preview_spr.reset(new sf::Sprite(create_sprite("room_build_preview.png")));
}
void RoomState::reset() {
    selection->clear();
    type = nullptr;
}

void RoomState::handle_event(const gui::Event &e) {
    if (auto p = dynamic_cast<const RoomTypeEvent*>(&e)) {
        type = p->obj;
    }
}

bool RoomState::handle_input(const sf::Event &e) {
    selection->handle_input(e);
    return true;
}

void RoomState::update(const sf::Time &dt) {
    selection->show_debug();
}
void RoomState::draw(sf::RenderWindow &w) {
    if (!selection->want_remove() && selection->is_active()) {
        assert(type != nullptr);
        assert(preview_spr != nullptr);


        MapSelection sel = to_map(world, selection->get_area());
        for (MapPos mp : sel) {
            WindowPos winpos = world->map2window(mp);
            preview_spr->setPosition(winpos.x, winpos.y);
            if (world->can_build(mp, type)) {
                preview_spr->setColor(make_color(255, 255, 255, 150));
            }
            else {
                preview_spr->setColor(make_color(0xFF9E9E, 150));
            }
            w.draw(*preview_spr);
        }
    }
}

// TODO remove?
bool RoomState::can_build() const {
    MapSelection sel = to_map(world, selection->get_area());
    for (MapPos mp : sel) {
        if (!world->can_build(mp, type)) return false;
    }
    return true;
}

} // Gui

