
#include "user_interface.hpp"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <ncurses.h>
#include <sstream>
#include <string>

#include "utils.hpp"


static void to_lower(std::string &s) {
    std::transform(s.begin(), s.end(), s.begin(), [](char c) { return std::tolower(c); });
}


UserInterface::UserInterface(Game* game) : game(game) {
    initscr();
    draw_frame();
}

UserInterface::~UserInterface() {
    std::cout << "Leaving" << std::endl;
    endwin();
}

bool UserInterface::run() {
    draw_game_state();
    /* game->draw(); */
    /* do */
    /*     game->draw(); */
    /* while (act()); */

    getch();
    return play_again();
}


bool UserInterface::play_again() const {
    std::cout << "Game over ! One day, you will be able to play again here" << std::endl;
    return false;
}

bool UserInterface::act() {
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

void UserInterface::draw_frame() const {
    std::string hborder(COLS-2, '-');
    hborder = "+" + hborder + "+";
    mvprintw(0, 0, hborder.c_str());
    mvprintw(LINES-1, 0, hborder.c_str());
    for (int j=1; j<LINES-1; j++) {
        mvaddch(j, 0, '|');
        mvaddch(j, COLS-1, '|');
    }
}

void UserInterface::draw_game_state() const {
    int padding = (COLS-1 - 4*9) / 4;
    int inner_padding = (COLS-1 - 4*9) / 6;

    mvprintw(3, padding, "Money : % 2d", game->money);
    mvprintw(3, padding+9+inner_padding, " Life: % 2d", game->life);
    mvprintw(3, padding+2*(9+inner_padding), " Wins: % 2d/10", game->victories);
    mvprintw(3, padding+3*(9+inner_padding), " Turn % 2d", game->victories);
}

void UserInterface::draw_team() const {

}

void UserInterface::draw_shop() const {

}

void UserInterface::draw_action() const {

}
