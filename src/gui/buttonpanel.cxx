#include "locator.hxx"
#include "gui/buttonpanel.hxx"
#include "gui/picbutton.hxx"
#include "gui/interface.hxx"
#include "scene/world.hxx"

using PType = scene::PlanningType;

namespace gui {

ButtonPanel::ButtonPanel(Interface &_gui) : gui(_gui), curr(Categories::UNSELECTED) {
    // TODO load from lua
    unique_ptr<List>(new List(12, 588)).swap(categories);

    subcategories.resize(static_cast<int>(Categories::NUM_CATEGORIES));
    categories->add(shared_ptr<BoundedObject>(
        new PicButton(make_category_selector(Categories::UNSELECTED), "mine"))
    );

    init_material_button();
    categories->add(shared_ptr<BoundedObject>(
        new PicButton(make_category_selector(Categories::UNSELECTED), "rooms"))
    );
    categories->add(shared_ptr<BoundedObject>(
        new PicButton(make_category_selector(Categories::UNSELECTED), "objects"))
    );
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

// TODO may cause some buttons to have to be clicked on twice.
function<void(BaseButton &button)> ButtonPanel::make_category_selector(Categories cat) {
    return [this, cat](BaseButton &button) mutable {
        if (curr != Categories::UNSELECTED) {
            int sel = static_cast<int>(curr);
            assert(0 <= sel && sel < (int)subcategories.size());
            assert(subcategories[sel] != nullptr);
            //L_("deselecting prev: %d\n", sel);
            subcategories[sel]->deselect();
        }

        L_("selecting: %d\n", static_cast<int>(cat));

        button.toggle_selection();
        if (button.is_selected()) {
            curr = cat;
        }
        else {
            curr = Categories::UNSELECTED;
            gui.set_state(GuiState::INFO);
        }
    };
}

void ButtonPanel::init_material_button() {
    categories->add(shared_ptr<BoundedObject>(
        new PicButton(make_category_selector(Categories::MATERIAL), "material"))
    );
    unique_ptr<List> cat(new List(12, 525));

    // TODO load buttons from material.lua

    subcategories[static_cast<int>(Categories::MATERIAL)].swap(cat);
}
void ButtonPanel::init_planning_button() {
    categories->add(shared_ptr<BoundedObject>(
        new PicButton(make_category_selector(Categories::PLANNING), "planning"))
    );
    // TODO in order!
    // TODO cleanup!
    unique_ptr<List> cat(new List(12, 525));
    cat->add(shared_ptr<BoundedObject>(new PicButton([this](BaseButton &button) {
        L_("Plan room\n");
        gui.set_state(GuiState::PLANNING);
        auto x = Locator::get_object_factory().create_planning_object(PType::ROOM);
        gui.handle_event(PlanningObjectEvent(move(x)));
    }, "room")));
    cat->add(shared_ptr<BoundedObject>(new PicButton([this](BaseButton &button) {
        L_("Plan object\n");
        gui.set_state(GuiState::PLANNING);
        auto x = Locator::get_object_factory().create_planning_object(PType::OBJECT);
        gui.handle_event(PlanningObjectEvent(move(x)));
    }, "object")));
    subcategories[static_cast<int>(Categories::PLANNING)].swap(cat);
}

}; // gui

