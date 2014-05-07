#include "locator.hxx"
#include "debug.hxx"

Debug::Debug() {
    Settings &settings = Locator::get_settings();
    settings.register_bool("enable_debug", false);
}

void Debug::tmp(string val) {
    tmps.push_back(val);
}

void Debug::set_key(string key, string val) {
    persistent[key] = val;
}
void Debug::del_key(string key) {
    persistent.erase(key);
}

void Debug::update() {
    if (Locator::get_settings().get_bool("enable_debug"))
        log();
    clear_tmp();
}

void Debug::clear_tmp() {
    tmps.clear();
}

