
#include "Pets/Bat.hpp"

#include <string>

#include "Objects/Items/Weak.hpp"
#include "utils.hpp"


Bat::Bat(Team* team, Shop* shop) : Pet("Bat", team, shop) {
    repr = "🦇";
    id = 13;
    pack = PACK_DLC1;
    tier = 2;
    attack = 1;
    life = 2;
    reset_stats();
}

Bat::~Bat() { }

void Bat::on_start_battle(Team* adv_team) {
    int lvl = get_level();
    utils::vector_logs.push_back("Start of battle: " + name + " makes " + std::to_string(lvl) + " enemy pets weak.");

    std::vector<Pet*> adv_pets = adv_team->get_pets();
    std::vector<Pet*> living_pets;

    std::copy_if(adv_pets.begin(), adv_pets.end(),
                 std::back_inserter(living_pets),
                 [this](Pet* pet) { return pet->is_alive(); });

    std::vector<Pet*> targets = utils::choice(living_pets, lvl);

    for (Pet* target : targets) {
        Object* weak = new Weak(team, shop);
        target->equip_object(weak, true);
    }
}
