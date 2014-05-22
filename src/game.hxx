#include <memory>
using namespace std;

#include "console.hxx"
#include "input/inputqueue.hxx"

#include <SFML/Graphics.hpp>

class Game {
public:
    Game();
    ~Game() noexcept;

    void run();
private:
    unique_ptr<sf::RenderWindow> window;

    unique_ptr<Console> console;
    InputQueue input_queue;

    sf::Text fps_txt;
    int fps_frame_count;
    float fps;
    sf::Clock fps_timer;
};

