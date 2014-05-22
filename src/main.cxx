#include "game.hxx"
#include <cstdlib>
#include <ctime>

int main()
{
    shared_ptr<Game> game(new Game());
    game->run();
    return 0;
}

