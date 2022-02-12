
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
    team->begin_turn();
    shop->begin_turn();
    turn++;
}

bool Game::end_turn(int indices[5]) {
    team->order(indices);
    team->end_turn();

    int victory = fight();
    if (victory == 1)
        victories++;
    else
        life -= life_per_turn(turn);

    if (life > 0) {
        begin_turn();
        return true;
    } else {
        std::cout << "You lost ! Game over" << std::endl;
        return false;
    }
}

int Game::fight() {
    Team* other_team = Team::get_random_team(turn);

    std::cout << "Fight ! Other team:" << std::endl;
    other_team->draw();

    return team->fight(other_team);
}

void Game::buy_pet(int index) {
    check_money("BUY_PET", 3);
    if (team->get_nb_pets() == 5)
        throw InvalidAction("[BUY_PET]: already have 5 pets in the team !");

    Pet* pet = shop->buy_pet(index);
    team->add(pet);
    money -= 3;
}

void Game::upgrade(int index_shop, int index_team) {
    check_money("UPGRADE_PET", 3);

    Pet* pet = shop->buy_pet(index_shop);
    team->upgrade(index_team, pet);
    delete pet;
    money -= 3;
}

void Game::sell(int index) {
    money += team->sell(index);
}

void Game::buy_object(int index, int index_target) {
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

void Game::freeze_pet(int index) {
    shop->freeze_pet(index);
}

void Game::freeze_object(int index) {
    shop->freeze_object(index);
}

void Game::get_state() const {

}

void Game::draw() const {
    std::cout << "Turn " << turn << ", HP = " << life << ", " << victories << " wins, ";
    std::cout << money << " gold\n";
    std::cout << "Team:" << std::endl;
    team->draw();
    std::cout << "Shop:" << std::endl;
    shop->draw();
    std::cout << std::endl;
}

void Game::cheat() {
    money += 1000;
}


void Game::check_money(std::string action, int amount) const {
    if (money >= amount)
        return;

    std::string msg = "[" + action + "]: not enough money to buy";
    msg += " (" + std::to_string(money) + " gold left)";
    throw InvalidAction(msg);
}
