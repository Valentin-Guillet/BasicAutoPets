
#include "animal.hpp"

#include <iostream>

#include "Animals/Ant.hpp"


Animal* Animal::create_random_animal(Team* team, Shop* shop, int max_tier) {
    return new Ant(team, shop);
}

Animal::Animal(std::string name, Team* team, Shop* shop) :
        name(name), team(team), shop(shop), xp(0) {
    reset_stats();
}

void Animal::reset_stats() {
    tmp_life = life;
    tmp_attack = attack;
}

int Animal::get_xp() const {
    return xp;
}

void Animal::draw() const {
    std::cout << name << " (tier " << tier << "): [" << tmp_life << "/" << tmp_attack << "]";
    std::cout << ", " << xp << "xp" << std::endl;
}
