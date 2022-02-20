
#include "user_interface.hpp"

#include <locale.h>

#include <algorithm>
#include <cctype>
#include <iostream>
#include <ncurses.h>
#include <sstream>
#include <string>

#include "utils.hpp"


/* static void to_lower(std::string &s) { */
/*     std::transform(s.begin(), s.end(), s.begin(), [](char c) { return std::tolower(c); }); */
/* } */


UserInterface::UserInterface(Game* game) : game(game) {
    setlocale(LC_ALL, "");
    initscr();
    curs_set(0);
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    draw_frame();
}

UserInterface::~UserInterface() {
    std::cout << "Leaving" << std::endl;
    endwin();
}

bool UserInterface::run() {
    do {
        draw_game_state();
        draw_team();
        draw_shop();
    } while (act());

    return play_again();
}


bool UserInterface::play_again() const {
    std::cout << "Game over ! One day, you will be able to play again here" << std::endl;
    return false;
}

bool UserInterface::act() {
    std::string actions = "What do you want to do ?   ";
    actions += "(B)uy     (S)ell     (F)reeze     (C)ombine";
    actions += "     (R)oll     (O)rder     (E)nd turn     (Q)uit";
    mvprintw(20, 5, actions.c_str());
    int c = std::tolower(getch());

    return c != 'q';

    /*
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
    */

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
    mvprintw(3, padding+3*(9+inner_padding), " Turn % 2d", game->turn);
}

void UserInterface::draw_pet(Pet* pet, int x, int y, bool draw_xp, bool frozen) const {
    if (pet->object)
        mvaddstr(y, x+2, pet->object->repr.c_str());
    mvaddstr(y+1, x+3, pet->repr.c_str());
    mvprintw(y+2, x, " %02d / %02d", pet->attack, pet->life);
    int lvl = pet->get_level();
    if (draw_xp) {
        int xp = pet->get_xp();
        if (lvl == 1)
            mvprintw(y+3, x, "Lvl 1 %d / 2", xp);
        else if (lvl == 2)
            mvprintw(y+3, x, "Lvl 2 %d / 3", xp - 2);
        else
            mvprintw(y+3, x, "Lvl 3 0 / 0");
    }
    if (frozen)
        mvaddstr(y+4, x+4, "🧊");
}

void UserInterface::draw_object(Object* obj, int x, int y, bool frozen) const {
    mvaddstr(y, x+3, obj->repr.c_str());
    mvprintw(y+1, x, "Cost: %d", obj->cost);
    if (frozen)
        mvaddstr(y+2, x+3, "🧊");
}

void UserInterface::draw_team() const {
    int padding = (COLS-1 - 4*9) / 3.5;
    int inner_padding = (COLS-1 - 4*9) / 10;

    for (Pet* pet : game->team->pets) {
        draw_pet(pet, padding, 7, true);
        padding += 9 + inner_padding;
    }
    for (size_t i=game->team->pets.size(); i<5; i++) {
        mvprintw(8, padding, "  Empty  ");
        padding += 9 + inner_padding;
    }
}

void UserInterface::draw_shop() const {
    int padding = (COLS-1 - 4*9) / 6;
    int inner_padding = (COLS-1 - 4*9) / 9;

    for (size_t i=0; i<game->shop->pets.size(); i++) {
        if (game->shop->pets[i])
            draw_pet(game->shop->pets[i], padding, 13, false, game->shop->frozen_pets[i]);
        padding += 9 + inner_padding;
    }
    padding += (9 + inner_padding) * (5 - game->shop->pets.size());

    for (size_t i=0; i<game->shop->objects.size(); i++) {
        if (game->shop->objects[i])
            draw_object(game->shop->objects[i], padding, 14, game->shop->frozen_objects[i]);
        padding += 9 + inner_padding;
    }
}

void UserInterface::draw_action() const {

}
