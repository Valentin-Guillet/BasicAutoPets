
#include "Objects/Foods/Pill.hpp"

#include <vector>

#include "utils.hpp"


Pill::Pill(Team* team, Shop* shop) : Object("pill", team, shop, ObjType::FOOD) {
    repr = "💊";
    id = 5;
    tier = 2;
    cost = 1;
    target_all = false;
}

Pill::~Pill() { }

void Pill::on_buy(size_t index) {
    utils::vector_logs.push_back(name + " bought !");
    team->faint(index);
}
