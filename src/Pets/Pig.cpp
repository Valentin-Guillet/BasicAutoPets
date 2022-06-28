
#include "Pets/Pig.hpp"

#include <string>

#include "utils.hpp"


Pig::Pig(Team* team, Shop* shop) : Pet("Pig", team, shop) {
    repr = "🐖";
    id = 12;
    pack = PACK_STANDARD | PACK_DLC1;
    tier = 1;
    attack = 3;
    life = 1;
    reset_stats();
}

Pig::~Pig() { }

void Pig::on_sell() {
    int lvl = get_level();
    team->earn_money(lvl);

    utils::vector_logs.push_back(name + " sold, " + std::to_string(lvl) + " gold earned");
}
