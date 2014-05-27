#include "locator.hxx"
#include "util/ext.hxx"
#include "gui/state.hxx"
#include "gui/interface.hxx"
#include "scene/world.hxx"
#include "scene/ore.hxx"
#include "scene/event.hxx"

namespace gui {

PlanningState::PlanningState(Interface *gui, scene::World *world) : State(gui, world), obj(nullptr),
    selection(new Selection(
        world,
        gui,
        [this](WorldSelection sel) mutable {
            MapSelection mapsel = to_map(this->world, sel);

            unique_ptr<scene::Event> cmd(new scene::PlacePlanningEvent(obj, mapsel));
            this->world->push_event(std::move(cmd));
        },
        [this](WorldSelection sel) mutable {
            MapSelection mapsel = to_map(this->world, sel);

            unique_ptr<scene::Event> cmd(new scene::RemovePlanningEvent(mapsel));
            this->world->push_event(std::move(cmd));
        }))
{
}

void PlanningState::reset() {
    selection->clear();
    obj = nullptr;
}

void PlanningState::handle_event(const gui::Event &e) {
    if (auto p = dynamic_cast<const PlanningObjectEvent*>(&e)) {
        //L_("Recieved event: %s\n", p->to_string());
        obj = p->obj;
    }
}

bool PlanningState::handle_input(const sf::Event &e) {
    selection->handle_input(e);
    return true;
}

void PlanningState::update(const sf::Time &dt) {
    // Suppress drawing of preview objects if we want to delete
    if (selection->want_remove() && selection->is_active()) {
        MapSelection sel = to_map(world, selection->get_area());
        for (MapPos mp : sel) {
            auto tile = world->get_tile(mp);
            tile->suppress_preview();
        }
    }

    selection->show_debug();
}
void PlanningState::draw(sf::RenderWindow &w) {
    if (!selection->want_remove() && selection->is_active()) {
        assert(obj != nullptr);

        MapSelection sel = to_map(world, selection->get_area());
        for (MapPos mp : sel) {
            WindowPos p = world->map2window(mp);
            obj->set_pos(p.x, p.y);
            obj->draw(w);
        }
    }
}

} // Gui

