
#include "Pets/Crab.hpp"

#include "utils.hpp"


Crab::Crab(Team* team, Shop* shop) : Pet("Crab", team, shop) {
    repr = "🦀";
    id = 15;
    pack = PACK_STANDARD;
    tier = 2;
    attack = 3;
    life = 3;
    reset_stats();
}

Crab::~Crab() { }

void Crab::on_buy() {
    utils::vector_logs.push_back("Buying " + name + ": copying health from most healthy pet");
    std::vector<Pet*> team_pets = team->get_pets();

    int new_life = life;
    for (Pet* pet : team->get_pets()) {
        if (pet->get_life() > new_life)
            new_life = pet->get_life();
    }
    life = new_life;
}
