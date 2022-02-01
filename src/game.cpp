
#include "game.hpp"

#include <iostream>
#include <string>


Game::Game() : life(10), victories(0), turn(1) {
    team = new Team();
    shop = new Shop(team);
    begin_turn();
};

Game::~Game() {
    delete team;
    delete shop;
}


void Game::begin_turn() {
    money = 10;
    team->begin_turn();
    shop->roll();
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

void Game::buy_object(int index) {
    Object* object = shop->buy_object(index);
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

void Game::end_turn(int indices[5]) {
    team->order(indices);
}

void Game::get_state() const {

}

void Game::draw() const {
    team->draw();
    shop->draw();
}
