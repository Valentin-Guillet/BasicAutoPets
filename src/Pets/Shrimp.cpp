
#include "Pets/Shrimp.hpp"

#include "utils.hpp"


Shrimp::Shrimp(Team* team, Shop* shop) : Pet("Shrimp", team, shop) {
    repr = "🦐";
    id = 23;
    pack = PACK_STANDARD | PACK_DLC1;
    tier = 2;
    attack = 2;
    life = 3;
    reset_stats();
}

Shrimp::~Shrimp() { }

void Shrimp::on_friend_sold() {
    utils::vector_logs.push_back("Friend sold, " + name + " buff a random friend");

    std::vector<Pet*> team_pets = team->get_pets();
    std::vector<Pet*> other_pets;

    std::copy_if(team_pets.begin(), team_pets.end(),
                 std::back_inserter(other_pets),
                 [this](Pet* pet) { return pet != this; });

    if (other_pets.empty())
        return;

    Pet* target = utils::choice(other_pets)[0];
    int lvl = get_level();
    target->buff(0, lvl, false);
}
