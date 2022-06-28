
#include "Pets/Mosquito.hpp"

#include <string>

#include "utils.hpp"


Mosquito::Mosquito(Team* team, Shop* shop) : Pet("Mosquito", team, shop) {
    repr = "🦟";
    id = 10;
    pack = PACK_STANDARD | PACK_DLC1;
    tier = 1;
    attack = 2;
    life = 2;
    reset_stats();
}

Mosquito::~Mosquito() { }

void Mosquito::on_start_battle(Team* adv_team) {
    int lvl = get_level();
    utils::vector_logs.push_back("Start of battle: " + name + " shots " + std::to_string(lvl) + " times.");

    std::vector<Pet*> adv_pets = adv_team->get_pets();
    std::vector<Pet*> living_pets;

    std::copy_if(adv_pets.begin(), adv_pets.end(),
                 std::back_inserter(living_pets),
                 [this](Pet* pet) { return pet->is_alive(); });

    std::vector<Pet*> targets = utils::choice(living_pets, lvl);
    for (Pet* target : targets)
        target->take_damage(1);
}
