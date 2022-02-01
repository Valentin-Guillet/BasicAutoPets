
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
        if (action == "buy_animal") {
            std::string arg;
            std::cin >> arg;
            int index = std::stoi(arg);

            game->buy_animal(index);

        } else if (action == "upgrade") {
            std::string arg;
            std::cin >> arg;
            int index_shop = std::stoi(arg);
            std::cin >> arg;
            int index_team = std::stoi(arg);

            game->upgrade(index_shop, index_team);

        } else if (action == "sell") {
            std::string arg;
            std::cin >> arg;
            int index = std::stoi(arg);

            game->sell(index);

        } else if (action == "buy_object") {

        } else if (action == "roll") {

        } else if (action == "freeze") {

        } else if (action == "end_turn") {

        } else if (action == "quit") {
            return false;
        }
    } catch (...) {
        std::cout << "Error !" << std::endl;
    }

    return true;
}
