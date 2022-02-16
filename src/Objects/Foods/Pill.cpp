
#include "Objects/Foods/Pill.hpp"

#include <vector>

#include "utils.hpp"


Pill::Pill(Team* team, Shop* shop) : Object("pill", team, shop, ObjType::FOOD) {
    id = 5;
    tier = 2;
    cost = 1;
}

Pill::~Pill() { }

void Pill::on_buy(size_t index) {
    spdlog::debug("{} bought !", name);
    team->faint(index);
}
