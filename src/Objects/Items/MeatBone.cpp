
#include "Objects/Items/MeatBone.hpp"

#include "utils.hpp"


MeatBone::MeatBone(Team* team, Shop* shop) : Object("MeatBone", team, shop, ObjType::ITEM) {
    m_repr = "🍖";
    m_id = 6;
    m_tier = 2;
}

MeatBone::~MeatBone() { }

int MeatBone::on_attack(int value) {
    utils::vector_logs.push_back(m_attached_pet->m_name + " has " + m_name + ", it deals 5 damages more");
    return value + 5;
}
