#include "butler.hxx"
#include "help.hxx"
#include "currentstate.hxx"
#include "constants.hxx"
#include "roomtype.hxx"
#include "settings.hxx"
#include "console.hxx"
#include "rand.hxx"
#include "inputqueue.hxx"
#include "locator.hxx"

#include <cstdlib>
#include <ctime>

int main()
{
    // Init global functions.
    Locator::init();

    // Register some defaults.
    Settings &settings = Locator::get_settings();
    settings.register_num_setting("screen_width", 800);
    settings.register_num_setting("screen_height", 600);
    settings.register_bool_setting("show_fps", false);
    settings.register_bool_setting("show_mouse_pos", false);

    settings.load_from_file("settings.lua");

    sf::RenderWindow window(
        sf::VideoMode(
            // TODO cannot handle different settings here, will bork aspect ratio of tiles.
            (int)settings.get_num_setting("screen_width"),
            (int)settings.get_num_setting("screen_height")
        ),
        "Mining Inc.",
        sf::Style::None
    );

    // TODO remove/move!
    // Yes it's happning here!
    init_rooms();
    set_seed(time(NULL));

    // We want a console for everything! =)
    Console console(window);

    push_next_state("game", window);

    sf::Text mpos = create_txt("arial.ttf", 14, "0, 0");
    mpos.setPosition(8, 5);
    //console.activate();

    InputQueue input_queue;
    input_queue.add_handler(&console);

    sf::Clock clock;
    while (window.isOpen() && has_state())
    {
        shared_ptr<State> state = current_state();
        sf::Event e;
        while (window.pollEvent(e))
        {
            //bool drop = true;
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

            if (input_queue.handle_input(e))
                state->handle_input(e);
        }

        sf::Time dt = clock.restart();
        state->update(dt);
        console.update(dt);

        // Draw things!
        window.clear();

        state->draw();
        console.draw();

        if (settings.get_bool_setting("show_mouse_pos")) {
            auto mp = sf::Mouse::getPosition(window);
            stringstream ss; ss << mp.x << ", " << mp.y;
            mpos.setString(ss.str());
            window.draw(mpos);
        }

        window.display();
    }

    return 0;
}

