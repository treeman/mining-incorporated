#include "state/help.hxx"
#include "state/game.hxx"
#include "constants.hxx"
#include "roomtype.hxx"
#include "settings.hxx"
#include "console.hxx"
#include "util/rand.hxx"
#include "input/inputqueue.hxx"
#include "locator.hxx"
#include "stdoutlogger.hxx"
#include "visualdebug.hxx"
#include "scene/ore.hxx"
#include "scene/ground.hxx"
#include "abort.hxx"

#include <cstdlib>
#include <ctime>

int main()
{
    // Log to console atm
    Locator::provide_logger(unique_ptr<Logger>(new StdoutLogger()));

    // Register some defaults.
    Locator::provide_settings(unique_ptr<Settings>(new Settings()));

    Settings &settings = Locator::get_settings();
    settings.register_num("screen_width", 800);
    settings.register_num("screen_height", 600);
    settings.register_bool("show_fps", false);
    settings.register_bool("show_mouse_pos", false);

    settings.load_from_file("settings.lua");
    // TODO make something more general?
    // Should all be settings?
    settings.load_from_file("gui.lua");

    // TODO move
    scene::load_ground_definitions("ground.lua");
    scene::load_ore_definitions("ore.lua");

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

    // Setup possible reachable states.
    typedef state::StateStack<state::State> StateHandler;
    unique_ptr<StateHandler> states(new StateHandler());
    states->add_generator("help", [&window](){ return new state::HelpState(window); });
    states->add_generator("game", [&window](){ return new state::GameState(window); });
    Locator::provide_statestack(move(states));

    InputQueue input_queue;
    input_queue.add_handler(&console);

    // Start at "game" state.
    StateHandler &state_handler = Locator::get_statestack();
    state_handler.push_generated("game");

    sf::Clock clock;
    while (window.isOpen() && state_handler.has_current())
    {
        shared_ptr<state::State> state = state_handler.current();
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
                    if (e.key.code == sf::Keyboard::Q) {
                        L_("exiting...\n");
                        window.close();
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

        // Debug mouse position here
        if (settings.get_bool("show_mouse_pos")) {
            auto mp = sf::Mouse::getPosition(window);
            D_.set_key("mpos", to_string(mp.x) + ", " + to_string(mp.y));
        }

        // Draw things!
        window.clear();

        state->draw();

        // Debugger logs and possibly draws last.
        Locator::get_debug().update();

        // Well console is last, heh!
        console.draw();

        window.display();
    }

    return 0;
}

