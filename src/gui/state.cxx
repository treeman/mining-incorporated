#include "gui/state.hxx"
#include "gui/interface.hxx"
#include "world/world.hxx"

namespace Gui {

State::State() : gui(nullptr), world(nullptr) {

}

void State::init(Interface *_gui, World *_world) {
    gui = _gui;
    world = _world;
}

}

