#include <iostream>
#include "console.hxx"

Console::Console(sf::RenderWindow &w, Settings &s) : window(w), settings(s), is_active(false),
    history(10, 10, 300, 500)
{
    settings.register_global_callback([=](string key, string val) {
            this->new_setting(key, val);
        });
}
void Console::activate() { is_active = true; }
void Console::deactivate() { is_active = false; }

bool Console::handle_input(const sf::Event &e) {
    if (!is_active) {
        if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::F1) {
            activate();
            return false;
        }
    }

    if (!is_active) return true;

    switch (e.type) {
        case sf::Event::KeyPressed:
            if (e.key.code == sf::Keyboard::F1) {
                deactivate();
                return false;
            }
            else if (e.key.code == sf::Keyboard::Space) {
                history.add_line("line");
            }
        default: break;
    }

    return true;
}
void Console::update(const sf::Time &dt) {

}
void Console::draw() {
    if (is_active)
        history.draw(window);
}

void Console::new_setting(string key, string val) {
    history.add_line(key + " = " + val);
}
