
#include "user_interface.hpp"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>
#include <string>

#include "utils.hpp"


static void to_lower(std::string &s) {
    std::transform(s.begin(), s.end(), s.begin(), [](char c) { return std::tolower(c); });
}


bool act(Game* game) {
    std::string line;
    std::cout << "What do you want to do ?\n";
    std::getline(std::cin, line);
    std::istringstream iss(line);

    std::string action;
    iss >> action;
    to_lower(action);

    std::cout << "Action: " << line << std::endl;
    try {
        if (action == "buy_pet") {
            std::string arg;
            iss >> arg;
            int index = std::stoi(arg) - 1;

            game->buy_pet(index);

        } else if (action == "combine_shop") {
            std::string arg;
            iss >> arg;
            int index_shop = std::stoi(arg) - 1;
            iss >> arg;
            int index_team = std::stoi(arg) - 1;

            game->combine_shop(index_shop, index_team);

        } else if (action == "combine_team") {
            std::string arg;
            iss >> arg;
            int src_index = std::stoi(arg) - 1;
            iss >> arg;
            int dst_index = std::stoi(arg) - 1;

            game->combine_team(src_index, dst_index);

        } else if (action == "sell") {
            std::string arg;
            iss >> arg;
            int index = std::stoi(arg) - 1;

            game->sell(index);

        } else if (action == "buy_object") {
            std::string arg;
            iss >> arg;
            int index = std::stoi(arg) - 1;
            iss >> arg;
            int index_target = std::stoi(arg) - 1;

            game->buy_object(index, index_target);

        } else if (action == "roll") {
            game->roll();

        } else if (action == "freeze_pet") {
            std::string arg;
            iss >> arg;
            int index = std::stoi(arg) - 1;
            game->freeze_pet(index);

        } else if (action == "freeze_object") {
            std::string arg;
            iss >> arg;
            int index = std::stoi(arg) - 1;
            game->freeze_object(index);

        } else if (action == "end_turn") {
            size_t indices[5];
            for (size_t i=0; i<5; i++) {
                std::string arg;
                iss >> arg;
                indices[i] = std::stoi(arg) - 1;
            }
            return game->end_turn(indices);

        } else if (action == "cheat") {
            game->cheat();

        } else if (action == "quit") {
            return false;
        } else {
            spdlog::warn("Action {} not recognized", action);
        }

    } catch (InvalidAction& e) {
        spdlog::warn(e.what());

    } catch (std::exception& e) {
        std::cerr << "Error in action " << action << " !" << std::endl;
        std::cerr << "Err: " << e.what() << std::endl;
    }

    return true;
}
