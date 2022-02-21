
#include "Objects/Foods/Apple.hpp"

#include <vector>

#include "utils.hpp"


Apple::Apple(Team* team, Shop* shop) : Object("apple", team, shop, ObjType::FOOD) {
    repr = "🍎";
    id = 1;
    tier = 1;
    target_all = false;
}

Apple::~Apple() { }

void Apple::on_buy(size_t index) {
    spdlog::debug("{} bought !", name);
    std::vector<Pet*>& team_pets = get_team_pets();

    team_pets[index]->buff(1, 1, false);
}
