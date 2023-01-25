
#include "Pets/Beaver.hpp"

#include <vector>

#include "utils.hpp"


Beaver::Beaver(Team* team, Shop* shop) : Pet("Beaver", team, shop) {
    m_repr = "🦫";
    m_id = 2;
    m_pack = PACK_STANDARD | PACK_DLC1;
    m_tier = 1;
    m_attack = 2;
    m_life = 2;
    reset_stats();
}

Beaver::~Beaver() { }

void Beaver::on_sell() {
    utils::vector_logs.push_back(m_name + " sold !");
    std::vector<Pet*> team_pets = m_team->get_pets();

    int lvl = get_level();
    std::vector<Pet*> targets = utils::choice(team_pets, 2);
    for (Pet* target : targets)
        target->buff(0, lvl, false);
}
