
#include "Pets/Beetle.hpp"

#include "utils.hpp"


Beetle::Beetle(Team* team, Shop* shop) : Pet("beetle", team, shop) {
    repr = "🪲";
    id = 3;
    pack = PACK_DLC1;
    tier = 1;
    attack = 2;
    life = 3;
    reset_stats();
}

Beetle::~Beetle() { }

void Beetle::on_object(Object* object) {
    spdlog::debug("{} fed, buffing shop !", name);
    int lvl = get_level();
    shop->upgrade(0, lvl, true);
}
