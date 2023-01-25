
#include "Pets/Pig.hpp"

#include <string>

#include "utils.hpp"


Pig::Pig(Team* team, Shop* shop) : Pet("Pig", team, shop) {
    m_repr = "🐖";
    m_id = 12;
    m_pack = PACK_STANDARD | PACK_DLC1;
    m_tier = 1;
    m_attack = 3;
    m_life = 1;
    reset_stats();
}

Pig::~Pig() { }

void Pig::on_sell() {
    int lvl = get_level();
    m_team->earn_money(lvl);

    utils::vector_logs.push_back(m_name + " sold, " + std::to_string(lvl) + " gold earned");
}
