
#include "Pets/Rat.hpp"

#include <string>

#include "Pets/DirtyRat.hpp"
#include "utils.hpp"


Rat::Rat(Team* team, Shop* shop) : Pet("Rat", team, shop) {
    m_repr = "🐀";
    m_id = 22;
    m_pack = PACK_STANDARD | PACK_DLC1;
    m_tier = 2;
    m_attack = 4;
    m_life = 5;
    reset_stats();
}

Rat::~Rat() { }

void Rat::on_faint(Pos pos) {
    if (!m_adv_team)
        return;

    int lvl = get_level();
    utils::vector_logs.push_back(m_name + " faints, summon " + std::to_string(lvl) + " Dirty Rat !");

    for (int i=0; i<lvl; i++) {
        Pet* dirty_rat = new DirtyRat(m_adv_team, nullptr);
        dirty_rat->bind(m_team);
        m_adv_team->summon(-1, dirty_rat);
    }
}
