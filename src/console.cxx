#include <iostream>
#include "console.hxx"

Console::Console(sf::RenderWindow &w, Settings &s) : window(w), settings(s), is_active(false),
    history(10, 10, 300, 500), input(10, 520)
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
            else if (e.key.code == sf::Keyboard::Return) {
                execute_cmd();
            }
            else if (e.key.code == sf::Keyboard::BackSpace) {
                input.del_char();
            }
            break;
        case sf::Event::TextEntered:
            if (e.text.unicode >= 32) {
                input.add_char(e.text.unicode);
            }
            break;
        default: break;
    }

    return true;
}
void Console::update(const sf::Time &dt) {

}
void Console::draw() {
    if (is_active) {
        history.draw(window);
        input.draw(window);
    }
}

void Console::new_setting(string key, string val) {
    history.add_line(key + " = " + val);
}

void Console::execute_cmd() {
    string cmd = input.get_string();
    if (!cmd.empty()) {
        // TODO do some things
        history.add_line(cmd);
        input.clear();
    }
}

