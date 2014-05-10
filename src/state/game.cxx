#include "game.hxx"
#include "butler.hxx"
#include "currentstate.hxx"

GameState::GameState(sf::RenderWindow &w) : State(w), world(w), gui(&world, w) {
    txt = create_txt("consola.ttf", 14);

    /*
    set<string> vals = { "coal", "iron", "copper", "gold", "silver", "diamond", "aluminium" };
    for (string x : vals)
        collected[x] = 0;
    */

    //gui.push_back(Button([&]() mutable { printf("click!\n"); }, 20, 570, "Rooms"));
}

void GameState::handle_input(const sf::Event &e) {
    gui.handle_input(e);
    world.handle_input(e);
}
void GameState::update(const sf::Time &dt) {
    world.update(dt);
}
void GameState::draw() {
    world.draw();

    gui.draw(window);

    // TODO move?


/*
    // Draw list of levels
    txt.setColor(sf::Color::White);
    txt.setPosition(20, 25);
    txt.setString("Level 1");
    window.draw(txt);
*/
}

