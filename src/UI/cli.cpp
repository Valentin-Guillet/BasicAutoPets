

#include "UI/cli.hpp"

#include <algorithm>
#include <iostream>
#include <exception>
#include <sstream>

#include "utils.hpp"


const int SIZE = 75;
const std::string CLEAR_SCREEN = "\x1B[2J\x1B[H";

CLI::CLI(Game* game) : UserInterface(game) {
    game->cheat();
    prev_cmd = {"help"};
}

CLI::~CLI() {
    std::cout << "Deleting CLI" << std::endl;
}

bool CLI::run() {
    std::cout << CLEAR_SCREEN;
    bool continue_game;
    do {
        disp_game_state();
        disp_team();
        disp_shop();
        disp_logs();
        while (true) {
            try {
                continue_game = act();
                break;
            } catch (InvalidAction& e) {
                std::cerr << e.what_str() << std::endl;
            }
        }
    } while(continue_game);

    return play_again();
}


void CLI::get_curr_cmd(std::string line) {
    curr_cmd.clear();
    std::istringstream iss(line);
    std::string token;

    while (!iss.eof()) {
        iss >> token;
        curr_cmd.push_back(token);
    }
}

std::vector<int> CLI::get_args(size_t n) const {
    std::vector<int> ans;
    if (n >= curr_cmd.size())
        throw InvalidAction("Not enough arguments provided, needs " + std::to_string(n) + " but " + std::to_string(curr_cmd.size()-1) + " were provided");

    size_t i;
    try {
        for (i=1; i<n+1; i++)
            ans.push_back(std::stoi(curr_cmd[i]));
    } catch (std::exception& e) {
        throw InvalidAction("Invalid arguments: " + curr_cmd[i] + " is not a digit.");
    }

    return ans;
}

bool CLI::play_again() const {
    std::cout << "Game over ! " << std::endl;
    while (true) {
        std::cout << "Do you want to play again ? [y/N]" << std::endl;
        std::string action;
        getline(std::cin, action);
        action = utils::to_lower(action);
        if (!action.empty() && action[0] == 'y')
            return true;
        else if (action.empty() || action[0] == 'n')
            return false;
        std::cout << "Invalid choice, please type Yes or No" << std::endl;
    }
}

bool CLI::act() {
    std::string line;
    std::cout << "What do you want to do ?\n";
    std::getline(std::cin, line);
    if (line.empty()) {
        curr_cmd = prev_cmd;
    } else {
        get_curr_cmd(line);
        prev_cmd = curr_cmd;
    }

    std::string action = curr_cmd[0];
    if (action == "h" || action == "help")
        help();

    else if (action == "b" || action == "buy")
        buy();

    else if (action == "c" || action == "combine_team")
        combine_team();

    else if (action == "m" || action == "combine_shop")
        combine_shop();

    else if (action == "s" || action == "sell")
        sell();

    else if (action == "r" || action == "roll")
        roll();

    else if (action == "f" || action == "freeze")
        freeze();

    else if (action == "o" || action == "order")
        order();

    else if (action == "e" || action == "end_turn")
        return end_turn();

    else if (action == "d" || action == "download")
        download();

    else if (action == "l" || action == "load")
        load();

    else if (action == "q" || action == "quit")
        return false;

    else
        throw InvalidAction("Action " + action + " not recognized.");

    std::cout << CLEAR_SCREEN;
    return true;
}

void CLI::help() const {
    std::string help_msg;
    help_msg += "The different possible actions are:\n";
    help_msg += "- `b[uy] {ind}` to buy a pet\n";
    help_msg += "- `b[uy] {ind} [{ind_target}]` to buy an object ({ind_target} is optional for objects without targets)\n";
    help_msg += "- `s[ell] {ind}` to sell a pet\n";
    help_msg += "- `f[reeze] {ind}` to freeze a pet or an object\n";
    help_msg += "- `c[ombine_team] {ind1} {ind2}` to combine two pets from the team\n";
    help_msg += "- `m {ind_shop} {ind_team}` or `combine_shop {ind_shop} {ind_team}` to combine a pet from the shop with a pet from the team\n";
    help_msg += "- `r[oll]` to roll\n";
    help_msg += "- `o[rder] {ind1} {ind2}` to switch position of two pets in the team\n";
    help_msg += "- `e[nd_turn]` to end turn and run a new fight\n";
    help_msg += "\n";
    help_msg += "- `q[uit]` to quit the current game\n";
    help_msg += "- `h[elp] to print this help message`\n";
    help_msg += "\n";
    help_msg += "In each case, the index can design a pet in the team (between 1 and 5), a pet in the shop (between 1 and 7) or an object (9 or 0).\n";
    throw InvalidAction(help_msg);
}

