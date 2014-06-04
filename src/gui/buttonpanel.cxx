#include "log.hxx"
#include "gui/selection.hxx"
#include "gui/buttonpanel.hxx"
#include "gui/picbutton.hxx"
#include "gui/interface.hxx"
#include "scene/world.hxx"
#include "scene/material.hxx"
#include "scene/roomtype.hxx"
#include "scene/objecttype.hxx"
#include "scene/objectfactory.hxx"

using PType = scene::PlanningType;

namespace gui {

ButtonPanel::ButtonPanel(Interface &_gui) : gui(_gui), curr(Categories::UNSELECTED) {
    // TODO load from lua
    unique_ptr<List>(new List(12, 588)).swap(categories);

    subcategories.resize(static_cast<int>(Categories::NUM_CATEGORIES));
    categories->add(shared_ptr<BoundedObject>(
        new PicButton([this](BaseButton &button) mutable {
                deselect_categories();
                gui.set_state(GuiState::MINE);
            }, "mine"))
    );

    init_material_button();
    init_room_button();
    init_objects_button();
    categories->add(shared_ptr<BoundedObject>(
        new PicButton(make_category_selector(Categories::UNSELECTED), "staff"))
    );
    categories->add(shared_ptr<BoundedObject>(
        new PicButton(make_category_selector(Categories::UNSELECTED), "utilities"))
    );
    init_planning_button();
}

bool ButtonPanel::handle_input(const sf::Event &e) {
    categories->handle_input(e);
    if (curr != Categories::UNSELECTED) {
        int sel = static_cast<int>(curr);
        assert(0 <= sel && sel < (int)subcategories.size());
        assert(subcategories[sel] != nullptr);
        subcategories[sel]->handle_input(e);
    }

    // TODO
    return true;
}
// TODO remove?
bool ButtonPanel::mark_hover(const WindowPos &p) {
    return true;
}
bool ButtonPanel::click(const WindowPos &p) {
    return true;
}

void ButtonPanel::update(const sf::Time &dt) {
    categories->update(dt);
    if (curr != Categories::UNSELECTED) {
        int sel = static_cast<int>(curr);
        assert(0 <= sel && sel < (int)subcategories.size());
        assert(subcategories[sel] != nullptr);
        subcategories[sel]->update(dt);
    }
}
void ButtonPanel::draw(sf::RenderWindow &w) {
    categories->draw(w);
    if (curr != Categories::UNSELECTED) {
        int sel = static_cast<int>(curr);
        assert(0 <= sel && sel < (int)subcategories.size());
        assert(subcategories[sel] != nullptr);
        subcategories[sel]->draw(w);
    }
}

void ButtonPanel::deselect_categories() {
    categories->deselect();
    curr = Categories::UNSELECTED;
}

// XXX This need to be reworked if we want buttons and not only categories.
// Assumes that is the case and forces deselect on every interaction,
// to prevent buttons having to be clicked twice.
function<void(BaseButton &button)> ButtonPanel::make_category_selector(Categories cat) {
    return [this, cat](BaseButton &button) mutable {
        bool sel = button.is_selected();

        if (curr != Categories::UNSELECTED) {
            int sel = static_cast<int>(curr);
            assert(0 <= sel && sel < (int)subcategories.size());
            assert(subcategories[sel] != nullptr);
            //L_("deselecting prev: %d\n", sel);
            subcategories[sel]->deselect();
        }

        //L_("selecting: %d\n", static_cast<int>(cat));

        deselect_categories();
        if (sel) {
            gui.set_state(GuiState::INFO);
        }
        else {
            button.select();
            curr = cat;
        }
    };
}

void ButtonPanel::init_material_button() {
    categories->add(shared_ptr<BoundedObject>(
        new PicButton(make_category_selector(Categories::MATERIAL), "material"))
    );
    unique_ptr<List> cat(new List(12, 525));

    string path = "material.lua";
    LuaState L;
    L.dofile(path);

    lua_getglobal(L, "material");
    if (!lua_istable(L, -1))
        throw lua_parse_error(path, fmt("material not a table."));

    for (lua_pushnil(L); lua_next(L, -2); lua_pop(L, 1)) {
        string key = lua_tostring(L, -2);
        if (!lua_istable(L, -1))
            throw lua_parse_error(path, fmt("material: %s not a table.", key));

        string ground = L.require_string("ground", fmt("ground missing from %s", key));
        int cost = (int)L.require_num("cost", fmt("cost missing from %s", key));

        shared_ptr<scene::Material> material(new scene::Material(
                    Locator::get_object_factory().get_ground(ground), cost));

        cat->add(shared_ptr<BoundedObject>(new PicButton([this, material, key](BaseButton &button) {
            gui.set_state(GuiState::MATERIAL);
            gui.handle_event(GroundMaterialObjectEvent(material));
        }, key)));
    }
    lua_pop(L, 1);
    assert(L.stack_size() == 0);

    subcategories[static_cast<int>(Categories::MATERIAL)].swap(cat);
}
void ButtonPanel::init_room_button() {
    categories->add(shared_ptr<BoundedObject>(
        new PicButton(make_category_selector(Categories::ROOM), "rooms"))
    );
    unique_ptr<List> cat(new List(12, 525));

    string path = "rooms.lua";
    LuaState L;
    L.dofile(path);

    lua_getglobal(L, "rooms");
    if (!lua_istable(L, -1))
        throw lua_parse_error(path, fmt("rooms not a table."));

    for (lua_pushnil(L); lua_next(L, -2); lua_pop(L, 1)) {
        string key = lua_tostring(L, -2);
        if (!lua_istable(L, -1))
            throw lua_parse_error(path, fmt("rooms: %s not a table.", key));

        shared_ptr<scene::RoomType> type(new scene::RoomType());
        type->name = key;

        cat->add(shared_ptr<BoundedObject>(new PicButton([this, type, key](BaseButton &) {
            gui.set_state(GuiState::ROOM);
            gui.handle_event(RoomTypeEvent(type));
        }, key)));
    }
    lua_pop(L, 1);
    assert(L.stack_size() == 0);

    subcategories[static_cast<int>(Categories::ROOM)].swap(cat);
}

void ButtonPanel::init_objects_button() {
    categories->add(shared_ptr<BoundedObject>(
        new PicButton(make_category_selector(Categories::OBJECTS), "objects"))
    );
    unique_ptr<List> cat(new List(12, 525));

    for (auto o : Locator::get_object_factory().get_buildable_objects()) {
        cat->add(shared_ptr<BoundedObject>(new PicButton([this, o](BaseButton &) {
            gui.set_state(GuiState::OBJECTS);
            gui.handle_event(ObjectTypeEvent(o));
        }, o->name)));
    }

    /*
    string path = "objects.lua";
    LuaState L;
    L.dofile(path);

    lua_getglobal(L, "objects");
    if (!lua_istable(L, -1))
        throw lua_parse_error(path, fmt("objects not a table."));

    for (lua_pushnil(L); lua_next(L, -2); lua_pop(L, 1)) {
        string key = lua_tostring(L, -2);
        if (!lua_istable(L, -1))
            throw lua_parse_error(path, fmt("objects: %s not a table.", key));

        shared_ptr<scene::ObjectType> type(new scene::ObjectType());
        type->name = key;

        type->spr = L.require_string("sprite", fmt("sprite missing from %s", key));

        cat->add(shared_ptr<BoundedObject>(new PicButton([this, type, key](BaseButton &) {
            gui.set_state(GuiState::OBJECTS);
            gui.handle_event(ObjectTypeEvent(type));
        }, key)));
    }
    lua_pop(L, 1);
    assert(L.stack_size() == 0);
    */

    subcategories[static_cast<int>(Categories::OBJECTS)].swap(cat);
}

void ButtonPanel::init_planning_button() {
    categories->add(shared_ptr<BoundedObject>(
        new PicButton(make_category_selector(Categories::PLANNING), "planning"))
    );
    // TODO in order!
    // TODO cleanup!
    unique_ptr<List> cat(new List(12, 525));
    cat->add(shared_ptr<BoundedObject>(new PicButton([this](BaseButton &button) {
        gui.set_state(GuiState::PLANNING);
        auto x = Locator::get_object_factory().create_planning_object(PType::ROOM);
        gui.handle_event(PlanningObjectEvent(move(x)));
    }, "room")));
    cat->add(shared_ptr<BoundedObject>(new PicButton([this](BaseButton &button) {
        gui.set_state(GuiState::PLANNING);
        auto x = Locator::get_object_factory().create_planning_object(PType::OBJECT);
        gui.handle_event(PlanningObjectEvent(move(x)));
    }, "object")));
    subcategories[static_cast<int>(Categories::PLANNING)].swap(cat);
}

}; // gui

