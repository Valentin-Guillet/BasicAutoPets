
#include "game.hpp"

#include <iostream>
#include <string>


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
    shop->roll();
    turn++;
}

bool Game::end_turn(int indices[5]) {
    team->order(indices);

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

void Game::buy_animal(int index) {
    Animal* animal = shop->buy_animal(index);
    team->add(animal);
    money -= 3;
}

void Game::upgrade(int index_shop, int index_team) {
    Animal* animal = shop->buy_animal(index_shop);
    team->upgrade(index_team, animal);
    delete animal;
    money -= 3;
}

void Game::sell(int index) {
    money += team->sell(index);
}

void Game::buy_object(int index, int index_target) {
    Object* object = shop->buy_object(index, index_target);
    if (object != nullptr)   // Item
        team->equip_item(index_target, object);
}

void Game::roll() {
    shop->roll();
    money--;
}

void Game::freeze_animal(int index) {
    shop->freeze_animal(index);
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
