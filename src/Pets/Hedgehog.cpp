
#include "Pets/Hedgehog.hpp"

#include <string>

#include "utils.hpp"


Hedgehog::Hedgehog(Team* team, Shop* shop) : Pet("Hedgehog", team, shop) {
    repr ="🦔";
    id = 20;
    pack = PACK_STANDARD | PACK_DLC1;
    tier = 2;
    attack = 3;
    life = 2;
    reset_stats();
}

Hedgehog::~Hedgehog() { }

void Hedgehog::on_faint(Pos pos) {
    int damages = 2 * get_level();

    utils::vector_logs.push_back(name + " faints, dealing " + std::to_string(damages) + " damages to all pets");

    for (Pet* pet : team->get_pets()) {
        if (pet->is_alive())
            pet->take_damage(damages);
    }

    if (adv_team) {
        for (Pet* pet : adv_team->get_pets()) {
            if (pet->is_alive())
                pet->take_damage(damages);
        }
    }

    Pet::on_faint(pos);
}
