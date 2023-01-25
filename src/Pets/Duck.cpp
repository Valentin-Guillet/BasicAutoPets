
#include "Pets/Duck.hpp"

#include "utils.hpp"


Duck::Duck(Team* team, Shop* shop) : Pet("Duck", team, shop) {
    m_repr = "🦆";
    m_id = 6;
    m_pack = PACK_STANDARD;
    m_tier = 1;
    m_attack = 1;
    m_life = 3;
    reset_stats();
}

Duck::~Duck() { }

void Duck::on_sell() {
    utils::vector_logs.push_back(m_name + " sold, buffing shop !");

    int lvl = get_level();
    m_shop->upgrade(0, lvl, true);
}
