
#include "game.hpp"

#include <iostream>
#include <string>

#include "object.hpp"
#include "utils.hpp"


static int life_per_turn(int turn) {
    return 3;
}


Game::Game() : life(10), victories(0), turn(0) {
    team = new Team();
    shop = new Shop(team);
    begin_turn();
};

Game::~Game() {
    Team::clear_team_list();
    delete team;
    delete shop;
}


void Game::begin_turn() {
    money = 10;
    shop->begin_turn();
    team->begin_turn();
    turn++;

    adv_team = Team::get_random_team(turn);
}

bool Game::end_turn(size_t indices[5]) {
    team->order(indices);
    team->end_turn();

    int victory = fight();
    if (victory == 1)
        victories++;
    else if (victory == -1)
        life -= life_per_turn(turn);

    if (life > 0)
        begin_turn();
    else
        std::cout << "You lost ! Game over" << std::endl;
    return life > 0;
}

int Game::fight() {
    Team* other_team = Team::get_random_team(turn);

    return team->fight(other_team);
}

bool Game::fight_step() {
    int end_fight = team->fight_step(adv_team);

    if (end_fight != -1) {
        if (end_fight == 1)
            victories++;
        else if (end_fight == 2)
            life -= life_per_turn(turn);

        team->reset();
        adv_team->reset();

        if (life > 0)
            begin_turn();
    }
    return end_fight != -1;
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

void Game::get_state() const {

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
