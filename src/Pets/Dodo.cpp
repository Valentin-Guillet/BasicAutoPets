
#include "Pets/Dodo.hpp"

#include "utils.hpp"


Dodo::Dodo(Team* team, Shop* shop) : Pet("Dodo", team, shop) {
    repr = "🦤";
    id = 16;
    pack = PACK_STANDARD;
    tier = 2;
    attack = 2;
    life = 3;
    reset_stats();
}

Dodo::~Dodo() { }

void Dodo::on_start_battle() {
    utils::vector_logs.push_back("Start of battle: " + name + " gives attack ahead");

    int lvl = get_level();
    int attack_bonus = ((lvl * get_attack()) + 1) / 2;
    std::vector<Pet*> pets = team->get_pets();

    int index = -1;
    for (size_t i=0; i<pets.size(); i++) {
        if (pets[i] == this) {
            index = i;
            break;
        }
    }
    index--;

    while (index >= 0) {
        if (pets[index]->is_alive()) {
            pets[index]->buff(attack_bonus, 0, false);
            break;
        }
    }
}
