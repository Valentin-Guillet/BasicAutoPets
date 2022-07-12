
#include "Pets/Swan.hpp"

#include <string>

#include "utils.hpp"


Swan::Swan(Team* team, Shop* shop) : Pet("Swan", team, shop) {
    repr = "🦢";
    id = 25;
    pack = PACK_STANDARD | PACK_DLC1;
    tier = 2;
    attack = 1;
    life = 3;
    reset_stats();
}

Swan::~Swan() { }

void Swan::on_start_turn() {
    int lvl = get_level();
    utils::vector_logs.push_back("Start of turn: " + name + " earns " + std::to_string(lvl) + " gold");

    team->earn_money(lvl);
}
