
#include "Pets/Fish.hpp"

#include "utils.hpp"


Fish::Fish(Team* team, Shop* shop) : Pet("Fish", team, shop) {
    m_repr = "🐟";
    m_id = 7;
    m_pack = PACK_STANDARD | PACK_DLC1;
    m_tier = 1;
    m_attack = 2;
    m_life = 3;
    reset_stats();
}

Fish::~Fish() { }

void Fish::on_level_up() {
    utils::vector_logs.push_back(m_name + " level up, buffing other pets !");

    int lvl = get_level();
    for (Pet* pet : m_team->get_pets()) {
        if (pet == this)
            continue;
        pet->buff(lvl-1, lvl-1, false);
    }
}
