
#include "Pets/Bee.hpp"


Bee::Bee(Team* team, Shop* shop) : Pet("Bee", team, shop) {
    repr = "🐝";
    id = 89;
    pack = PACK_STANDARD | PACK_DLC1;
    tier = -1;
    attack = 1;
    life = 1;
    reset_stats();
}

Bee::~Bee() { }
