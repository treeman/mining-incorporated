#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;

#include "butler.hxx"
#include "help.hxx"
#include "currentstate.hxx"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Mining Inc.", sf::Style::None);

    push_next_state("game", window);
    push_next_state("help", window);

    sf::Clock clock;
    while (window.isOpen() && has_state())
    {
        shared_ptr<State> state = current_state();
        sf::Event e;
        while (window.pollEvent(e))
        {
            bool drop = true;
            switch (e.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (e.key.code == sf::Keyboard::H) {
                        drop = false;
                        if (state->id() != "help")
                            push_next_state("help", window);
                    }
                    break;
                default: break;
            }

            if (drop)
                state->handle_input(e);
        }

        sf::Time dt = clock.restart();
        state->update(dt);

        window.clear();
        state->draw();
        window.display();
    }

    return 0;
}

