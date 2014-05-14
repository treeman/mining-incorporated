#include "locator.hxx"
#include "util/ext.hxx"
#include "gui/state.hxx"
#include "gui/interface.hxx"
#include "scene/world.hxx"
#include "scene/ore.hxx"

namespace gui {

State::State() : gui(nullptr), world(nullptr) {

}

void State::init(Interface *_gui, scene::World *_world) {
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
        shared_ptr<scene::Worker> worker(world->select_closest_worker(world_pos));
        if (worker != nullptr) {
            D_.tmp("Some worker!");
        }
    }
}
void InfoState::draw(sf::RenderWindow &w) {

}

PlanningState::PlanningState() : obj(nullptr) {

}
void PlanningState::reset() {
    selection.clear();
    obj = nullptr;
}

void PlanningState::handle_event(const gui::Event &e) {
    if (auto p = dynamic_cast<const PlanningObjectEvent*>(&e)) {
        L_("Recieved event: %s\n", p->to_string());
        obj = p->obj;
    }
}

bool PlanningState::handle_input(const sf::Event &e) {
    switch (e.type) {
        case sf::Event::MouseMoved:
            move(WindowPos(e.mouseMove.x, e.mouseMove.y));
            break;
        case sf::Event::MouseButtonPressed:
            if (e.mouseButton.button == sf::Mouse::Button::Left) {
                left_click(WindowPos(e.mouseButton.x, e.mouseButton.y));
            }
            else if (e.mouseButton.button == sf::Mouse::Button::Right) {
                right_click(WindowPos(e.mouseButton.x, e.mouseButton.y));
            }
            break;
        case sf::Event::MouseButtonReleased:
            if (e.mouseButton.button == sf::Mouse::Button::Left) {
                left_release(WindowPos(e.mouseButton.x, e.mouseButton.y));
            }
            else if (e.mouseButton.button == sf::Mouse::Button::Right) {
                right_release(WindowPos(e.mouseButton.x, e.mouseButton.y));
            }
            break;
        default: break;
    }
    return true;
}

void PlanningState::move(const WindowPos &p) {
    if (world->in_world(p))
        selection.extend(world->window2world(p));
}
void PlanningState::left_click(const WindowPos &p) {
    if (world->in_world(p)) {
        selection.begin(world->window2world(p));
    }
}
void PlanningState::right_click(const WindowPos &p) {

}
void PlanningState::left_release(const WindowPos &p) {
    // Can cancel selection by holding right and releasing
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        selection.clear();
    }
    else if (selection.is_active()) {
        // TODO Execute selection
        MapSelection sel = to_map(world, selection.get_area());
        L_("Executing %s\n", sel.to_string());
        selection.clear();
    }
}
void PlanningState::right_release(const WindowPos &p) {

}

void PlanningState::update(const sf::Time &dt) {
    D_.tmp("world sel: " + selection.to_string());
    if (selection.is_active()) {
        MapSelection sel = to_map(world, selection.get_area());
        D_.tmp("map sel: " + sel.to_string());
    }
}
void PlanningState::draw(sf::RenderWindow &w) {

}

} // Gui

