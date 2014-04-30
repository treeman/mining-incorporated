#include "butler.hxx"
#include "help.hxx"
#include "currentstate.hxx"
#include "constants.hxx"
#include "roomtype.hxx"
#include "settings.hxx"
#include "console.hxx"
#include "rand.hxx"

#include <cstdlib>
#include <ctime>

int main()
{
    Settings settings;
    settings.load_from_file("settings.lua");

    settings.register_num_callback("x", [](int val) { printf("new val: %d\n", val); });
    settings.set_num_setting("x", 12);

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
    Console console(window, settings);
    settings.set_num_setting("x", 13);
    settings.set_num_setting("x", 14);
    settings.set_bool_setting("show_mouse_pos", false);
    settings.set_string_setting("y", "meow");

    push_next_state("game", window);

    sf::Text mpos = create_txt("arial.ttf", 14, "0, 0");
    mpos.setPosition(8, 5);
    console.activate();

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

            drop = console.handle_input(e);
            if (drop)
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

