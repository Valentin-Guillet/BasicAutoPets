
#include "Objects/Foods/Pill.hpp"

#include <vector>

#include "utils.hpp"


Pill::Pill(Team* team, Shop* shop) : Object("Pill", team, shop, ObjType::FOOD) {
    m_repr = "💊";
    m_id = 5;
    m_tier = 2;
    m_cost = 1;
}

Pill::~Pill() { }

void Pill::on_buy(size_t index) {
    utils::vector_logs.push_back(m_name + " bought !");

    if (!m_team->has_pet(index))
        return;

    Pet* pet = m_team->get_pets()[m_team->pos_to_index(index)];
    pet->kill();
}
