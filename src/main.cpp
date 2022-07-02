
#include <iostream>

#include "game.hpp"
#include "UI/user_interface.hpp"
#include "utils.hpp"


int main(int argc, char** argv) {
    Game* game = new Game();
    bool use_cli = false;
    for (int i=1; i<argc; i++) {
        std::string arg(argv[i]);
        if (arg == "-c" || arg == "--cli")
            use_cli = true;
    }

    UserInterface* ui = UserInterface::create_ui(game, use_cli);
    while (ui->run())
        game->reset();

    delete game;
    delete ui;

    std::cout << "End of game !" << std::endl;

    return 0;
}
