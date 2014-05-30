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
        [this](scene::WorldArea sel) mutable {
            scene::MapArea mapsel = to_map(this->world, sel);

            assert(type != nullptr);
            unique_ptr<scene::Event> cmd(new scene::BuildRoomEvent(type, mapsel));
            this->world->push_event(std::move(cmd));
        },
        [this](scene::WorldArea sel) mutable {
            scene::MapArea mapsel = to_map(this->world, sel);

            unique_ptr<scene::Event> cmd(new scene::RemoveRoomEvent(mapsel));
            this->world->push_event(std::move(cmd));
        }))
{
    preview_spr.reset(new sf::Sprite(create_sprite("room_build_preview.png")));
    remove_spr.reset(new sf::Sprite(create_sprite("room_build_preview.png")));
    remove_spr->setColor(make_color(0xfaa5a5, 100));
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
    if (!selection->is_active()) return;

    if (!selection->want_remove()) {
        assert(type != nullptr);
        assert(preview_spr != nullptr);

        scene::MapArea sel = to_map(world, selection->get_area());
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
    else {
        assert(remove_spr != nullptr);

        scene::MapArea sel = to_map(world, selection->get_area());
        for (MapPos mp : sel) {
            if (world->get_room(mp) != nullptr) {
                WindowPos winpos = world->map2window(mp);
                remove_spr->setPosition(winpos.x, winpos.y);
                w.draw(*remove_spr);
            }
        }
    }
}

// TODO remove?
bool RoomState::can_build() const {
    scene::MapArea sel = to_map(world, selection->get_area());
    for (MapPos mp : sel) {
        if (!world->can_build(mp, type)) return false;
    }
    return true;
}

} // Gui

