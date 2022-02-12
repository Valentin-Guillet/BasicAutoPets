
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
    team->faint(index);
}
