
#include "Pets/Beetle.hpp"

#include "utils.hpp"


Beetle::Beetle(Team* team, Shop* shop) : Pet("Beetle", team, shop) {
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
    utils::vector_logs.push_back(name + " fed, buffing shop !");
    int lvl = get_level();
    shop->upgrade(0, lvl, true);
}
