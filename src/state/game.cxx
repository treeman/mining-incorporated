#include "butler.hxx"
#include "state/game.hxx"

namespace state {

GameState::GameState(sf::RenderWindow &w) : State(w), world(w), gui(&world, w) {
    txt = create_txt("consola.ttf", 14);
}

void GameState::handle_input(const sf::Event &e) {
    gui.handle_input(e);
    world.handle_input(e);
}
void GameState::update(const sf::Time &dt) {
    gui.update(dt);
    world.update(dt);
}
void GameState::draw() {
    world.draw();
    gui.draw(window);
}

}

