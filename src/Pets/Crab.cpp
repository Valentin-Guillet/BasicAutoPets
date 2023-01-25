
#include "Pets/Crab.hpp"

#include "utils.hpp"


Crab::Crab(Team* team, Shop* shop) : Pet("Crab", team, shop) {
    m_repr = "🦀";
    m_id = 15;
    m_pack = PACK_STANDARD;
    m_tier = 2;
    m_attack = 3;
    m_life = 3;
    reset_stats();
}

Crab::~Crab() { }

void Crab::on_buy() {
    utils::vector_logs.push_back("Buying " + m_name + ": copying health from most healthy pet");
    std::vector<Pet*> team_pets = m_team->get_pets();

    int new_life = m_life;
    for (Pet* pet : m_team->get_pets()) {
        if (pet->get_life() > new_life)
            new_life = pet->get_life();
    }
    m_life = new_life;
}
