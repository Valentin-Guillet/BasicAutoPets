
#include "Pets/Dromedary.hpp"

#include "utils.hpp"


Dromedary::Dromedary(Team* team, Shop* shop) : Pet("Dromedary", team, shop) {
    m_repr = "🐪";
    m_id = 17;
    m_pack = PACK_DLC1;
    m_tier = 2;
    m_attack = 2;
    m_life = 4;
    reset_stats();
}

Dromedary::~Dromedary() { }

void Dromedary::on_start_turn() {
    utils::vector_logs.push_back("Start of turn: " + m_name + " buffs pet shops");
    int lvl = get_level();
    m_shop->upgrade(lvl, lvl, true);
}
