

#include "UI/cli.hpp"

#include <iostream>
#include <sstream>
#include <string>

#include "utils.hpp"


CLI::CLI(Game* game) : UserInterface(game) {
    game->cheat();
}

CLI::~CLI() {
    std::cout << "Deleting CLI" << std::endl;
}

bool CLI::run() {
    std::cout << "Running" << std::endl;

    return play_again();
}


bool CLI::play_again() const {
    return false;
}
