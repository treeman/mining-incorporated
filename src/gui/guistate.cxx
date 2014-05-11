#include "guistate.hxx"
#include "gui.hxx"

GuiState::GuiState() : gui(nullptr), world(nullptr) {

}

void GuiState::init(Gui *_gui, World *_world) {
    gui = _gui;
    world = _world;
}