void CLI::buy() {
    int index = get_args(1)[0];
    if (index == 9 || index == 0) {
        int ind_obj = (index == 9 ? 0 : 1);

        Object const* obj = get_shop_object(ind_obj);
        bool target_all;
        if (obj)
            target_all = obj->target_all;

        if (target_all) {
            game->buy_object(ind_obj, 0);
        } else {
            std::vector<int> args = get_args(2);
            int ind_target = args[1] - 1;
            game->buy_object(ind_obj, ind_target);
        }
    } else {
        game->buy_pet(index - 1);
    }
}

void CLI::combine_shop() {
    std::vector<int> args = get_args(2);
    int ind_shop = args[0] - 1;
    int ind_team = args[1] - 1;
    game->combine_shop(ind_shop, ind_team);
}

void CLI::combine_team() {
    std::vector<int> args = get_args(2);
    int ind_team_1 = args[0] - 1;
    int ind_team_2 = args[1] - 1;
    game->combine_team(ind_team_1, ind_team_2);
}

void CLI::sell() {
    int index = get_args(1)[0] - 1;
    game->sell(index);
}

void CLI::roll() {
    game->roll();
}

void CLI::freeze() {
    int index = get_args(1)[0];
    if (index == 9 || index == 0) {
        game->freeze_object((index == 9 ? 0 : 1));
    } else {
        game->freeze_pet(index - 1);
    }
}

void CLI::order() {
    std::vector<int> args = get_args(2);
    int ind1 = args[0] - 1;
    int ind2 = args[1] - 1;

    size_t indices[5] = {0, 1, 2, 3, 4};
    indices[ind1] = ind2;
    indices[ind2] = ind1;

    game->order(indices);
}

void CLI::fight() {
    disp_fight();

    std::string action;
    getline(std::cin, action);
    bool skip = (!action.empty() && (action[0] == 'q' || action[0] == 's'));
    int battle_status = game->fight_step();
    while (battle_status == -1) {
        if (!skip) {
            disp_fight();
            disp_logs();
            getline(std::cin, action);
            skip = (!action.empty() && (action[0] == 'q' || action[0] == 's'));
        }

        battle_status = game->fight_step();
    }

    disp_fight();
    disp_logs();
    std::cout << "Press a key to continue..." << std::endl;
    getline(std::cin, action);
    std::cout << CLEAR_SCREEN;

    game->reset_turn(battle_status);
}

bool CLI::end_turn() {
    game->end_turn();
    std::cout << CLEAR_SCREEN;
    disp_game_state();
    disp_team();
    disp_shop();
    disp_logs();
    std::cout << "Press a key to continue..." << std::endl;
    std::string key;
    getline(std::cin, key);
    std::cout << CLEAR_SCREEN;

    fight();
    return game->is_over();
}

void CLI::download() const {
    game->save_state();
    utils::vector_logs.push_back("Current game state saved");
}

void CLI::load() {
    game->load_state();
    utils::vector_logs.push_back("Loading game state");
}

void CLI::disp_game_state() const {
    std::cout << std::endl;
    std::cout << utils::pad("Money: " + std::to_string(get_money()), SIZE/4);
    std::cout << utils::pad("Life: " + std::to_string(get_life()), SIZE/4);
    std::cout << utils::pad("Victories: " + std::to_string(get_victories()), SIZE/4);
    std::cout << utils::pad("Turn: " + std::to_string(get_turn()), SIZE/4);
    std::cout << std::endl;
}

