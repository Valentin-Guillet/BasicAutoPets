
#include "Objects/Foods/Pill.hpp"

#include <vector>

#include "utils.hpp"


Pill::Pill(Team* team, Shop* shop) : Object("pill", team, shop, ObjType::FOOD) {
    id = 2;
    pack = PACK_STANDARD | PACK_DLC1;
    tier = 1;
    cost = 1;
}

Pill::~Pill() { }

void Pill::on_buy(int index) {
    spdlog::debug("{} bought !", name);
    std::vector<Pet*>& team_pets = get_team_pets();

    Pet* pet = team_pets[index];
    team_pets.erase(team_pets.begin() + index);
    pet->on_faint();
    delete pet;
}
