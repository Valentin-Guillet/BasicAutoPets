
#include "Pets/Dromedary.hpp"

#include "utils.hpp"


Dromedary::Dromedary(Team* team, Shop* shop) : Pet("Dromedary", team, shop) {
    repr = "🐪";
    id = 17;
    pack = PACK_DLC1;
    tier = 2;
    attack = 2;
    life = 4;
    reset_stats();
}

Dromedary::~Dromedary() { }

void Dromedary::on_start_turn() {
    utils::vector_logs.push_back("Start of turn: " + name + " buffs pet shops");
    int lvl = get_level();
    shop->upgrade(lvl, lvl, true);
}
