
#include "Pets/Hedgehog.hpp"

#include <string>

#include "utils.hpp"


Hedgehog::Hedgehog(Team* team, Shop* shop) : Pet("Hedgehog", team, shop) {
    m_repr ="🦔";
    m_id = 20;
    m_pack = PACK_STANDARD | PACK_DLC1;
    m_tier = 2;
    m_attack = 3;
    m_life = 2;
    reset_stats();
}

Hedgehog::~Hedgehog() { }

void Hedgehog::on_faint(Pos pos) {
    int damages = 2 * get_level();

    utils::vector_logs.push_back(m_name + " faints, dealing " + std::to_string(damages) + " damages to all pets");

    for (Pet* pet : m_team->get_pets()) {
        if (pet->is_alive())
            pet->take_damage(damages);
    }

    if (m_adv_team) {
        for (Pet* pet : m_adv_team->get_pets()) {
            if (pet->is_alive())
                pet->take_damage(damages);
        }
    }

    Pet::on_faint(pos);
}
