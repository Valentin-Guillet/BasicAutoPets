
#include "Objects/Foods/Apple.hpp"

#include <vector>

#include "utils.hpp"


Apple::Apple(Team* team, Shop* shop) : Object("Apple", team, shop, ObjType::FOOD) {
    repr = "🍎";
    id = 1;
    tier = 1;
    target_all = false;
}

Apple::~Apple() { }

void Apple::on_buy(size_t index) {
    utils::vector_logs.push_back(name + " bought !");
    std::vector<Pet*> team_pets = team->get_pets();

    team_pets[index]->buff(1, 1, false);
}
