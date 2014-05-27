#include "locator.hxx"
#include "util/ext.hxx"
#include "gui/state.hxx"
#include "gui/interface.hxx"
#include "scene/world.hxx"
#include "scene/ore.hxx"
#include "scene/event.hxx"

namespace gui {

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
        for (MapPos mp : sel) {
            WindowPos winpos = world->map2window(mp);
            preview_spr->setPosition(winpos.x, winpos.y);
            if (world->can_build(mp, material)) {
                preview_spr->setColor(make_color(255, 255, 255, 150));
            }
            else {
                // TODO move color to lua
                preview_spr->setColor(make_color(0xFF9E9E, 150));
            }
            w.draw(*preview_spr);
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

} // Gui

