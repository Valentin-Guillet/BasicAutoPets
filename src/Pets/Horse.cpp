
#include "Pets/Horse.hpp"

#include "utils.hpp"


Horse::Horse(Team* team, Shop* shop) : Pet("Horse", team, shop) {
    m_repr = "🐎";
    m_id = 8;
    m_pack = PACK_STANDARD;
    m_tier = 1;
    m_attack = 2;
    m_life = 1;
    reset_stats();
}

Horse::~Horse() { }

void Horse::on_friend_summoned(Pet* new_pet) {
    utils::vector_logs.push_back(m_name + " applies temporary buff to new " + new_pet->m_name + "!");

    int lvl = get_level();
    new_pet->buff(lvl, 0, true);
}
