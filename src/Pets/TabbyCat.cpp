
#include "Pets/TabbyCat.hpp"

#include "utils.hpp"


TabbyCat::TabbyCat(Team* team, Shop* shop) : Pet("TabbyCat", team, shop) {
    m_repr = "🐈";
    m_id = 26;
    m_pack = PACK_DLC1;
    m_tier = 2;
    m_attack = 5;
    m_life = 3;
    reset_stats();
}

TabbyCat::~TabbyCat() { }

void TabbyCat::on_object(Object* object) {
    utils::vector_logs.push_back(m_name + " fed, buffing friends !");
    int lvl = get_level();

    for (Pet* pet : m_team->get_pets()) {
        if (pet != this)
            pet->buff(lvl, 0, true);
    }
}
