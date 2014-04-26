#include <set>
#include <sstream>
using namespace std;

#include "util.hxx"
#include "game.hxx"
#include "butler.hxx"
#include "currentstate.hxx"

GameState::GameState(sf::RenderWindow &w) : State(w), world(w), gui(&world, w) {
    txt = create_txt("consola.ttf", 14);

    set<string> vals = { "coal", "iron", "copper", "gold", "silver", "diamond", "aluminium" };
    for (string x : vals)
        collected[x] = 0;

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

    // Draw list of levels
    txt.setColor(sf::Color::White);
    txt.setPosition(20, 25);
    txt.setString("Level 1");
    window.draw(txt);

    // Draw current state
    int xoff = 690;
    int yoff = 10;
    txt.setColor(sf::Color::White);
    txt.setPosition(xoff, yoff);
    txt.setString("Money: ");
    int off = txt.getGlobalBounds().width;
    window.draw(txt);

    txt.setColor(make_color(0x2F9C3F));
    txt.setPosition(xoff + off, yoff);
    txt.setString("$20");
    window.draw(txt);

    // TODO custom colors for collected things later
    // TODO move stats to world. Can share state...
    int h = 16, curry = yoff + h + 5;
    for (auto x : collected) {
        txt.setColor(sf::Color::White);
        txt.setPosition(xoff, curry);
        stringstream ss;
        ss << x.first << " " << x.second;
        txt.setString(ss.str());
        window.draw(txt);

        curry += h;
    }
}

