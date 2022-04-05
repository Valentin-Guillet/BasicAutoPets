
#include "user_interface.hpp"

#include <locale.h>
#include <ncurses.h>

#include <algorithm>
#include <cctype>
#include <chrono>
#include <iostream>
#include <sstream>
#include <thread>
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
    {UIState::fighting, "Fight !     (A)uto-play     (P)lay     (S)kip"},
};


UserInterface::UserInterface(Game* game) : game(game), state(UIState::none) {
    setlocale(LC_ALL, "");
    initscr();
    curs_set(0);
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    game->cheat();
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
    bool continue_game = true;
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
            case UIState::fighting:
                continue_game = fight();
                break;
        }
    } catch (InvalidAction& e) {
        status = e.what_str();
    }
    return continue_game;
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

        case 'e':
            state = UIState::fighting;
            game->team->end_turn();
            break;

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

        std::string obj_name = obj->name;
        if (obj->target_all) {
            game->buy_object(nc, 0);
            status = "[BUY_OBJECT]: Bought " + obj_name;
        } else {
            status = "[BUY_OBJECT]: Buying " + obj_name + " for pet ...";
            draw_status();

            int target = std::tolower(getch());
            if (!('1' <= target && target <= '5')) {
                status = "[BUY_OBJECT]: Invalid target for " + obj_name;
                return;
            }

            std::string target_name;
            if ((target - '1') < (int)game->team->pets.size())
                target_name = game->team->pets[target - '1']->name;

            game->buy_object(nc, target - '1');
            if (!target_name.empty())
                status = "[BUY_OBJECT]: Giving " + obj_name + " to " + target_name;
        }
    }
}

void UserInterface::sell() {
    state = UIState::none;
    status = "[SELL]: Selling pet ...";
    int c = std::tolower(getch());
    if (!('1' <= c && c <= '5')) {
        status = "[SELL]: Invalid pet index";
        return;
    }

    std::string pet_name;
    if ((c - '1') < (int)game->team->pets.size())
        pet_name = game->team->pets[c - '1']->name;

    game->sell(c - '1');
    if (!pet_name.empty())
        status = "[SELL]: Sold " + pet_name + " (index " + std::to_string(c - '0') + ")";
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
    status = "[COMBINE_TEAM]: Combining pets ... and ...";
    draw_status();

    int c1 = std::tolower(getch());
    if (!('1' <= c1 && c1 <= '5')) {
        status = "[COMBINE_TEAM]: Invalid pet index";
        return;
    }
    status = "[COMBINE_TEAM]: Combining pets " + std::to_string(c1 - '0') + " and ...";
    draw_status();

    int c2 = std::tolower(getch());
    if (!('1' <= c2 && c2 <= '5')) {
        status = "[COMBINE_TEAM]: Invalid pet index";
        return;
    }
    status = "[COMBINE_TEAM]: Combining pets " + std::to_string(c1 - '0') + " and " + std::to_string(c2 - '0');

    game->combine_team(c1 - '1', c2 - '1');
}

void UserInterface::combine_shop() {
    state = UIState::none;
    status = "[COMBINE_SHOP]: Combining shop pet ... with team pet ...";
    draw_status();

    int c1 = std::tolower(getch());
    if (!('1' <= c1 && c1 <= '5')) {
        status = "[COMBINE_SHOP]: Invalid pet index";
        return;
    }
    status = "[COMBINE_SHOP]: Combining shop pet " + std::to_string(c1 - '0') + " with team pet ...";
    draw_status();

    int c2 = std::tolower(getch());
    if (!('1' <= c2 && c2 <= '5')) {
        status = "[COMBINE_SHOP]: Invalid pet index";
        return;
    }
    status = "[COMBINE_SHOP]: Combining shop pet " + std::to_string(c1 - '0') + " with team pet " + std::to_string(c2 - '0');

    game->combine_shop(c1 - '1', c2 - '1');
}

