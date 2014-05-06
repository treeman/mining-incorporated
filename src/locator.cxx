#include <cassert>
#include "locator.hxx"

void Locator::init() {
    unique_ptr<Settings>(new Settings()).swap(settings);
}
//static Butler &Locator::get_butler() {
    //assert(static_cast<bool>(butler));
    //return *butler;
//}
Settings &Locator::get_settings() {
    assert(settings != nullptr);
    return *settings;
}

unique_ptr<Settings> Locator::settings{ nullptr };

