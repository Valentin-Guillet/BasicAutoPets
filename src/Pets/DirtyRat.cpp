
#include "Pets/DirtyRat.hpp"


DirtyRat::DirtyRat(Team* team, Shop* shop) : Pet("DirtyRat", team, shop) {
    m_repr = "Z🐀";
    m_id = 85;
    m_pack = PACK_STANDARD | PACK_DLC1;
    m_tier = -1;
    m_attack = 1;
    m_life = 1;
    reset_stats();
}

DirtyRat::~DirtyRat() { }
