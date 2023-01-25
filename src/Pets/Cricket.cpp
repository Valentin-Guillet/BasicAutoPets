
#include "Pets/Cricket.hpp"

#include "Pets/ZombieCricket.hpp"
#include "utils.hpp"


Cricket::Cricket(Team* team, Shop* shop) : Pet("Cricket", team, shop) {
    m_repr = "🦗";
    m_id = 5;
    m_pack = PACK_STANDARD | PACK_DLC1;
    m_tier = 1;
    m_attack = 1;
    m_life = 2;
    reset_stats();
}

Cricket::~Cricket() { }

void Cricket::on_faint(Pos pos) {
    utils::vector_logs.push_back(m_name + " fainting !");

    int lvl = get_level();
    Pet* zombie = new ZombieCricket(m_team, m_shop, lvl);
    zombie->bind(m_adv_team);
    m_team->summon(pos, zombie);

    Pet::on_faint(pos);
}
