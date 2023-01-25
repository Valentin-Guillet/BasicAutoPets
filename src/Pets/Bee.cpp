
#include "Pets/Bee.hpp"


Bee::Bee(Team* team, Shop* shop) : Pet("Bee", team, shop) {
    m_repr = "🐝";
    m_id = 89;
    m_pack = PACK_STANDARD | PACK_DLC1;
    m_tier = -1;
    m_attack = 1;
    m_life = 1;
    reset_stats();
}

Bee::~Bee() { }
