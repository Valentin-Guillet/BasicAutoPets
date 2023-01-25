
#include "Objects/Foods/Apple.hpp"

#include <vector>

#include "utils.hpp"


Apple::Apple(Team* team, Shop* shop) : Object("Apple", team, shop, ObjType::FOOD) {
    m_repr = "🍎";
    m_id = 1;
    m_tier = 1;
}

Apple::~Apple() { }

void Apple::on_buy(size_t index) {
    utils::vector_logs.push_back(m_name + " bought !");
    std::vector<Pet*> team_pets = m_team->get_pets();

    team_pets[index]->buff(1, 1, false);
}
