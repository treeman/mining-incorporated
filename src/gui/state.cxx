#include "locator.hxx"
#include "util/ext.hxx"
#include "gui/state.hxx"
#include "gui/interface.hxx"
#include "scene/world.hxx"
#include "scene/ore.hxx"
#include "scene/command.hxx"

namespace gui {

State::State(Interface *_gui, scene::World *_world) : gui(_gui), world(_world) {

}

string type2string(GuiState type) {
    switch (type) {
        case GuiState::INFO: return "Info";
        case GuiState::MATERIAL: return "Material";
        case GuiState::PLANNING: return "Planning";
        case GuiState::NUM_STATES: return "Invalid GuiState";
        default: return "Unknown GuiState";
    }
}

InfoState::InfoState(Interface *gui, scene::World *world) : State(gui, world) {

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

        shared_ptr<scene::Tile> tile(world->get_tile(dim_pos));
        auto ground = tile->get_ground();

        // TODO make something more persistent.
        if (auto ore = dynamic_cast<const scene::Ore*>(ground)) {
            D_.tmp(fmt("ore: %s", ore->key));
        }
        else {
            D_.tmp(fmt("ground: %s", ground->key));
        }

        // TODO should select worker by bounding box
        //shared_ptr<scene::Worker> worker(world->select_closest_worker(world_pos));
        //if (worker != nullptr) {
            //D_.tmp("Some worker!");
        //}
    }
}
void InfoState::draw(sf::RenderWindow &w) {

}

MaterialState::MaterialState(Interface *gui, scene::World *world) : State(gui, world), //obj(nullptr),
    selection(new Selection(world,
        [this](WorldSelection sel) mutable {
            MapSelection mapsel = to_map(this->world, sel);

            assert(material != nullptr);
            unique_ptr<scene::Command> cmd(new scene::BuildMaterialCommand(material, mapsel));
            this->world->push_cmd(std::move(cmd));
        },
        [](WorldSelection sel) { }))
{
}
void MaterialState::reset() {
    selection->clear();
    material = nullptr;
}

void MaterialState::handle_event(const gui::Event &e) {
    if (auto p = dynamic_cast<const GroundMaterialObjectEvent*>(&e)) {
        material = p->obj;
    }
}

bool MaterialState::handle_input(const sf::Event &e) {
    selection->handle_input(e);
    return true;
}

void MaterialState::update(const sf::Time &dt) {
    selection->show_debug();
}
void MaterialState::draw(sf::RenderWindow &w) {
    /*if (!selection->want_remove() && selection->is_active()) {
        assert(obj != nullptr);

        MapSelection sel = to_map(world, selection->get_area());
        for (int x = sel.start.pos.x; x <= sel.end.pos.x; ++x) {
            for (int y = sel.start.pos.y; y <= sel.end.pos.y; ++y) {
                WindowPos p = world->map2window(MapPos(x, y, world->get_curr_floor()));
                obj->set_pos(p.x, p.y);
                obj->draw(w);
            }
        }
    }
    */
}

PlanningState::PlanningState(Interface *gui, scene::World *world) : State(gui, world), obj(nullptr),
    selection(new Selection(world,
        [this](WorldSelection sel) mutable {
            MapSelection mapsel = to_map(this->world, sel);

            unique_ptr<scene::Command> cmd(new scene::PlacePlanningCommand(obj, mapsel));
            this->world->push_cmd(std::move(cmd));
        },
        [this](WorldSelection sel) mutable {
            MapSelection mapsel = to_map(this->world, sel);

            unique_ptr<scene::Command> cmd(new scene::RemovePlanningCommand(mapsel));
            this->world->push_cmd(std::move(cmd));
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
        for (int x = sel.start.pos.x; x <= sel.end.pos.x; ++x) {
            for (int y = sel.start.pos.y; y <= sel.end.pos.y; ++y) {
                auto tile = world->get_tile(MapPos(x, y, world->get_curr_floor()));
                tile->suppress_preview();
            }
        }
    }

    selection->show_debug();
}
void PlanningState::draw(sf::RenderWindow &w) {
    if (!selection->want_remove() && selection->is_active()) {
        assert(obj != nullptr);

        MapSelection sel = to_map(world, selection->get_area());
        for (int x = sel.start.pos.x; x <= sel.end.pos.x; ++x) {
            for (int y = sel.start.pos.y; y <= sel.end.pos.y; ++y) {
                WindowPos p = world->map2window(MapPos(x, y, world->get_curr_floor()));
                obj->set_pos(p.x, p.y);
                obj->draw(w);
            }
        }
    }
}

} // Gui

