
#include "Pets/DirtyRat.hpp"


DirtyRat::DirtyRat(Team* team, Shop* shop) : Pet("DirtyRat", team, shop) {
    repr = "Z🐀";
    id = 85;
    pack = PACK_STANDARD | PACK_DLC1;
    tier = -1;
    attack = 1;
    life = 1;
    reset_stats();
}

DirtyRat::~DirtyRat() { }
