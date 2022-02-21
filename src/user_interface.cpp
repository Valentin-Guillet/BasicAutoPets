
#include "user_interface.hpp"

#include <locale.h>
#include <ncurses.h>

#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>
#include <unordered_map>

#include "utils.hpp"


const std::unordered_map<UIState, std::string> MSGS = {
    {UIState::none, "What do you want to do ?     (B)uy     (S)ell     (F)reeze     (C)ombine team     Co(m)bine shop     (R)oll     (O)rder     (E)nd turn     (Q)uit"},
    {UIState::buy, "Buying !"},
    {UIState::sell, "Selling !"},
    {UIState::freeze, "Freezing !"},
    {UIState::combine_team, "Combining team !"},
    {UIState::combine_shop, "Combining shop !"},
    {UIState::order, "Ordering !"},
};


UserInterface::UserInterface(Game* game) : game(game), state(UIState::none) {
    setlocale(LC_ALL, "");
    initscr();
    curs_set(0);
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
}

UserInterface::~UserInterface() {
    endwin();
    std::cout << "Leaving" << std::endl;
}

bool UserInterface::run() {
    do {
        clear();
        draw_frame();
        draw_game_state();
        draw_team();
        draw_shop();
        draw_action();
        draw_status();
    } while (act());

    return play_again();
}


bool UserInterface::play_again() const {
    return false;
}

bool UserInterface::act() {
    try {
        switch (state) {
            case UIState::none:
                return take_action();
            case UIState::buy:
                buy();
                break;
            case UIState::sell:
                sell();
                break;
            case UIState::freeze:
                freeze();
                break;
            case UIState::combine_team:
                combine_team();
                break;
            case UIState::combine_shop:
                combine_shop();
                break;
            case UIState::order:
                order();
                break;
        }
    } catch (InvalidAction& e) {
        status = e.what_str();
    }
    return true;
}

bool UserInterface::take_action() {
    int c = std::tolower(getch());
    status = "";

    switch (c) {
        case KEY_RESIZE:
            clear();
            draw_frame();
            draw_game_state();
            draw_team();
            draw_shop();
            draw_action();
            draw_status();
            break;

        case 'b':
            state = UIState::buy;
            break;

        case 's':
            state = UIState::sell;
            break;

        case 'f':
            state = UIState::freeze;
            break;

        case 'c':
            state = UIState::combine_team;
            break;

        case 'm':
            state = UIState::combine_shop;
            break;

        case 'r':
            status = "Rolling...";
            game->roll();
            break;

        case 'o':
            state = UIState::order;
            break;

        case 'e': {
            size_t indices[5] = {1, 2, 3, 4, 5};
            game->end_turn(indices);
            break;
        }

        case 'q':
            return false;
    }

    return true;
}

void UserInterface::buy() {
    state = UIState::none;
    int c = std::tolower(getch());

    // Buy pet
    if ('1' <= c && c <= '7') {
        game->buy_pet(c - '1');

    // Buy object
    } else if (c == '9' || c == '0') {
        int nc = (c == '9' ? 0 : 1);
        Object* obj = game->shop->objects[nc];
        if (!obj) {
            status = "[BUY_OBJECT]: No object in shop at index " + std::to_string(nc);
            return;
        }
        if (obj->target_all) {
            game->buy_object(nc, 0);
            status = "[BUY_OBJECT]: Bought object " + std::to_string(nc+1);
        } else {
            int target = std::tolower(getch());
            if ('1' <= target && target <= '5') {
                game->buy_object(nc, target - '1');
                status = "[BUY_OBJECT]: Given object " + std::to_string(nc+1) + " to " + std::to_string(target-'0');
            } else {
                status = "[BUY_OBJECT]: Invalid target for object 0";
            }
            return;
        }
    }
}

void UserInterface::sell() {
    state = UIState::none;
    int c = std::tolower(getch());

    if (!('1' <= c && c <= '5'))
        return;

    game->sell(c - '1');
    status = "[SELL]: Sold " + std::to_string(c - '0');
}

void UserInterface::freeze() {
    state = UIState::none;
    int c = std::tolower(getch());

    if ('1' <= c && c <= '5') {
        game->freeze_pet(c - '1');
        status = "[FREEZE]: Frozen pet " + std::to_string(c - '0');
    } else if (c == '9' || c == '0') {
        game->freeze_object((c == '9' ? 0 : 1));
        status = "[FREEZE]: Frozen object " + std::to_string(c == '9' ? 1 : 2);
    }
}

void UserInterface::combine_team() {
    state = UIState::none;
    int c1 = std::tolower(getch());
    int c2 = std::tolower(getch());

    if (!('1' <= c1 && c1 <= '5' && '1' <= c2 && c2 <= '5')) {
        status = "[COMBINE_TEAM]: Invalid pet indices";
        return;
    }
    game->combine_team(c1 - '1', c2 - '1');
    status = "[COMBINE_TEAM]: Combined pets " + std::to_string(c1 - '0') + " and " + std::to_string(c2 - '0');
}

void UserInterface::combine_shop() {
    state = UIState::none;
    int c1 = std::tolower(getch());
    int c2 = std::tolower(getch());

    if (!('1' <= c1 && c1 <= '5' && '1' <= c2 && c2 <= '5')) {
        status = "[COMBINE TEAM]: Invalid pet indices";
        return;
    }
    game->combine_shop(c1 - '1', c2 - '1');
    status = "[COMBINE_SHOP]: Upgraded pet " + std::to_string(c2 - '0');
}

void UserInterface::order() {
    state = UIState::none;
    int c1 = std::tolower(getch());
    int c2 = std::tolower(getch());

    if (!('1' <= c1 && c1 <= '5' && '1' <= c2 && c2 <= '5')) {
        status = "[ORDER]: Invalid order index";
        return;
    }

    size_t indices[5] = {0, 1, 2, 3, 4};
    indices[c1 - '1'] = c2 - '1';
    indices[c2 - '1'] = c1 - '1';

    game->team->order(indices);
    status = "[ORDER]: Switching " + std::to_string(c1 - '1') + " and " + std::to_string(c2 - '1');
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
        else
            mvprintw(15, padding, "  ___  ");
        padding += 9 + inner_padding;
    }
    padding += (9 + inner_padding) * (5 - game->shop->pets.size());

    for (size_t i=0; i<game->shop->objects.size(); i++) {
        if (game->shop->objects[i])
            draw_object(game->shop->objects[i], padding, 14, game->shop->frozen_objects[i]);
        else
            mvprintw(15, padding, "  ___  ");
        padding += 9 + inner_padding;
    }
}

void UserInterface::draw_action() const {
    std::string empty_msg(COLS-3, ' ');
    mvprintw(20, 1, empty_msg.c_str());
    mvprintw(20, 1, MSGS.at(state).c_str());
}

void UserInterface::draw_status() const {
    std::string empty_msg(COLS-3, ' ');
    mvprintw(21, 1, empty_msg.c_str());
    mvprintw(21, 1, status.c_str());
}
