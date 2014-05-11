#include <cassert>
#include "locator.hxx"

//void Locator::init() {
    //unique_ptr<Settings>(new Settings()).swap(settings);
//}
//static Butler &Locator::get_butler() {
    //assert(static_cast<bool>(butler));
    //return *butler;
//}
Settings &Locator::get_settings() {
    assert(settings != nullptr);
    return *settings;
}
void Locator::provide_settings(unique_ptr<Settings> s) {
    settings.swap(s);
}

Logger &Locator::get_logger() {
    assert(logger != nullptr);
    return *logger;
}
void Locator::provide_logger(unique_ptr<Logger> next) {
    logger.swap(next);
}

Debug &Locator::get_debug() {
    assert(debug != nullptr);
    return *debug;
}
void Locator::provide_debug(unique_ptr<Debug> d) {
    debug.swap(d);
}

bool Locator::has_window() {
    return window != nullptr;
}
sf::RenderWindow &Locator::get_window() {
    assert(window != nullptr);
    return *window;
}
void Locator::provide_window(sf::RenderWindow *w) {
    window = w;
}

state::StateStack<state::State> &Locator::get_statestack() {
    assert(statestack != nullptr);
    return *statestack;
}
void Locator::provide_statestack(unique_ptr<state::StateStack<state::State>> s) {
    statestack.swap(s);
}

unique_ptr<Settings> Locator::settings{ nullptr };
unique_ptr<Logger> Locator::logger{ nullptr };
unique_ptr<Debug> Locator::debug{ nullptr };
sf::RenderWindow *Locator::window{ nullptr };
unique_ptr<state::StateStack<state::State>> Locator::statestack{ nullptr };

