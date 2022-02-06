
#include <iostream>

#include "game.hpp"
#include "user_interface.hpp"


int main(int argc, char** argv) {

    Game* game = new Game();
    game->draw();

    while (act(game))
        game->draw();

    delete game;

    std::cout << "End of game !" << std::endl;

    return 0;
}
