
#include "Pets/Horse.hpp"

#include "utils.hpp"


Horse::Horse(Team* team, Shop* shop) : Pet("Horse", team, shop) {
    repr = "🐎";
    id = 8;
    pack = PACK_STANDARD;
    tier = 1;
    attack = 2;
    life = 1;
    reset_stats();
}

Horse::~Horse() { }

void Horse::on_friend_summoned(Pet* new_pet) {
    utils::vector_logs.push_back(name + " applies temporary buff to new " + new_pet->name + "!");

    int lvl = get_level();
    new_pet->buff(lvl, 0, true);
}
