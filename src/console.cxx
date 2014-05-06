#include <iostream>
#include "console.hxx"
#include "locator.hxx"
#include "string.hxx"

Console::Console(sf::RenderWindow &w) : window(w), is_active(false),
    history(10, 10, 300, 500), input(10, 520)
{
    Settings &settings = Locator::get_settings();
    settings.register_global_callback([this](string key, string val) {
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

    return false;
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

        int sp = cmd.find('=');
        // Single command?
        if (sp == -1) {
            printf("cmd: '%s'\n", trim(cmd).c_str());
        }
        // Assignment
        else {
            string key = trim(cmd.substr(0, sp));
            string val = trim(cmd.substr(sp + 1));
            printf("key: '%s' val: '%s'\n", key.c_str(), val.c_str());
        }
    }
}

