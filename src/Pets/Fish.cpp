
#include "Pets/Fish.hpp"

#include "utils.hpp"


Fish::Fish(Team* team, Shop* shop) : Pet("Fish", team, shop) {
    repr = "🐟";
    id = 7;
    pack = PACK_STANDARD | PACK_DLC1;
    tier = 1;
    attack = 2;
    life = 3;
    reset_stats();
}

Fish::~Fish() { }

void Fish::on_level_up() {
    utils::vector_logs.push_back(name + " level up, buffing other pets !");

    int lvl = get_level();
    for (Pet* pet : get_team_pets()) {
        if (pet == this)
            continue;
        pet->buff(lvl-1, lvl-1, false);
    }
}
