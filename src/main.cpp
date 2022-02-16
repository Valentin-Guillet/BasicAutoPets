
#include <iostream>

#include "game.hpp"
#include "user_interface.hpp"
#include "utils.hpp"


int main(int argc, char** argv) {
    spdlog::set_level(spdlog::level::debug);

    Game* game = new Game();

    UserInterface ui(game);

    while (ui.run()) {
        delete game;
        game = new Game();
    }

    delete game;

    std::cout << "End of game !" << std::endl;

    return 0;
}
