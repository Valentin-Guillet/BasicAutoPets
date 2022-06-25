
#include "Pets/Bluebird.hpp"

#include <vector>

#include "utils.hpp"


Bluebird::Bluebird(Team* team, Shop* shop) : Pet("Bluebird", team, shop) {
    repr = "🐦";
    id = 4;
    pack = PACK_DLC1;
    tier = 1;
    attack = 2;
    life = 1;
    reset_stats();
}

Bluebird::~Bluebird() { }

void Bluebird::on_end_turn() {
    utils::vector_logs.push_back("End of turn, " + name + " buff !");
    std::vector<Pet*> team_pets = team->get_pets();

    int lvl = get_level();
    team_pets.back()->buff(lvl, 0, false);
}
