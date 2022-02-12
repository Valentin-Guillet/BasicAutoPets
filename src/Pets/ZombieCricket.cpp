
#include "Pets/ZombieCricket.hpp"

ZombieCricket::ZombieCricket(Team* team, Shop* shop, int lvl) : Pet("zombiecricket", team, shop) {
    id = 0;
    pack = PACK_STANDARD | PACK_DLC1;
    tier = -1;
    attack = lvl;
    life = lvl;
    reset_stats();
}

ZombieCricket::~ZombieCricket() { }

