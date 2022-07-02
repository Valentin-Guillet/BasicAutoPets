
#include "Pets/Ant.hpp"

#include <algorithm>
#include <iterator>
#include <vector>

#include "utils.hpp"


Ant::Ant(Team* team, Shop* shop) : Pet("Ant", team, shop) {
    repr = "🐜";
    id = 1;
    pack = PACK_STANDARD | PACK_DLC1;
    tier = 1;
    attack = 2;
    life = 1;
    reset_stats();
};

Ant::~Ant() { }

void Ant::on_faint(Pos pos) {
    utils::vector_logs.push_back(name + " fainting !");

    std::vector<Pet*> team_pets = team->get_pets();
    std::vector<Pet*> living_pets;

    std::copy_if(team_pets.begin(), team_pets.end(),
                 std::back_inserter(living_pets),
                 [this](Pet* pet) { return pet->is_alive() && pet != this; });

    if (!living_pets.empty()) {
        Pet* target = utils::choice(living_pets)[0];
        int lvl = get_level();
        target->buff(2*lvl, 1*lvl, false);
    }

    Pet::on_faint(pos);
}
