#include "help.hxx"
#include "currentstate.hxx"
#include "constants.hxx"
#include "roomtype.hxx"
#include "settings.hxx"
#include "console.hxx"
#include "rand.hxx"
#include "inputqueue.hxx"
#include "locator.hxx"
#include "consolelogger.hxx"
#include "visualdebug.hxx"
#include "ground.hxx"
#include "ore.hxx"

#include <cstdlib>
#include <ctime>

int main()
{
    // Init global functions.
    Locator::init();

    // Log to console atm
    Locator::provide_logger(unique_ptr<Logger>(new ConsoleLogger()));

    load_ground_definitions("ground.lua");
    load_ore_definitions("ore.lua");

    // Register some defaults.
    Settings &settings = Locator::get_settings();
    settings.register_num("screen_width", 800);
    settings.register_num("screen_height", 600);
    settings.register_bool("show_fps", false);
    settings.register_bool("show_mouse_pos", false);

    settings.load_from_file("settings.lua");
    // TODO make something more general?
    // Should all be settings?
    settings.load_from_file("gui.lua");

    sf::RenderWindow window(
        sf::VideoMode(
            // TODO cannot handle different settings here, will bork aspect ratio of tiles.
            (int)settings.get_num("screen_width"),
            (int)settings.get_num("screen_height")
        ),
        "Mining Inc.",
        sf::Style::None
    );

    Locator::provide_window(&window);
    Locator::provide_debug(unique_ptr<VisualDebug>(new VisualDebug()));

    // TODO remove/move!
    // Yes it's happning here!
    init_rooms();
    set_seed(time(0));

    // We want a console for everything! =)
    Console console(window);

    push_next_state("game", window);

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

        if (settings.get_bool("show_mouse_pos")) {
            auto mp = sf::Mouse::getPosition(window);
            D_.tmp("mpos: " + to_string(mp.x) + ", " + to_string(mp.y));
        }

        // Debugger logs and possibly draws last.
        Locator::get_debug().update();

        // Well console is last, heh!
        console.draw();

        window.display();
    }

    return 0;
}

