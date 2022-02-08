
#include "user_interface.hpp"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>
#include <string>


static void to_lower(std::string &s) {
    std::transform(s.begin(), s.end(), s.begin(), [](char c) { return std::tolower(c); });
}


bool act(Game* game) {
    std::string action;

    std::cout << "What do you want to do ?\n";
    std::cin >> action;
    to_lower(action);

    std::cout << "Action: " << action << std::endl;
    try {
        if (action == "buy_pet") {
            std::string arg;
            std::cin >> arg;
            int index = std::stoi(arg) - 1;

            game->buy_pet(index);

        } else if (action == "upgrade") {
            std::string arg;
            std::cin >> arg;
            int index_shop = std::stoi(arg) - 1;
            std::cin >> arg;
            int index_team = std::stoi(arg) - 1;

            game->upgrade(index_shop, index_team);

        } else if (action == "sell") {
            std::string arg;
            std::cin >> arg;
            int index = std::stoi(arg) - 1;

            game->sell(index);

        } else if (action == "buy_object") {
            std::string arg;
            std::cin >> arg;
            int index = std::stoi(arg) - 1;
            std::cin >> arg;
            int index_target = std::stoi(arg) - 1;

            game->buy_object(index, index_target);

        } else if (action == "roll") {
            game->roll();

        } else if (action == "freeze") {

        } else if (action == "end_turn") {
            int indices[5];
            for (size_t i=0; i<5; i++) {
                std::string arg;
                std::cin >> arg;
                indices[i] = std::stoi(arg) - 1;
            }
            return game->end_turn(indices);

        } else if (action == "quit") {
            return false;
        }
    } catch (...) {
        std::cerr << "Error in action " << action << " !" << std::endl;
    }

    return true;
}
