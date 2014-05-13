#include "locator.hxx"
#include "gui/buttonpanel.hxx"
#include "gui/picbutton.hxx"
#include "gui/interface.hxx"

namespace Gui {

ButtonPanel::ButtonPanel(Interface &_gui) : gui(_gui), curr(0) {
    unique_ptr<List>(new List(12, 588)).swap(categories);
    categories->add(shared_ptr<BoundedObject>(new PicButton([](BaseButton &button) mutable {
            L_("Mine");
        }, "Mine")));
    categories->add(shared_ptr<BoundedObject>(new PicButton([](BaseButton &button) mutable {
            L_("Material");
        }, "Material")));
    categories->add(shared_ptr<BoundedObject>(new PicButton([](BaseButton &button) mutable {
            L_("Rooms");
        }, "Rooms")));
    categories->add(shared_ptr<BoundedObject>(new PicButton([](BaseButton &button) mutable {
            L_("Staff");
        }, "Staff")));
    categories->add(shared_ptr<BoundedObject>(new PicButton([](BaseButton &button) mutable {
            L_("Utilities");
        }, "Utilities")));
    categories->add(shared_ptr<BoundedObject>(new PicButton([](BaseButton &button) mutable {
            L_("Planning");
        }, "Planning")));
    //unique_ptr<List> list;
    //vector<unique_ptr<List>> subcategories;
}

bool handle_input(const sf::Event &) {
    return true;
}

void ButtonPanel::update(const sf::Time &dt) {
    categories->update(dt);
    //assert(0 <= curr && curr < (int)subcategories.size());
    //subcategories[curr]->update(dt);
}
void ButtonPanel::draw(sf::RenderWindow &w) {
    categories->draw(w);
    //assert(0 <= curr && curr < (int)subcategories.size());
    //subcategories[curr]->draw(w);
}

}

