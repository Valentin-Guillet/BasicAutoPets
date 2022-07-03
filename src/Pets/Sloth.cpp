
#include "Pets/Sloth.hpp"


Sloth::Sloth(Team* team, Shop* shop) : Pet("Sloth", team, shop) {
    repr = "🦥";
    id = 13;
    pack = PACK_STANDARD | PACK_DLC1;
    tier = 1;
    attack = 1;
    life = 1;
    reset_stats();
}

Sloth::~Sloth() { }
