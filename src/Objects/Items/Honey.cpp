
#include "Objects/Items/Honey.hpp"

#include "Pets/all_pets.hpp"
#include "utils.hpp"


Honey::Honey(Team* team, Shop* shop) : Object("Honey", team, shop, ObjType::ITEM) {
    m_repr = "🍯";
    m_id = 2;
    m_tier = 1;
}

Honey::~Honey() { }

void Honey::on_faint(Pos pos) {
    utils::vector_logs.push_back(m_name + " on " + m_attached_pet->m_name + " summons a bee !");

    Pet* bee = AllPets::create_new_pet("bee", m_team, m_shop);
    bee->bind(m_attached_pet->get_adv_team());
    m_team->summon(pos, bee);
}
