
#include <iostream>

#include "game.hpp"
#include "UI/cli.hpp"
#include "UI/gui.hpp"
#include "utils.hpp"


int main(int argc, char** argv) {
    Game* game = new Game();
    UserInterface* ui;

    bool use_cli = false;
    for (int i=1; i<argc; i++) {
        std::string arg(argv[i]);
        if (arg == "-c" || arg == "--cli")
            use_cli = true;
    }

    if (use_cli)
        ui = new CLI(game);
    else
        ui = new GUI(game);

    while (ui->run()) {
        game->reset();
    }

    delete game;
    delete ui;

    std::cout << "End of game !" << std::endl;

    return 0;
}
