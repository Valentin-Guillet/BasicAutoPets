
#include "Pets/Spider.hpp"

#include "utils.hpp"


Spider::Spider(Team* team, Shop* shop) : Pet("Spider", team, shop) {
    m_repr = "🕷";
    m_id = 24;
    m_pack = PACK_STANDARD | PACK_DLC1;
    m_tier = 2;
    m_attack = 2;
    m_life = 2;
    reset_stats();
}

Spider::~Spider() { }

void Spider::on_faint(Pos pos) {
    utils::vector_logs.push_back(m_name + " fainting: summoning a tier 3 2/2 pet");

    Pet* new_pet = Pet::create_random_pet(m_team, m_shop, 3, true);
    new_pet->set_stats(2, 2, m_xp);
    new_pet->bind(m_adv_team);
    m_team->summon(pos, new_pet);

    Pet::on_faint(pos);
}
