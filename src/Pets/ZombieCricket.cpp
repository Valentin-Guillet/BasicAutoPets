
#include "Pets/ZombieCricket.hpp"

ZombieCricket::ZombieCricket(Team* team, Shop* shop, int lvl) : Pet("ZombieCricket", team, shop) {
    m_repr = "Z🦗";
    m_id = 82;
    m_pack = PACK_STANDARD | PACK_DLC1;
    m_tier = -1;
    m_attack = lvl;
    m_life = lvl;
    reset_stats();
}

ZombieCricket::~ZombieCricket() { }
