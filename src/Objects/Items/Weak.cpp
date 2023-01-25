
#include "Objects/Items/Weak.hpp"

#include "utils.hpp"


Weak::Weak(Team* team, Shop* shop) : Object("Weak", team, shop, ObjType::ITEM) {
    m_repr = "🦠";
    m_id = 5;
    m_tier = -1;
    m_target_all = false;
}

Weak::~Weak() { }

int Weak::on_damages(int value) {
    utils::vector_logs.push_back(m_attached_pet->m_name + " is " + m_name + ", it takes 3 damages more");
    return value + 3;
}
