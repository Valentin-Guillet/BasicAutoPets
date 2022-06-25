
#include "Pets/Otter.hpp"

#include "utils.hpp"


Otter::Otter(Team* team, Shop* shop) : Pet("Otter", team, shop) {
    repr = "🦦";
    id = 11;
    pack = PACK_STANDARD;
    tier = 1;
    attack = 1;
    life = 2;
    reset_stats();
}

Otter::~Otter() { }

void Otter::on_buy() {
    utils::vector_logs.push_back(name + " bought, buffing random friend !");

    int lvl = get_level();
    std::vector<Pet*> team_pets = team->get_pets();
    if (team_pets.empty())
        return;

    Pet* target = utils::choice(team_pets)[0];
    target->buff(lvl, lvl, false);
}
