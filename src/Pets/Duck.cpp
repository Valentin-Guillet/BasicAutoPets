
#include "Pets/Duck.hpp"

#include "utils.hpp"


Duck::Duck(Team* team, Shop* shop) : Pet("duck", team, shop) {
    repr = "🦆";
    id = 6;
    pack = PACK_STANDARD;
    tier = 1;
    attack = 1;
    life = 3;
    reset_stats();
}

Duck::~Duck() { }

void Duck::on_sell() {
    utils::vector_logs.push_back(name + " sold, buffing shop !");

    int lvl = get_level();
    shop->upgrade(0, lvl, true);
}
