
#include "Animals/Ant.hpp"

#include <iostream>


Ant::Ant(Team* team, Shop* shop) : Animal("ant", team, shop) {
    id = 0;
    pack = PACK_STANDARD | PACK_DLC1;
    tier = 1;
    life = 1;
    attack = 2;
};

Ant::~Ant() { }

void Ant::on_faint() {
    std::cout << "[" << name << "] I'm fainting !" << std::endl;
}
