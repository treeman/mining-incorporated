#include "help.hxx"
#include "butler.hxx"
#include "currentstate.hxx"

HelpState::HelpState(sf::RenderWindow &w) : State(w) {
    txt = create_txt("pf_tempesta_seven.ttf", 40, "Mining Incorporated");
    txt.setPosition(140, 40);
    //pic = create_sprite("help.png");
}

void HelpState::handle_input(const sf::Event &e) {
    switch (e.type) {
        case sf::Event::KeyPressed:
            if (e.key.code == sf::Keyboard::Space)
                pop_state();
            break;
        default: break;
    }
}
void HelpState::update(const sf::Time &dt) {
}
void HelpState::draw() {
    window.draw(txt);
    //window.draw(pic);
}

