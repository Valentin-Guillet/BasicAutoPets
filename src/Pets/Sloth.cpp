
#include "Pets/Sloth.hpp"


Sloth::Sloth(Team* team, Shop* shop) : Pet("Sloth", team, shop) {
    m_repr = "🦥";
    m_id = 13;
    m_pack = PACK_STANDARD | PACK_DLC1;
    m_tier = 1;
    m_attack = 1;
    m_life = 1;
    reset_stats();
}

Sloth::~Sloth() { }
