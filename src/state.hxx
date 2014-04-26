#pragma once

#include <SFML/Graphics.hpp>
#include <string>
using namespace std;

class State {
public:
    State(sf::RenderWindow &w) : window(w) { }

    virtual string id() const = 0;

    virtual void handle_input(const sf::Event &e) { }
    virtual void update(const sf::Time &dt) { }
    virtual void draw() { }
protected:
    sf::RenderWindow &window;
};

