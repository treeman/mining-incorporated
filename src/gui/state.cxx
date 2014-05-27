#include "locator.hxx"
#include "util/ext.hxx"
#include "gui/state.hxx"
#include "gui/interface.hxx"
#include "scene/world.hxx"
#include "scene/ore.hxx"
#include "scene/event.hxx"

namespace gui {

State::State(Interface *_gui, scene::World *_world) : gui(_gui), world(_world) {

}

string type2string(GuiState type) {
    switch (type) {
        case GuiState::INFO: return "Info";
        case GuiState::MATERIAL: return "Material";
        case GuiState::PLANNING: return "Planning";
        case GuiState::MINE: return "Mine";
        case GuiState::NUM_STATES: return "Invalid GuiState";
        default: return "Unknown GuiState";
    }
}


} // Gui

