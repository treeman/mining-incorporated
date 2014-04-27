#include "util.hxx"
#include "butler.hxx"
#include "help.hxx"
#include "currentstate.hxx"
#include "constants.hxx"
#include "roomtype.hxx"

#include <cstdlib>
#include <ctime>

int main()
{
    sf::RenderWindow window(sf::VideoMode(screen_width, screen_height), "Mining Inc.", sf::Style::None);

    // Yes it's happning here!
    init_rooms();
    //srand(time(NULL));
    //init_rand(time(NULL));
    set_seed(time(NULL));

    push_next_state("game", window);
    //push_next_state("help", window);

    sf::Text mpos = create_txt("arial.ttf", 14, "0, 0");
    mpos.setPosition(8, 5);

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
                        //drop = false;
                        //if (state->id() != "help")
                            //push_next_state("help", window);
                    }
                    break;
                default: break;
            }

            if (drop)
                state->handle_input(e);
        }

        sf::Time dt = clock.restart();
        state->update(dt);

        // Draw things!
        window.clear();

        state->draw();

        /*
        auto mp = sf::Mouse::getPosition(window);
        stringstream ss; ss << mp.x << ", " << mp.y;
        mpos.setString(ss.str());
        window.draw(mpos);
        */

        window.display();
    }

    return 0;
}

