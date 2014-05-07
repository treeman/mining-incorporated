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

Logger &Locator::get_logger() {
    assert(logger != nullptr);
    return *logger;
}
void Locator::provide_logger(unique_ptr<Logger> next) {
    logger.swap(next);
}

unique_ptr<Settings> Locator::settings{ nullptr };
unique_ptr<Logger> Locator::logger{ nullptr };

