
#include "Pets/Beetle.hpp"

#include "utils.hpp"


Beetle::Beetle(Team* team, Shop* shop) : Pet("Beetle", team, shop) {
    m_repr = "🪲";
    m_id = 3;
    m_pack = PACK_DLC1;
    m_tier = 1;
    m_attack = 2;
    m_life = 3;
    reset_stats();
}

Beetle::~Beetle() { }

void Beetle::on_object(Object* object) {
    utils::vector_logs.push_back(m_name + " fed, buffing shop !");
    int lvl = get_level();
    m_shop->upgrade(0, lvl, true);
}
