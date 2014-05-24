#include "locator.hxx"
#include "util/ext.hxx"
#include "gui/state.hxx"
#include "gui/interface.hxx"
#include "scene/world.hxx"
#include "scene/ore.hxx"
#include "scene/event.hxx"

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
        auto ground = tile->get_ground();

        // TODO make something more persistent.
        if (auto ore = dynamic_cast<const scene::Ore*>(ground)) {
            D_.tmp(fmt("ore: %s", ore->key));
        }
        else {
            D_.tmp(fmt("ground: %s", ground->key));
        }

        // TODO more printouts!
        shared_ptr<scene::Worker> worker(world->select_worker(world_pos));
        if (worker != nullptr) {
            D_.tmp("Hovering over worker!");
        }
        if (selected_worker != nullptr) {
            D_.tmp("worker selected");
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

MaterialState::MaterialState(Interface *gui, scene::World *world) : State(gui, world), //obj(nullptr),
    selection(new Selection(
        world,
        gui,
        [this](WorldSelection sel) mutable {
            MapSelection mapsel = to_map(this->world, sel);

            assert(material != nullptr);
            unique_ptr<scene::Event> cmd(new scene::BuildMaterialEvent(material, mapsel));
            this->world->push_event(std::move(cmd));
        },
        [](WorldSelection sel) { }))
{
    txt.reset(new sf::Text(create_txt("consola.ttf", 14)));
}
void MaterialState::reset() {
    selection->clear();
    material = nullptr;
}

void MaterialState::handle_event(const gui::Event &e) {
    if (auto p = dynamic_cast<const GroundMaterialObjectEvent*>(&e)) {
        material = p->obj;
        preview_spr.reset(new sf::Sprite(create_sprite(material->ground->spr)));
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
    if (!selection->want_remove() && selection->is_active()) {
        assert(material != nullptr);
        assert(preview_spr != nullptr);

        MapSelection sel = to_map(world, selection->get_area());
        for (int x = sel.start.pos.x; x <= sel.end.pos.x; ++x) {
            for (int y = sel.start.pos.y; y <= sel.end.pos.y; ++y) {
                WindowPos p = world->map2window(MapPos(x, y, gui->current_floor()));
                preview_spr->setPosition(p.x, p.y);
                preview_spr->setColor(make_color(255, 255, 255, 150));
                w.draw(*preview_spr);
            }
        }

        int preview_cost = sel.area<int>() * material->cost;
        if (preview_cost > 0) {
            WindowPos preview_pos = selection->get_outside_txt_pos();
            txt->setPosition(preview_pos);
            txt->setString("$" + to_string(preview_cost));
            w.draw(*txt);
        }
    }
}

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
        for (int x = sel.start.pos.x; x <= sel.end.pos.x; ++x) {
            for (int y = sel.start.pos.y; y <= sel.end.pos.y; ++y) {
                auto tile = world->get_tile(MapPos(x, y, sel.start.floor));
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
                WindowPos p = world->map2window(MapPos(x, y, sel.start.floor));
                obj->set_pos(p.x, p.y);
                obj->draw(w);
            }
        }
    }
}

} // Gui

