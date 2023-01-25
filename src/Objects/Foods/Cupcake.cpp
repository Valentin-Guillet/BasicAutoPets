
#include "Objects/Foods/Cupcake.hpp"

#include <vector>

#include "utils.hpp"


Cupcake::Cupcake(Team* team, Shop* shop) : Object("Cupcake", team, shop, ObjType::FOOD) {
    m_repr = "🧁";
    m_id = 3;
    m_tier = 2;
}

Cupcake::~Cupcake() { }

void Cupcake::on_buy(size_t index) {
    utils::vector_logs.push_back(m_name + " bought !");
    std::vector<Pet*> team_pets = m_team->get_pets();

    team_pets[index]->buff(3, 3, true);
}
