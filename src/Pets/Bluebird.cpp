
#include "Pets/Bluebird.hpp"

#include <vector>

#include "utils.hpp"


Bluebird::Bluebird(Team* team, Shop* shop) : Pet("bluebird", team, shop) {
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
    spdlog::debug("End of turn, {} buff !", name);
    std::vector<Pet*> team_pets = get_team_pets();

    int lvl = get_level();
    team_pets.back()->buff(lvl, 0, false);
}
