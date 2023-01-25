
#include "Pets/Swan.hpp"

#include <string>

#include "utils.hpp"


Swan::Swan(Team* team, Shop* shop) : Pet("Swan", team, shop) {
    m_repr = "🦢";
    m_id = 25;
    m_pack = PACK_STANDARD | PACK_DLC1;
    m_tier = 2;
    m_attack = 1;
    m_life = 3;
    reset_stats();
}

Swan::~Swan() { }

void Swan::on_start_turn() {
    int lvl = get_level();
    utils::vector_logs.push_back("Start of turn: " + m_name + " earns " + std::to_string(lvl) + " gold");

    m_team->earn_money(lvl);
}
