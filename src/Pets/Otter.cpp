
#include "Pets/Otter.hpp"

#include "utils.hpp"


Otter::Otter(Team* team, Shop* shop) : Pet("Otter", team, shop) {
    m_repr = "🦦";
    m_id = 11;
    m_pack = PACK_STANDARD;
    m_tier = 1;
    m_attack = 1;
    m_life = 2;
    reset_stats();
}

Otter::~Otter() { }

void Otter::on_buy() {
    utils::vector_logs.push_back(m_name + " bought, buffing random friend !");

    int lvl = get_level();
    std::vector<Pet*> team_pets = m_team->get_pets();
    if (team_pets.empty())
        return;

    Pet* target = utils::choice(team_pets)[0];
    target->buff(lvl, lvl, false);
}
