
#include "Objects/Foods/Pill.hpp"

#include <vector>

#include "utils.hpp"


Pill::Pill(Team* team, Shop* shop) : Object("Pill", team, shop, ObjType::FOOD) {
    repr = "💊";
    id = 4;
    tier = 2;
    cost = 1;
    target_all = false;
}

Pill::~Pill() { }

void Pill::on_buy(size_t index) {
    utils::vector_logs.push_back(name + " bought !");

    if (!team->has_pet(index))
        return;

    Pet* pet = team->get_pets()[team->pos_to_index(index)];
    pet->kill();
}
