
#include "game.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

#include "object.hpp"
#include "utils.hpp"


static int life_per_turn(int turn) {
    if (turn < 3)
        return 1;
    else if (turn < 5)
        return 2;
    return 3;
}


Game::Game() : life(10), victories(0), turn(0) {
    team = new Team(this);
    shop = new Shop(team);
    begin_turn();
    fight_status = FIGHT_STATUS::None;
};

Game::~Game() {
    Team::clear_team_list();
    delete team;
    delete shop;
}

void Game::reset() {
    life = 10;
    victories = 0;
    turn = 0;

    delete team;
    delete shop;
    team = new Team(this);
    shop = new Shop(team);

    begin_turn();
}


void Game::begin_turn() {
    money = 10;
    shop->begin_turn();
    team->begin_turn();
    turn++;
}

void Game::move(size_t src_index, size_t dst_index) {
    team->move(src_index, dst_index);
}

void Game::end_turn() {
    team->end_turn();
}

bool Game::is_over() const {
    return (life > 0 && victories < 10);
}

void Game::start_fight() {
    adv_team = Team::get_random_team(turn);
    fighting_team = Team::copy_team(team);
    fight_status = FIGHT_STATUS::Fighting;
}

bool Game::fight_step() {
    fight_status = Team::fight_step(fighting_team, adv_team);
    return in_fight();
}

void Game::end_fight() {
    if (fight_status == FIGHT_STATUS::Win)
        victories++;

    else if (fight_status == FIGHT_STATUS::Loss)
        life -= life_per_turn(turn);

    delete fighting_team;
    delete adv_team;
    fighting_team = nullptr;
    adv_team = nullptr;

    if (life > 0)
        begin_turn();

    fight_status = FIGHT_STATUS::None;
}

bool Game::in_fight() const {
    return fight_status == FIGHT_STATUS::Fighting;
}

void Game::buy_pet(size_t index) {
    check_money("BUY_PET", 3);
    if (team->get_nb_pets() == 5)
        throw InvalidAction("[BUY_PET]: already have 5 pets in the team !");

    Pet* pet = shop->buy_pet(index);
    team->add(pet);
    money -= 3;
}

void Game::combine_shop(size_t index_shop, size_t index_team) {
    check_money("COMBINE_SHOP", 3);
    std::string shop_pet_name = shop->get_pet_name(index_shop);
    team->can_combine(index_team, shop_pet_name);

    Pet* pet = shop->buy_pet(index_shop);
    team->combine(index_team, pet);
    money -= 3;
}

void Game::combine_team(size_t src_index, size_t dst_index) {
    team->combine(src_index, dst_index);
}

void Game::sell(size_t index) {
    money += team->sell(index);
}

void Game::buy_object(size_t index, size_t index_target) {
    int cost = shop->get_cost_object(index);
    check_money("BUY_OBJECT", cost);

    shop->buy_object(index, index_target);
    money -= cost;
}

void Game::roll() {
    check_money("ROLL", 1);

    shop->roll();
    money--;
}

void Game::freeze_pet(size_t index) {
    shop->freeze_pet(index);
}

void Game::freeze_object(size_t index) {
    shop->freeze_object(index);
}

void Game::earn_money(int amount) {
    money += amount;
}

std::string Game::serialize() const {
    std::string state = std::to_string(turn) + " ";
    state += std::to_string(life) + " ";
    state += std::to_string(victories) + " ";
    state += std::to_string(money) + "\n";
    state += team->serialize() + "\n";
    state += shop->serialize();
    return state;
}

void Game::unserialize(std::string game_str) {
    std::stringstream stream(game_str);
    std::string line;

    std::getline(stream, line, '\n');
    int index = line.find(' ');
    turn = std::stoi(line.substr(0, index));
    line = line.substr(index+1);

    index = line.find(' ');
    life = std::stoi(line.substr(0, index));
    line = line.substr(index+1);

    index = line.find(' ');
    victories = std::stoi(line.substr(0, index));
    line = line.substr(index+1);

    index = line.find(' ');
    money = std::stoi(line.substr(0, index));

    std::string turn_str = std::to_string(turn) + " ";
    delete team;
    std::getline(stream, line, '\n');
    team = Team::unserialize(this, turn_str + line);

    delete shop;
    std::getline(stream, line, '\n');
    shop = Shop::unserialize(team, turn_str + line);
}

void Game::save_state() const {
    std::string state = serialize();
    std::ofstream file("data/game_save");
    if (!file) {
        std::cout << "Couldn't save file" << std::endl;
        return;
    }

    file << state;
    file.close();
}

void Game::load_state() {
    std::ifstream file("data/game_save");
    if (!file) {
        std::cout << "Couldn't load file" << std::endl;
        return;
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string state = buffer.str();
    file.close();

    unserialize(state);
}

void Game::cheat() {
    money += 1000;
}


void Game::check_money(std::string action, int amount) const {
    if (money >= amount)
        return;

    std::string msg = "[" + action + "]: not enough money to do this action";
    msg += " (" + std::to_string(money) + " gold left)";
    throw InvalidAction(msg);
}
