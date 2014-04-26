#include <SFML/Graphics.hpp>

#include "state.hxx"

class HelpState : public State {
public:
    HelpState(sf::RenderWindow &w);

    string id() const { return "help"; }

    void handle_input(const sf::Event &e);
    void update(const sf::Time &dt);
    void draw();
private:
    sf::Text txt;
};