void UserInterface::order() {
    state = UIState::none;
    status = "[ORDER]: Switching ... and ...";
    draw_status();

    int c1 = std::tolower(getch());
    if (!('1' <= c1 && c1 <= '5')) {
        status = "[ORDER]: Invalid order index";
        return;
    }
    status = "[ORDER]: Switching " + std::to_string(c1 - '0') + " and ...";
    draw_status();

    int c2 = std::tolower(getch());
    if (!('1' <= c2 && c2 <= '5')) {
        status = "[ORDER]: Invalid order index";
        return;
    }
    status = "[ORDER]: Switching " + std::to_string(c1 - '0') + " and " + std::to_string(c2 - '0');

    size_t indices[5] = {0, 1, 2, 3, 4};
    indices[c1 - '1'] = c2 - '1';
    indices[c2 - '1'] = c1 - '1';

    game->team->order(indices);
}

bool UserInterface::fight() {
    clear();
    draw_frame();
    draw_action();

    draw_fight();
    char c;
    bool invalid;
    do {
        c = std::tolower(getch());
        invalid = (c != 'a' && c != 'p' && c != 'n' && c != 's' && c != 'q');
        if (invalid) {
            status = "Invalid action !";
            draw_status();
        }
    } while (invalid);

    while (!game->fight_step()) {
        if (c == 's' || c == 'q') continue;
        draw_fight();
        if (c == 'a') {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        } else if (c == 'p' || c == 'n') {
            do {
                c = std::tolower(getch());
                invalid = (c != 'a' && c != 'p' && c != 'n' && c != 's' && c != 'q');
                if (invalid) {
                    status = "Invalid action !";
                    draw_status();
                }
            } while (invalid);
        }
    }
    status = "";

    state = UIState::none;
    return (game->life > 0 && game->victories < 10);
}


void UserInterface::draw_frame() const {
    std::string hborder(COLS-2, '-');
    hborder = "+" + hborder + "+";
    mvaddstr(0, 0, hborder.c_str());
    mvaddstr(LINES-1, 0, hborder.c_str());
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
    if (pet->attack != pet->tmp_attack)
        attron(A_UNDERLINE);
    mvprintw(y+2, x+1, "%02d", pet->tmp_attack);
    attroff(A_UNDERLINE);

    mvaddch(y+2, x+5, '/');

    if (pet->life != pet->tmp_life)
        attron(A_UNDERLINE);
    mvprintw(y+2, x+7, "%02d", pet->tmp_life);
    attroff(A_UNDERLINE);

    int lvl = pet->get_level();
    if (draw_xp) {
        int xp = pet->get_xp();
        if (lvl == 1)
            mvprintw(y+3, x, "Lvl 1 %d/2", xp);
        else if (lvl == 2)
            mvprintw(y+3, x, "Lvl 2 %d/3", xp - 2);
        else
            mvaddstr(y+3, x, "Lvl 3 0/0");
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
        mvaddstr(8, padding, "  Empty  ");
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
            mvaddstr(15, padding, "  ___  ");
        padding += 9 + inner_padding;
    }
    padding += (9 + inner_padding) * (5 - game->shop->pets.size());

    for (size_t i=0; i<game->shop->objects.size(); i++) {
        if (game->shop->objects[i])
            draw_object(game->shop->objects[i], padding, 14, game->shop->frozen_objects[i]);
        else
            mvaddstr(15, padding, "  ___  ");
        padding += 9 + inner_padding;
    }
}

void UserInterface::draw_action() const {
    std::string empty_msg(COLS-3, ' ');
    mvaddstr(20, 1, empty_msg.c_str());
    mvaddstr(20, 1, MSGS.at(state).c_str());
}

void UserInterface::draw_fight() const {
    int middle = COLS / 2;
    int padding = (middle - 5*9) / 6;

    for (int i=0; i<4; i++)
        mvaddch(6+i, middle, '|');

    for (size_t ind=0; ind<game->team->tmp_pets.size(); ind++) {
        int x = middle - padding*2*(ind+1);
        draw_pet(game->team->tmp_pets[ind], x, 6, true, false);
    }

    for (size_t ind=0; ind<game->adv_team->tmp_pets.size(); ind++) {
        int x = middle + padding*(2*ind+1);
        draw_pet(game->adv_team->tmp_pets[ind], x, 6, true, false);
    }
}

void UserInterface::draw_status() const {
    std::string empty_msg(COLS-3, ' ');
    mvaddstr(21, 1, empty_msg.c_str());
    mvaddstr(21, 1, status.c_str());
}
