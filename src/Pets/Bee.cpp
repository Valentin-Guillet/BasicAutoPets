
#include "Pets/Bee.hpp"

Bee::Bee(Team* team, Shop* shop) : Pet("bee", team, shop) {
    id = 0;
    pack = PACK_STANDARD | PACK_DLC1;
    tier = -1;
    attack = 1;
    life = 1;
    reset_stats();
}

Bee::~Bee() { }

