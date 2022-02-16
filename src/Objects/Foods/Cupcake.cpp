
#include "Objects/Foods/Cupcake.hpp"

#include <vector>

#include "utils.hpp"


Cupcake::Cupcake(Team* team, Shop* shop) : Object("cupcake", team, shop, ObjType::FOOD) {
    id = 3;
    tier = 2;
}

Cupcake::~Cupcake() { }

void Cupcake::on_buy(size_t index) {
    spdlog::debug("{} bought !", name);
    std::vector<Pet*>& team_pets = get_team_pets();

    team_pets[index]->buff(3, 3, true);
}