void CLI::disp_pet(int padding, Pet const* pet,
                   std::string& objects, std::string& pets,
                   std::string& stats, std::string& xps, bool in_fight) const {
    if (!pet) {
        objects += utils::pad("", padding);
        if (in_fight)
            pets += utils::pad("", padding);
        else
            pets += utils::pad("______", padding);
        stats += utils::pad("", padding);
        xps += utils::pad("", padding);

        return;
    }

    std::string obj_repr = get_object_repr(pet);
    objects += utils::pad(obj_repr, padding+(obj_repr.empty() ? 0 : 2));
    pets += utils::pad(get_repr(pet), padding+2);

    std::string attack = std::to_string(get_attack(pet));
    int pad = padding;
    if (!in_fight && has_attack_buff(pet)) {
        attack = "\e[4m" + attack + "\e[0m";
        pad += 8;
    }
    std::string life = std::to_string(get_life(pet));
    if (!in_fight && has_life_buff(pet)) {
        life = "\e[4m" + life + "\e[0m";
        pad += 8;
    }
    stats += utils::pad(attack + " / " + life, pad);

    int lvl = pet->get_level();
    int xp = pet->get_xp();
    if (lvl == 1)
        xps += utils::pad("Lvl 1 " + std::to_string(xp) + "/2", padding);
    else if (lvl == 2)
        xps += utils::pad("Lvl 1 " + std::to_string(xp - 2) + "/3", padding);
    else
        xps += utils::pad("Lvl 3 0/0", padding);
}

void CLI::disp_team() const {
    const int padding = SIZE / 5;

    std::cout << utils::pad("", SIZE, '-') << std::endl;
    std::string objects, pets, stats, xps;
    for (int i=4; i>=0; i--) {
        Pet const* pet = get_team_pet(i);
        disp_pet(padding, pet, objects, pets, stats, xps, false);
    }
    std::cout << objects << "\n" << pets << "\n" << stats << "\n" << xps << std::endl;
}

void CLI::disp_shop() const {
    const int padding = SIZE / 7;
    std::cout << std::endl;

    std::string pets, stats, frozen;
    for (int i=0; i<nb_pets_in_shop(); i++) {
        Pet const* pet = get_shop_pet(i);
        if (!pet) {
            pets += utils::pad("______", padding);
            stats += utils::pad("", padding);
            frozen += utils::pad("", padding);
        } else {
            pets += utils::pad(get_repr(pet), padding+2);

            std::string attack = std::to_string(get_attack(pet));
            std::string life = std::to_string(get_life(pet));
            stats += utils::pad(attack + " / " + life, padding);

            frozen += utils::pad((is_pet_frozen(i) ? "🧊" : ""), padding);
        }
    }
    pets += utils::pad("", padding * (5 - nb_pets_in_shop()));
    stats += utils::pad("", padding * (5 - nb_pets_in_shop()));
    frozen += utils::pad("", padding * (5 - nb_pets_in_shop()));

    for (int i=0; i<nb_objs_in_shop(); i++) {
        Object const* obj = get_shop_object(i);
        if (obj) {
            pets += utils::pad(get_repr(obj), padding);
            stats += utils::pad("Cost: " + std::to_string(get_cost(obj)), padding);
            frozen += utils::pad((is_obj_frozen(i) ? "🧊" : ""), padding);
        } else {
            pets += utils::pad("______", padding);
            stats += utils::pad("", padding);
            frozen += utils::pad("", padding);
        }
    }

    std::cout << "\n" << pets << "\n" << stats << "\n" << frozen << std::endl;
}

void CLI::disp_fight() const {
    const int padding = SIZE / 6;
    std::cout << CLEAR_SCREEN;

    std::string objects, pets, stats, xps;
    for (int i=4; i>=0; i--) {
        Pet const* pet = get_team_pet(i);
        disp_pet(padding, pet, objects, pets, stats, xps, true);
    }

    objects += "  |  ";
    pets += "  |  ";
    stats += "  |  ";
    xps += "  |  ";

    for (int i=0; i<5; i++) {
        Pet const* pet = get_adv_pet(i);
        disp_pet(padding, pet, objects, pets, stats, xps, true);
    }

    std::cout << objects << "\n" << pets << "\n" << stats << "\n" << xps << std::endl;
}

void CLI::disp_logs() const {
    for (size_t i=0; i<utils::vector_logs.size(); i++)
        std::cout << "> " << utils::vector_logs[i] << std::endl;
    std::cout << std::endl;

    utils::vector_logs.clear();
}
