
#include "Objects/Foods/Apple.hpp"

#include <vector>


Apple::Apple(Team* team, Shop* shop) : Object("apple", team, shop, ObjType::FOOD) {
    id = 1;
    pack = PACK_STANDARD | PACK_DLC1;
    tier = 1;
}

Apple::~Apple() { }

void Apple::on_buy(int index) {
    std::vector<Animal*> team_animals = get_team_animals();

    team_animals[index]->buff(1, 1, false);
}
